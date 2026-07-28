#include "../src/parser.h"
#include "test.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tests_run = 0;
int tests_failed = 0;

/* TEST CASES */

void test_tokens(void)
{
    printf("Testing token output\n");

    char *tokens[BUFSIZ];
    char *line = malloc(BUFSIZ * sizeof(char));
    size_t size = BUFSIZ;

    strlcpy(line, "this is a test\n", size);

    parse(line, tokens);

    TEST_ASSERT("First token should be 'this'\n", (strcmp("this", tokens[0]) == 0));
    TEST_ASSERT("Second token should be 'is'\n", (strcmp("is", tokens[1]) == 0));
    TEST_ASSERT("Third token should be 'a'\n", (strcmp("a", tokens[2]) == 0));
    TEST_ASSERT("Third token should be 'test'\n", (strcmp("test", tokens[3]) == 0));
}

void test_cmd_with_one_pipe(void) {
    printf("Testing token output with pipes\n");

    char *cmds[BUFSIZ];
    char *tokens1[BUFSIZ];
    char *tokens2[BUFSIZ];
    char *line = malloc(BUFSIZ * sizeof(char));
    size_t size = BUFSIZ;

    strlcpy(line, "this is a test|with pipe\n", size);

    split_pipe_cmd(line, cmds);

    parse(cmds[0], tokens1);
    parse(cmds[1], tokens2);

    TEST_ASSERT("First token should be 'this'\n", (strcmp("this", tokens1[0]) == 0));
    TEST_ASSERT("Second token should be 'is'\n", (strcmp("is", tokens1[1]) == 0));
    TEST_ASSERT("Third token should be 'a'\n", (strcmp("a", tokens1[2]) == 0));
    TEST_ASSERT("Third token should be 'test'\n", (strcmp("test", tokens1[3]) == 0));

    TEST_ASSERT("First token should be 'with'\n", (strcmp("with", tokens2[0]) == 0));
    TEST_ASSERT("Second token should be 'pipe'\n", (strcmp("pipe", tokens2[1]) == 0));
}

void test_cmd_with_multiple_pipes(void) {
    printf("Testing token output with multiple pipes\n");

    char *cmds[BUFSIZ];
    char *tokens1[BUFSIZ];
    char *tokens2[BUFSIZ];
    char *tokens3[BUFSIZ];
    char *tokens4[BUFSIZ];
    char *line = malloc(BUFSIZ * sizeof(char));
    size_t size = BUFSIZ;

    strlcpy(line, "this is a test|with| multiple| pipes\n", size);

    split_pipe_cmd(line, cmds);

    parse(cmds[0], tokens1);
    parse(cmds[1], tokens2);
    parse(cmds[2], tokens3);
    parse(cmds[3], tokens4);

    TEST_ASSERT("First token should be 'this'\n", (strcmp("this", tokens1[0]) == 0));
    TEST_ASSERT("Second token should be 'is'\n", (strcmp("is", tokens1[1]) == 0));
    TEST_ASSERT("Third token should be 'a'\n", (strcmp("a", tokens1[2]) == 0));
    TEST_ASSERT("Third token should be 'test'\n", (strcmp("test", tokens1[3]) == 0));

    TEST_ASSERT("First token should be 'with'\n", (strcmp("with", tokens2[0]) == 0));

    TEST_ASSERT("First token should be 'multiple'\n", (strcmp("multiple", tokens3[0]) == 0));

    TEST_ASSERT("First token should be 'pipes'\n", (strcmp("pipes", tokens4[0]) == 0));

}

/* MAIN */
int main()
{
    printf("----STARTING TESTS----\n");

    test_tokens();
    test_cmd_with_one_pipe();
    test_cmd_with_multiple_pipes();

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
