#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Poczatek\n");
    execlp("jaja", "ale jaja", "-l", NULL);
    perror("haha ale jaja bład");
    printf("Koniec \n");
    return 0;
}
