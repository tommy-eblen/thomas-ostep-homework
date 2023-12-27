#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int x = 100;
    int rc = fork();
    if (rc < 0) {
    // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child: redirect standard output to a file
        x = 20;
        close(STDOUT_FILENO);
        open("./output.txt", O_CREAT|O_WRONLY|O_TRUNC,S_IRWXU);
        // now exec "wc"...
        char *myargs[3];
        myargs[0] = strdup("wc"); // program: wc
        myargs[1] = strdup("test_text_file.txt"); // arg: file to count
        myargs[2] = NULL; // mark end of array
        execvp(myargs[0], myargs);
        printf("child: %d", x);
    } else {
        // parent goes down this path (main)
        //int rc_wait = wait(NULL);
        x = 80;
        open("./output.txt", O_CREAT|O_WRONLY|O_TRUNC,S_IRWXU);
        printf("parent: %d", x);

    }
    return 0;
}