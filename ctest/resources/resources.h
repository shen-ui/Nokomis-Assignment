#pragma once

typedef int* result_t;
typedef int* resource_a_t;
typedef int* resource_b_t;
typedef int* resource_c_t;

void release_a( resource_a_t *a );
void release_b( resource_b_t *b );
void release_c( resource_c_t *c );
