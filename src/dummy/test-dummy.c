#include "tests.h"
#include "dummy.h"

static void test_init(void **arg)
{
    dummy_init();
}

const struct CMUnitTest dummy_tests[] = {
    cmocka_unit_test(test_init),
};

SUITE(dummy);
