#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 100
int main() {
int fd;
char buffer[BUFFER_SIZE];
ssize_t bytesRead;
fd = open("Sample.txt\n", O_RDONLY);
if(fd==-1)
{
printf("Error Opening File\n");
return 1;
}
bytesRead = read(fd, buffer, BUFFER_SIZE -1);
if(bytesRead == -1)
{
printf("Error reading file\n");
close(fd);
return 1 ;
}
buffer[bytesRead] = '\0';
printf("%s",buffer);
close(fd);
return 0;
}
