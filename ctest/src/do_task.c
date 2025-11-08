#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../resources/resources.h"

/**
 * Releases any acquired resources.
 * */
void release_a( resource_a_t *a ) {
    if (a && *a) {
        free(*a);
        *a = NULL;
    }
}
void release_b( resource_b_t *b ) {
    if (b && *b) {
        free(*b);
        *b = NULL;
    }
}
void release_c( resource_c_t *c ) {
    if (c && *c) {
        free(*c);
        *c = NULL;
    }
}

/**
Acquiring A, B, and C are sequential and dependent. (I think.)
*/
int acquire_a( resource_a_t **a ) {
    resource_a_t* a_t = (resource_a_t *)malloc(sizeof(resource_a_t));
    a_t = *a;
    if (a_t == NULL) {
        return -1; // Error
    }
    return **a_t; // Success
};
resource_b_t * acquire_b( resource_a_t *a ) {
    // Aquiring B is not well defined in the test description. Assuming aquiring B is relational to A.
    resource_a_t* a_t = (resource_a_t *)malloc(sizeof(resource_a_t)); 
    resource_b_t* b_t = (resource_b_t *)malloc(sizeof(resource_b_t));
    a_t = a;
    if (a_t == NULL) {
        return NULL; // Error
    } else {
        // do something with a_t to get b_t
    }
    return b_t; // Success
};
void acquire_c(resource_a_t *a, resource_c_t **c, int *ecode) {
    // Aquiring C is not well defined in the test description. Assuming aquiring C to return ecode.
    resource_c_t* c_t = (resource_c_t *)malloc(sizeof(resource_c_t));
    c_t = *c;
    if (c_t == NULL) {
        *ecode = 11; // Try Again Error
        printf("Error", "%d", *ecode);
        printf(strerror(*ecode));
        perror("Failed to acquire resource C\n");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Successfully acquired resource C\n");
        printf("Ecode: %d\n", *ecode);
    }
};

/**
 * task involves calling do_subtask() on resources A, B, and C, and getting a result
 * */
int do_subtask(
    // These resources are pointers to the actual resources  
    resource_a_t    *this_a,
    resource_b_t    *this_b,
    resource_c_t    *this_c,
    result_t        *result
    ) {
    // Based on the test description, the assumption is acquiring A -> B --> C are sequential.
    // If A fails, B and C are not acquired. Likewise with B and C.
    int             acquire_a( resource_a_t **a );
    resource_b_t *  acquire_b( resource_a_t *a );
    void            acquire_c( resource_a_t *a, resource_c_t **c, int *ecode );
}
int do_task(result_t *result) {
    // These resources are the actual resources
    // resources are not specified by the test, so they are defined in headers
    resource_a_t this_a;
    resource_b_t this_b;
    resource_c_t this_c;
    
    int do_subtask(
        resource_a_t    *this_a,
        resource_b_t    *this_b,
        resource_c_t    *this_c,
        result_t        *result
    );
    
    //After aquisition release resources from memory.
    void release_a( resource_a_t *a );
    void release_b( resource_b_t *b );
    void release_c( resource_c_t *c );
}

