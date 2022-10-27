#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fd[2]; // 0 read end; 1 write end

int main() {
  pipe(fd);

  int rc = fork();

  if (rc == 0) { // child 1
    int pid = getpid();
    char *msg = "hello world\n";
    printf("PID %d will write: %s\n", pid, msg);
    close(fd[0]);
    write(fd[1], msg, 13);
    close(fd[1]);
    exit(0);
  } else {
    int rc2 = fork();
    if (rc2 == 0) { // child 2
      int pid = getpid();
      close(fd[1]);
      char buf;
      while (read(fd[0], &buf, 1) > 0)
        printf("PID %d reading: %c\n", pid, buf);
      close(fd[0]);
      exit(0);
    }
  }

}