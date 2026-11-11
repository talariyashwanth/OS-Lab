#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char data[100];
    char ch;

    // Create and write to a file
    fp = fopen("sample.txt", "w");

    if (fp == NULL) {
        printf("Unable to create file.\n");
        return 1;
    }

    printf("Enter text to write into the file: ");
    fgets(data, sizeof(data), stdin);

    fprintf(fp, "%s", data);
    fclose(fp);

    printf("\nData written successfully.\n");

    // Read the file
    fp = fopen("sample.txt", "r");

    if (fp == NULL) {
        printf("Unable to open file.\n");
        return 1;
    }

    printf("\nFile contents:\n");

    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);

    // Append data to the file
    fp = fopen("sample.txt", "a");

    if (fp == NULL) {
        printf("Unable to open file.\n");
        return 1;
    }

    printf("\nEnter text to append: ");
    fgets(data, sizeof(data), stdin);

    fprintf(fp, "%s", data);
    fclose(fp);

    printf("\nData appended successfully.\n");

    return 0;
}