#include "parser.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tests_run = 0;
int tests_failed = 0;

#define TEST_ASSERT(message, test)                                             \
    if (!test)                                                                 \
    {                                                                          \
        printf("[FAILED] %s\n", message);                                      \
        tests_failed++;                                                        \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        printf("[PASSED] %s \n", message);                                     \
    }                                                                          \
    tests_run++;

/* TEST CASES */

int test_tokens(void)
{
    printf("Testing token output\n");

    char *tokens[BUFSIZ];
    char *line = malloc(BUFSIZ * sizeof(char));
    size_t size = BUFSIZ;

    strlcpy(line, "this is a test\n", size);

    parse(line, tokens);

    TEST_ASSERT("First token should be 'this'\n", strcmp("this", tokens[0]) == 0);
    TEST_ASSERT("Second token should be 'is'\n", strcmp("is", tokens[1]) == 0);
    TEST_ASSERT("Third token should be 'a'\n", strcmp("a", tokens[2]) == 0);
    TEST_ASSERT("Third token should be 'test'\n", strcmp("test", tokens[3]) == 0);
}

/* MAIN */
int main(int argc, char *argv[])
{
    printf("----STARTING TESTS----\n");

    test_tokens();

    printf("----TEST SUMMARY----\n");
    printf("Tests run: %d\n", tests_run);
    if (tests_failed == 0)
    {
        printf("SUCCESS: All tests passed!\n");
    }
    else
    {
        printf("FAILURE: %d test(s) failed.\n", tests_failed);
    }

    return EXIT_SUCCESS;
}
