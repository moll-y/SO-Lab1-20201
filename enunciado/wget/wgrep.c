/*
 * wgrep is a super reduced mirror of the command-line tool grep.
 * It takes the pattern as its first argument and then a list of
 * files. If there is not any file, it will read from the stdin.
 *
 * By moll-y and Loidarua IBM.
 */
#include<stdio.h>
#include<string.h>

void fprintstr(FILE *, char *);

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }
    if (argc == 2)
        fprintstr(stdin, argv[1]);
    else {
        for (int i = 2; i < argc; i++) {
            if ((fp = fopen(argv[i], "r")) == NULL) {
                printf("wgrep: cannot open file\n");
                return 1;
            }
            fprintstr(fp, argv[1]);
            fclose(fp);
        }
    }
    return 0;
}

/* 
 * fprintstr wrap the strstr function. It reads 
 * from f line per line and if an occurrence of p is 
 * found it writes the entiry line to stdout and so on.
 */
void fprintstr(FILE *f, char *p) 
{
    char *buf = NULL;
    size_t n = 0;
    /*
     * if we initialize *buf to null and n to 0
     * getline will make malloc for us. 
     */
    while (getline(&buf, &n, f) != -1)
        if (strstr(buf, p) != NULL) 
            printf("%s", buf);
}
