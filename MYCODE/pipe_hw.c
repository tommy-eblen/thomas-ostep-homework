#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int main() {
    printf("this is the parent pid: %d", (int)getpid());
    fflush(stdout);
    int p[2]; //p[0] is read, p[1] is write
    pipe(p);

    char buff1[100];

    int rc = fork();
    dup2(p[1], STDOUT_FILENO);
    dup2(p[0], STDIN_FILENO);
    if(rc == 0){
        // Note that we an write to stdout, but not read from it(or can we...)
        puts("Boy I hope this works");
        fflush(stdout);
    }
    else {
        int rc2 = fork();
        if(rc2 == 0){
            int fd = open("output/pipe_hw_output.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
            // Note we can read from stdin, but not write to it(or can we...)
            int n = read(STDIN_FILENO, buff1, sizeof buff1); // n is number of bytes read
            write(fd, buff1, n);

        }
        else {
            printf("end of parent: %d", (int)getpid());
            fflush(stdout);
        }
    }
    return 0;

}