#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_MAX_SIZE 30000

int stack[1024] = {0};
int stack_size = 0;

static inline void push_back(int pos) {
    if(stack_size + 1 > sizeof(stack)) {
        fprintf(stderr, "Error: Too many loops\n");
        exit(1);
    }

    stack[stack_size++] = pos;
}

static inline int pop_back() {
    if (stack_size - 1 < 0) {
        fprintf(stderr, "Error: Found unexpected end of loop\n");
        exit(1);
    }
    
    return stack[--stack_size];
}

static inline int get_last_element() {
    if (stack_size - 1 < 0) {
        fprintf(stderr, "Error: Found unexpected end of loop\n");
        exit(1);
    }

    return stack[stack_size - 1];
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

    int array[ARRAY_MAX_SIZE] = {0};
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
                if (*dp == -1)
                    *dp = 255;
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
                    pos = get_last_element();
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