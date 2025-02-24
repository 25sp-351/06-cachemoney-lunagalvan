#include <stdio.h>
#include <stdlib.h>
#include "money_words.h"

int main(void) {
    char line[100];
    long cents;

    init_money_cache();

    while (fgets(line, sizeof(line), stdin)) {
        cents = atol(line);
        char* words = money_to_words(cents);
        printf("%ld = %s\n", cents, words);
        free(words);
    }

    free_money_cache();
    return 0;
}