#ifndef MONEY_WORDS_H
#define MONEY_WORDS_H

// Max amount to be cached
#define MAX_MEMOIZED_VALUE 150000

char* money_to_words(long value);

void init_money_cache(void);

void free_money_cache(void);

#endif