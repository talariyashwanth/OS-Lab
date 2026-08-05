#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
int fd;
fd = open("Sample.txt", O_CREAT | O_WRONLY, 0644);
if(fd==-1)
{
printf("Error Opening file\n");
return 1;
}
printf("File openend successfully\n");
close(fd);
return 0;
}
