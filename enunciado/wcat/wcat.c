/*
 * wcat is a super reduced mirror of the command-line tool cat. 
 * It takes the file names as arguments and then prints their 
 * content. It does not use the stdin when there are not any 
 * argument so be careful.
 * 
 * Written by moll-y and Loidarua UdeA.
 *
 */
#include <stdio.h>
#define MAXLINE 1000 

int main(int argc, char *argv[])
{
    char buf[MAXLINE];
    FILE *fp;

    while (--argc > 0) {
        if ((fp = fopen(*++argv, "r")) == NULL) {
            printf("wcat: cannot open file\n");
            return 1;
        }
        while (fgets(buf, MAXLINE, fp) != NULL)
            printf("%s", buf);
        fclose(fp);
    }
    return 0;
}
