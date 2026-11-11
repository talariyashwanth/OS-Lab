#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

int main(void) {
    printf("Parent process ID: %d\n", getpid());

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("Child process ID: %d\n", getpid());
        execl("/bin/echo", "echo",
              "exec() executed in child process", (char *)NULL);
        perror("execl");
        exit(1);
    }

    wait(NULL);
    printf("Child process completed; wait() returned.\n");

    int fd = open("sample1.txt",
                  O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    write(fd, "Linux system calls demo\n", 24);
    close(fd);

    printf("File created and descriptor closed using close().\n");

    struct stat info;

    if (stat("sample1.txt", &info) == 0)
        printf("File size: %lld bytes\n", (long long)info.st_size);

    DIR *dir = opendir(".");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Directory entries (first few):\n");

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL && count < 5) {
        printf("  %s\n", entry->d_name);
        count++;
    }

    closedir(dir);
    return 0;
}