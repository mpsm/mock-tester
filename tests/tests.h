#ifndef __TESTS_H__
#define __TESTS_H__

#ifdef UNITTEST

#  include <stddef.h>
#  include <stdarg.h>
#  include <setjmp.h>
#  include <cmocka.h>

#  undef assert
#  define assert(expr) mock_assert((int)(expr), #expr, __FILE__, __LINE__)

typedef struct {
    const struct CMUnitTest *tests;
    unsigned int count;
} group_test_t;

#  define SUITE(suite)                                                         \
    group_test_t suite ## _group_tests = {                                     \
        suite ## _tests,                                                       \
        sizeof(suite ## _tests) / sizeof(suite ## _tests)[0],                  \
    }

#  define RUN(suite)                                                           \
    extern group_test_t suite ## _group_tests;                                 \
    int suite ## _tests_setup(void **state)                                    \
    __attribute__ (( weak ));                                                  \
    int suite ## _tests_setup(void **state)                                    \
    {                                                                          \
        (void)state;                                                           \
        return 0;                                                              \
    }                                                                          \
    int suite ## _tests_teardown(void **state)                                 \
    __attribute__ (( weak ));                                                  \
    int suite ## _tests_teardown(void **state)                                 \
    {                                                                          \
        (void)state;                                                           \
        return 0;                                                              \
    }                                                                          \
    int main(void) {                                                           \
        return _cmocka_run_group_tests(                                        \
                # suite,                                                       \
                suite ## _group_tests.tests,                                   \
                suite ## _group_tests.count,                                   \
                suite ## _tests_setup,                                         \
                suite ## _tests_teardown                                       \
                );                                                             \
    }

#else

#  define assert(expr)

#endif /* UNITTEST */

#endif /* __TESTS_H__ */
