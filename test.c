#include <stdlib.h>
#include <assert.h>
#include <mimick.h>
#include <errno.h>
#include "my_fn.h"

/* Define the blueprint of a mock identified by `malloc_proto`
   that returns a `void *` and takes a `size_t size` parameter. */
mmk_mock_define (malloc_mock, void *, size_t, size);
mmk_mock_define (my_fn_mock, int, int, hello);

int main(void) {
    mmk_init ();

    /* Mock the malloc function in the current module using 
       the `malloc_mock` blueprint. */
    mmk_mock m = mmk_mock_create ("malloc", malloc_mock);

    /* Tell the mock to return NULL and set errno to ENOMEM
       whatever the given parameter is. */
    mmk_when (m, malloc_mock, with (mmk_any (size_t)),
            .then_return = NULL,
            .then_errno = ENOMEM);

    assert(malloc(42) == NULL && errno == ENOMEM);
    mmk_mock_destroy(m);


    mmk_mock m2 = mmk_mock_create ("my_fn", my_fn_mock);
    mmk_when (m2, my_fn_mock, with (mmk_any (int)),
            .then_return = 123);
    assert(my_fn(42) == 123);

    mmk_mock_destroy(m2);
}

