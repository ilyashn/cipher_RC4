#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "out.txt"
#define FILE_OPEN_ERROR 2

// procedure that change two symbols positions in s - block
void swap(unsigned char *a, unsigned char *b){
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}
// s - block initialization
void KSA(unsigned char *key, unsigned char *s, unsigned long length){
    int i = 0, j = 0;
    for(i = 0; i < 256; i++) {
        s[i] = (unsigned char) i;
    }
    for(i = 0; i < 256; i++){
        j = (j + s[i] + key[i%length]) % 256;
        swap(&s[i], &s[j]);
    }
}
// generate pseudo-random byte
void PRGA(unsigned char *str, unsigned char *s,  long len){
    int i = 0, j = 0;
    long k = 0;
    while (k < len){
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        swap(&s[i], &s[j]);
        str[k] ^= s[(s[i] + s[j]) % 256];
        k++;
    }
}

int main() {
    unsigned char key[32] = {0};
    unsigned char s[256];
    FILE *in = fopen(INPUT_FILE, "rb");
    if (in == NULL){
        printf("Error! Can't open input file.\n");
        return FILE_OPEN_ERROR;
    }
    fseek(in, 0, SEEK_END);
    long length = ftell(in);
    unsigned char *str = (unsigned char *)calloc(length + 1, sizeof(unsigned char));
    fseek(in, 0, SEEK_SET);
    fread(str, length, 1, in);
    fclose(in);
    str[length] = '\0';
    scanf("%s", key);
    KSA(key, s, strlen(key));
    PRGA(str, s, length);
    FILE *out = fopen(OUTPUT_FILE, "wb");
    if (out == NULL){
        printf("Error! Can't open output file.\n");
        return FILE_OPEN_ERROR;
    }
    fwrite(str, sizeof(char), strlen(str), out);
    fclose(out);
    KSA(key, s, strlen(key));
    PRGA(str, s,  length);
    printf("%s", str);
    return 0;
}
