#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/hash_set.c"

void testAddAndContains() {
    HashSet* set = createHashSet();
    
    add(set, 5);
    add(set, 10);
    add(set, 15);

    CU_ASSERT_TRUE(contains(set, 5));
    CU_ASSERT_TRUE(contains(set, 10));
    CU_ASSERT_TRUE(contains(set, 15));
    CU_ASSERT_FALSE(contains(set, 20));
}

void testRemove() {
    HashSet* set = createHashSet();
    
    add(set, 5);
    add(set, 10);
    add(set, 15);

    removeKey(set, 10);

    CU_ASSERT_TRUE(contains(set, 5));
    CU_ASSERT_FALSE(contains(set, 10));
    CU_ASSERT_TRUE(contains(set, 15));
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("HashSet_Test_Suite", NULL, NULL);
    CU_add_test(suite, "Add and Contains Test", testAddAndContains);
    CU_add_test(suite, "Remove Test", testRemove);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}