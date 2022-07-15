#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int loop[1024] = {0};
int loop_size = 0;

static inline void push_back(int pos) {
    if(loop_size + 1 > sizeof(loop)) {
        fprintf(stderr, "Error: Too many loops\n");
        exit(1);
    }
    loop[loop_size++] = pos;
}

static inline int pop_back() {
    if (loop_size - 1 < 0) {
        fprintf(stderr, "Usage: Found unexpected end of loop\n");
        exit(1);
    }
    
    return loop[--loop_size];
}

static inline int get_last() {
    if (loop_size - 1 < 0) {
        fprintf(stderr, "Usage: Found unexpected end of loop\n");
        exit(1);
    }

    return loop[loop_size - 1];
}

int main(int argc, char **argv) {
    
    if (argc < 2) {
        fprintf(stderr, "Usage: bf <input>\n");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");

    if(fp == NULL) {
        fprintf(stderr, "Error: Failed to open the specified file.\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    long bytes = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *source = calloc(bytes + 1, sizeof(char));
    fread(source, sizeof(char), bytes, fp);
    if (source == NULL) {
        fprintf(stderr, "Error: Failed to read the specified file.\n");
        exit(1);
    }
    
    fclose(fp);

    source[bytes + 1] = '\0';

    int array[30000] = {0};
    int *dp = array;
    int pos = 0;

    while (pos != strlen(source)) {
        char ch = source[pos];
        switch (ch) {

            case '\n':
            case ' ':
            case '\t':
                break;
            case '>':
                dp++;
                break;
            case '<':
                dp--;
                break;
            case '+':
                (*dp)++;
                break;
            case '-':
                (*dp)--;
                break;
            case ',':
                *dp = getchar();
                break;
            case '.':
                putchar(*dp);
                break;
            case '[':
                if (*dp == 0)
                {
                    while (ch != ']')
                        ch = source[++pos];
                } else {
                    push_back(pos);
                }
                
                break;
            case ']':
                if (*dp != 0)
                    pos = get_last();
                else
                    pop_back();
                
                break;
            default:
                break;
                
        }
        pos++;
    }
    
    return EXIT_SUCCESS;
}