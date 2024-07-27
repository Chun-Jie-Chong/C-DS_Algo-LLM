#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/hash_map.c"

void testHashMap() {
    HashMap *map = createHashMap(10);

    // Test insertion
    insert(map, "key1", 100);
    insert(map, "key2", 200);
    insert(map, "key3", 300);

    // Test lookup
    int value;
    get(map, "key1", &value);
    CU_ASSERT_EQUAL(value, 100);
    get(map, "key2", &value);
    CU_ASSERT_EQUAL(value, 200);
    get(map, "key3", &value);
    CU_ASSERT_EQUAL(value, 300);

    CU_ASSERT_FALSE(get(map, "key4", &value));

    // Test deletion
    delete(map, "key2");
    CU_ASSERT_FALSE(get(map, "key2", &value));

    // Test cleanup
    freeHashMap(map);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("HashMap_Test_Suite", NULL, NULL);
    CU_add_test(suite, "testHashMap", testHashMap);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}