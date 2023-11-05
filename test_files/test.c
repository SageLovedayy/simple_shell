#include "main.h"

int main() {
    /* The string to tokenize */
    char input[] = "NULL";
    /* Delimiters */
    const char *delimiters = " -,";

    /* Get the first token */
    char *token = _strtok(input, delimiters);

    /* Walk through the rest of the tokens */
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = _strtok(NULL, delimiters); /* Get the next token */
    }

    return 0;
}
