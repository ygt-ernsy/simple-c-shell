#include "../src/executer.h"
#include "test.h"
#include <stdlib.h>

int tests_run = 0;
int tests_failed = 0;

void test_executing_command(void)
{

    char *const command[] = {"echo", "test_executing_command"};

    int status = execute(2, command);

    // NOTE: I don't know if this is how I should do things
    TEST_ASSERT("The returned value should be 0\n", (status == 0));
}

int main()
{
    printf("----STARTING TESTS----\n");

    test_executing_command();

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
