#include <stdio.h>
#include "do_task.c"
#include "../resources/resources.h"

int main(int argc, char *argv[]) {

    printf("ctest main started\n");
    result_t* result = (result_t *)malloc(sizeof(result_t));
    do_task(result);
    return 0;
}