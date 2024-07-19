#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/merge_sort.c"

// Test case 1: Test sorting an array with positive integers
void testMergeSort_PositiveIntegers() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int expected[] = {5, 6, 7, 11, 12, 13};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, arr_size - 1);

    for (int i = 0; i < arr_size; i++) {
        CU_ASSERT_EQUAL(arr[i], expected[i]);
    }
}

// Test case 2: Test sorting an array with negative integers
void testMergeSort_NegativeIntegers() {
    int arr[] = {-5, -10, -3, -8, -1};
    int expected[] = {-10, -8, -5, -3, -1};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, arr_size - 1);

    for (int i = 0; i < arr_size; i++) {
        CU_ASSERT_EQUAL(arr[i], expected[i]);
    }
}

// Test case 3: Test sorting an array with duplicate elements
void testMergeSort_DuplicateElements() {
    int arr[] = {5, 2, 8, 2, 5};
    int expected[] = {2, 2, 5, 5, 8};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, arr_size - 1);

    for (int i = 0; i < arr_size; i++) {
        CU_ASSERT_EQUAL(arr[i], expected[i]);
    }
}

// Test case 4: Test sorting an already sorted array
void testMergeSort_AlreadySorted() {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, arr_size - 1);

    for (int i = 0; i < arr_size; i++) {
        CU_ASSERT_EQUAL(arr[i], expected[i]);
    }
}

// Test case 5: Test sorting an empty array
void testMergeSort_EmptyArray() {
    int arr[] = {};
    int expected[] = {};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, arr_size - 1);

    for (int i = 0; i < arr_size; i++) {
        CU_ASSERT_EQUAL(arr[i], expected[i]);
    }
}

// Main function
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("MergeSort_Test_Suite", 0, 0);
    CU_add_test(suite, "test_positive_integers", testMergeSort_PositiveIntegers);
    CU_add_test(suite, "test_negative_integers", testMergeSort_NegativeIntegers);
    CU_add_test(suite, "test_duplicate_elements", testMergeSort_DuplicateElements);
    CU_add_test(suite, "test_sorted", testMergeSort_AlreadySorted);
    CU_add_test(suite, "test_empty", testMergeSort_EmptyArray);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}