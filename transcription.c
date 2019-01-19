#include <stdio.h>
#include <string.h>

char replace_with_hebrew (char input);

int main() {
    char transliteration[100];
    char output[100];

    fgets(transliteration, 98, stdin);
    int length = strlen(transliteration);

    for (int i = 0; i < length; i++) {
        output[i] = replace_with_hebrew(transliteration[i]);
    }
    fputs(output, stdout);
    return 0;
}

char replace_with_hebrew (char input) {
    static char guide[127];
    /* Estimated Need: 22 letters + 22 dagesh-letters + 14 vowels
                       + 5 final forms + 1 NULL */
    return input;
}
