/*
 * wzip is a super reduced mirror of the command-line tool zip.
 * It takes files names as arguments and then prints their content
 * compressed to stdout using the method run-length encoding.
 *
 * Written by moll-y and Loidarua NASA.
 */
#include <stdio.h>
#define INTLEN 4       /* 4-bytes integer length */
#define ASCLEN 1       /* 1-byte ascii length    */

void write(int, char, FILE*);

int main(int argc, char *argv[])
{
    char c, b = '\0';
    FILE *fp;
    int n;

    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }
    while (--argc > 0) {
        if ((fp = fopen(*++argv, "r")) == NULL)
            return 1;
        while ((c = getc(fp)) != EOF) {
            if (c == b)
                n++;
            else {
                if (b != '\0')
                    write(n, b, stdout);
                b = c;
                n = 1;
            }
        }
        fclose(fp);
    }
    write(n, b, stdout);
    return 0;
}

/*
 * write writes an integer of 4-bytes size in binary
 * followed by a 1-byte ascii character to f.
 */
void write(int n, char c, FILE *f)
{
    fwrite(&n, INTLEN, 1, f);
    fwrite(&c, ASCLEN, 1, f);
}
