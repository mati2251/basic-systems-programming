#include "books.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define PROCESS_NUMBER 10
#define LIBRARY_COUNT 10

static struct sembuf sem_buf;

struct program_properties {
  int books_count;
  int books_in_library_count;
  int readers[PROCESS_NUMBER];
  int number_of_readers;
  int books_in_library_readers_count[LIBRARY_COUNT];
};

struct process_properties {
  int sem_id;
  int msg_id;
};

enum process_type { READER, WRITER };

enum phase_type { RELAX, LIBRARY_USING };

void down(int sem_id, int sem_num) {
  sem_buf.sem_num = sem_num;
  sem_buf.sem_op = -1;
  sem_buf.sem_flg = 0;
  if (semop(sem_id, &sem_buf, 1) == -1) {
    perror("Raising the semaphore");
    exit(1);
  }
}

void up(int sem_id, int sem_num) {
  sem_buf.sem_num = sem_num;
  sem_buf.sem_op = 1;
  sem_buf.sem_flg = 0;
  if (semop(sem_id, &sem_buf, 1) == -1) {
    perror("Lowering the semaphore");
    exit(1);
  }
}

void reader_operation(struct program_properties *program_p,
                      struct process_properties process_p) {
  up(process_p.sem_id, 0);
  down(process_p.sem_id, 1);
  struct book book;
  if (msgrcv(process_p.msg_id, &book, sizeof(book), getpid(), 0) == -1) {
    perror("Odebranie elementu");
    exit(1);
  }
  program_p->books_in_library_readers_count[book.index]--;
  if (program_p->books_in_library_readers_count[book.index] == 0) {
    program_p->books_in_library_count--;
  }
  down(process_p.sem_id, 0);
  if (program_p->books_in_library_count == 0) {
    up(process_p.sem_id, 1);
  }
}

void writer_operation(struct program_properties *program_p,
                      struct process_properties process_p) {
  printf("Process %d is writer now\n", getpid());
  fflush(stdout);
  down(process_p.sem_id, 0);
  down(process_p.sem_id, 3);
  up(process_p.sem_id, 2);
  program_p->books_in_library_readers_count[program_p->books_in_library_count] =
      program_p->number_of_readers;
  struct book book = books[program_p->books_count];
  book.index = program_p->books_in_library_count;
  for (int i = 0; i < program_p->number_of_readers; i++) {
    book.mtype = program_p->readers[i];
    if (msgsnd(process_p.msg_id, &book, sizeof(book), 0) == -1) {
      perror("Wyslanie pustego komunikatu");
      exit(1);
    }
  }
  program_p->books_count++;
  program_p->books_in_library_count++;
  up(process_p.sem_id, 0);
  up(process_p.sem_id, 2);
  up(process_p.sem_id, 3);
  if (program_p->books_in_library_count == LIBRARY_COUNT) {
    down(process_p.sem_id, 2);
  }
}

void add_reader(struct program_properties *program_p,
                struct process_properties process_p) {
  printf("Process %d is writer now\n", getpid());
  fflush(stdout);
  down(process_p.sem_id, 3);
  program_p->readers[program_p->number_of_readers] = getpid();
  program_p->number_of_readers++;
  up(process_p.sem_id, 3);
}

void remove_reader(struct program_properties *program_p,
                   struct process_properties process_p) {
  down(process_p.sem_id, 3);
  for (int i = 0; i < program_p->number_of_readers; i++) {
    if (program_p->readers[i] == getpid()) {
      program_p->readers[i] = program_p->readers[program_p->number_of_readers];
      program_p->number_of_readers--;
      break;
    }
  }
  up(process_p.sem_id, 3);
}

void process(struct program_properties *program_p,
             struct process_properties process_p) {
  enum process_type type = rand() % 2;
  enum phase_type phase = rand() % 2;
  if (type == READER) {
    add_reader(program_p, process_p);
  }
  while (program_p->books_count < 30) {
    enum process_type old_type = type;
    if (phase == RELAX) {
      type = rand() % 2;
      phase = LIBRARY_USING;
    } else {
      if (type == READER) {
        if (old_type == WRITER) {
          add_reader(program_p, process_p);
        }
        reader_operation(program_p, process_p);
      } else {
        if (old_type == READER) {
          remove_reader(program_p, process_p);
        }
        writer_operation(program_p, process_p);
      }
      phase = RELAX;
    }
  }
}

void initialize_semaphore_value(int sum_id, int sum_num) {
  if (semctl(sum_id, sum_num, SETVAL, (int)0) == -1) {
    perror("Nadanie wartosci semaforowi");
    exit(1);
  }
}

int main() {
  printf("Program started\n");
  int shm_id, sem_id, msg_id;
  struct program_properties *properties;
  int number_of_semaphores = 4;
  // Semaphores: 0 - library block, 1 - reader block, 2 - writer block, 3 -
  // current reader block
  sem_id = semget(45282, number_of_semaphores, IPC_CREAT | 0600);
  if (sem_id == -1) {
    perror("Create semaphore arrays");
    exit(1);
  }
  for (int i = 0; i < number_of_semaphores; i++) {
    initialize_semaphore_value(sem_id, i);
  }
  shm_id = shmget(45282, sizeof(struct program_properties), IPC_CREAT | 0600);
  if (shm_id == -1) {
    perror("Create a segment shared memory");
    exit(1);
  }
  properties = (struct program_properties *)shmat(shm_id, NULL, 0);
  properties->books_count = 0;
  properties->books_in_library_count = 0;
  properties->number_of_readers = 0;
  if (properties == NULL) {
    perror("Connecting a shared memory segment");
    exit(1);
  }
  msg_id = msgget(45283, IPC_EXCL | 0600);
  if (msg_id == -1) {
    msg_id = msgget(45283, IPC_CREAT | 0600);
    if (msg_id == -1) {
      perror("Create a message queue");
      exit(1);
    }
  }
  for (int i = 0; i < PROCESS_NUMBER; i++) {
    pid_t pid = fork();
    if (pid == 0) {
      process(properties, (struct process_properties){sem_id, msg_id});
      exit(0);
    }
  }
  for (int i = 0; i < PROCESS_NUMBER; i++) {
    wait(NULL);
  }
  return 0;
}
