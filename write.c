#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char message[] = "Hello!\nWelcome to Linux System Calls.\nThis file is created using write() system call.\n";

    // Open or create the file
    fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd == -1)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // Write data to the file
    if (write(fd, message, strlen(message)) == -1)
    {
        printf("Error writing to file.\n");
        close(fd);
        return 1;
    }

    printf("Data written successfully to output.txt\n");

    // Close the file
    close(fd);

    return 0;
}

