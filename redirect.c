#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    close(STDOUT_FILENO);
    open("./redirected-output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    char *myargs[3];
    myargs[0] = strdup("wc");
    myargs[1] = strdup("fork-wait.c");
    myargs[2] = NULL;
    execv("/usr/bin/wc", myargs);
    printf("this shouldn't print out");
  } else {
    int rc_wait = wait(NULL);
  }

  return 0;
}
