#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "money_words.h"

static char** cache = NULL;


void init_money_cache(void) {
    cache = (char**)calloc(MAX_MEMOIZED_VALUE + 1, sizeof(char*));
    if (!cache) {
        fprintf(stderr, "Failed to allocate cache\n");
        exit(1);
    }
}
// free the cache
void free_money_cache(void) {
    if (cache) {
        for (long i = 0; i <= MAX_MEMOIZED_VALUE; i++) {
            free(cache[i]);
        }
        free(cache);
        cache = NULL;
    }
}

static const char* ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
static const char* teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
static const char* tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

static char* convert_below_hundred(long value) {
    char buffer[100];
    
    if (value < 10) {
        sprintf(buffer, "%s cent%s", ones[value], value != 1 ? "s" : "");
    } else if (value < 20) {
        sprintf(buffer, "%s cents", teens[value - 10]);
    } else if (value == 100) {
        sprintf(buffer, "one dollar");
    } else {
        long dollars = value / 100;
        long cents = value % 100;
        
        if (dollars > 0 && cents == 0) {
            sprintf(buffer, "%s dollar%s", 
                    ones[dollars],
                    dollars != 1 ? "s" : "");
        } else if (dollars > 0) {
            if (cents < 10) {
                sprintf(buffer, "%s dollar%s and %s cent%s",
                        ones[dollars],
                        dollars != 1 ? "s" : "",
                        ones[cents],
                        cents != 1 ? "s" : "");
            } else if (cents < 20) {
                sprintf(buffer, "%s dollar%s and %s cents",
                        ones[dollars],
                        dollars != 1 ? "s" : "",
                        teens[cents - 10]);
            } else {
                sprintf(buffer, "%s dollar%s and %s%s%s cents",
                        ones[dollars],
                        dollars != 1 ? "s" : "",
                        tens[cents / 10],
                        cents % 10 ? "-" : "",
                        cents % 10 ? ones[cents % 10] : "");
            }
        } else {
            if (cents < 20) {
                sprintf(buffer, "%s cents", teens[cents - 10]);
            } else {
                sprintf(buffer, "%s%s%s cents",
                        tens[cents / 10],
                        cents % 10 ? "-" : "",
                        cents % 10 ? ones[cents % 10] : "");
            }
        }
    }
    
    return strdup(buffer);
}

static char* convert_hundreds(long value) {
    char buffer[100];
    long dollars = value / 100;
    long cents = value % 100;
    
    if (cents == 0) {
        if (dollars < 20) {
            sprintf(buffer, "%s dollars", teens[dollars - 10]);
        } else {
            sprintf(buffer, "%s%s%s dollars",
                    tens[dollars / 10],
                    dollars % 10 ? "-" : "",
                    dollars % 10 ? ones[dollars % 10] : "");
        }
    } else {
        if (dollars < 20) {
            sprintf(buffer, "%s dollars and %s cents",
                    teens[dollars - 10],
                    convert_below_hundred(cents));
        } else {
            sprintf(buffer, "%s%s%s dollars and %s cents",
                    tens[dollars / 10],
                    dollars % 10 ? "-" : "",
                    dollars % 10 ? ones[dollars % 10] : "",
                    convert_below_hundred(cents));
        }
    }
    
    return strdup(buffer);
}

static char* convert_thousands(long value) {
    char buffer[200];
    long dollars = value / 100;
    long cents = value % 100;
    
    if (dollars >= 1000) {
        sprintf(buffer, "%ld,%03ld dollars", dollars / 1000, dollars % 1000);
    } else {
        sprintf(buffer, "%ld dollars", dollars);
    }
    
    if (cents > 0) {
        char cents_buffer[50];
        if (cents < 10) {
            sprintf(cents_buffer, " and %s cent%s",
                    ones[cents],
                    cents != 1 ? "s" : "");
        } else if (cents < 20) {
            sprintf(cents_buffer, " and %s cents",
                    teens[cents - 10]);
        } else {
            sprintf(cents_buffer, " and %s%s%s cents",
                    tens[cents / 10],
                    cents % 10 ? "-" : "",
                    cents % 10 ? ones[cents % 10] : "");
        }
        strcat(buffer, cents_buffer);
    }
    
    return strdup(buffer);
}

char* money_to_words(long value) {

    if (value <= MAX_MEMOIZED_VALUE && cache && cache[value]) {
        return strdup(cache[value]);
    }

    char* result;
    if (value == 0) {
        result = strdup("zero dollars");
    } else if (value == 1) {
        result = strdup("one cent");
    } else if (value == 100) { 
        result = strdup("one dollar");
    } else if (value < 100) {
        result = convert_below_hundred(value);
    } else if (value < 1000) {
        result = convert_hundreds(value);
    } else {
        result = convert_thousands(value);
    }

    if (value <= MAX_MEMOIZED_VALUE && cache) {
        cache[value] = strdup(result);
    }

    return result;
}