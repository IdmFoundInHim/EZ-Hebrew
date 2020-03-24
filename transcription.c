#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "utf8.c"

#define INPUT_BUFFER 256
#define OUTPUT_BUFFER 512
#define GUIDE_BUFFER 256
#define DESTWIDTH 2

char *get_utf8_input()
{
    char *line, *u8s;
    wchar_t *wcs; // orig: unsigned int
    int len;

    line = malloc(1024);
    fgets(line, INPUT_BUFFER - 1, stdin);
    if (setlocale(LC_ALL, "") == "UTF-8") {
        return line;
    }
    else {
        len = mbstowcs(NULL, line, 0)+1;
        wcs = malloc(len * sizeof(int));
        mbstowcs(wcs, line, len);
        u8s = malloc(len * sizeof(int));
        u8_toutf8(u8s, len*sizeof(int), (u_int32_t *)wcs, len);
        free(line);
        free(wcs);
        return u8s;
    }
}

typedef struct mapping{
    unsigned char input;
    unsigned char output[DESTWIDTH];
} mapping;


int main()
{
    unsigned int *test = malloc(INPUT_BUFFER * sizeof(int));
    unsigned char *locale;
    int locale_is_utf;
    locale = setlocale(LC_ALL, "");
    locale_is_utf = u8_is_locale_utf8(locale);
    mapping guide[2] = {{'n', {0xd7, 0xa0}}, {0, ""}};
    // malloc(GUIDE_BUFFER * sizeof(int));
 
    /* Estimated Need: (22 letters + 22 dagesh-letters + 14 vowels
                       + 5 final forms) * 2 languages + 1 NUL = 253 uns. int */
    // char *input = malloc(INPUT_BUFFER);
    unsigned char *output = malloc(OUTPUT_BUFFER);
    unsigned char *output_cpy = output;
    /* Each Hebrew char *should* take 2 bytes (Hebrew block: 0x0590–0x05FF) */
    unsigned char *input = malloc(INPUT_BUFFER);
    fgets(input, INPUT_BUFFER, stdin);
    unsigned char *input_free = input;
    for (int count = 0; count < OUTPUT_BUFFER - 1;) {
        mapping *search = guide;
        int unmapped = 1;
        for (; (*search).input != '\0'; search++)
            if ((*search).input == *input) {
                unmapped = 0;
                break;
            }
        if (unmapped)
            output[count++] = *input;
        else
            for (int i = 0; i < DESTWIDTH; i++)
                output[count++] = (*search).output[i];
        if (!(*(++input))) {
            output[count] = 0;
            break;
        }
    }
    
    for (; *output_cpy; output_cpy++)
        printf("%x ", *output_cpy);
    puts(output);
    getchar();
    free(test);
    free(guide);
    free(input_free);
    free(output);
}

char * replace_with_hebrew (char input);

int main_old() {
    char transliteration[100];
    char output[200];

    fgets(transliteration, 98, stdin);
    int length = strlen(transliteration);

    for (int i = 0; i < length; i++) {
        strcat(output, replace_with_hebrew(transliteration[i]));
    }
    fputs(output, stdout);
    fputs("ע", stdout);
    return 0;
}

char * replace_with_hebrew (char input) {
    static char guide[127] = "gג";
    /* Estimated Need: 22 letters + 22 dagesh-letters + 14 vowels
                       + 5 final forms + 1 NULL */
    static char replacement_chars[3] = "\0\0\0";
    char * p_input = &input;
    char * guide_entry = strstr(guide, p_input);
    if (guide_entry != NULL)
        for (int j = 0; j < 2; j++)
            replacement_chars[j] = guide_entry[j + 1];
    else
        replacement_chars[0] = input;
        replacement_chars[1] = '\0';
    return replacement_chars;
}

