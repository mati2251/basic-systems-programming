#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 512

int main(int argc, char* argv[]){
    int desc = open("plik.txt", O_RDWR);
    lseek(desc, 532235, SEEK_CUR);
    write(desc, "cos tam", 4);
    close(desc);
    exit(0);
}