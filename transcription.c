#include <stdio.h>
#include <string.h>

char * replace_with_hebrew (char input);

int main() {
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
