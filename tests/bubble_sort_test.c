#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/bubble_sort.c"

// Test case 1: Sorting an already sorted array
void testBubbleSort_SortedArray() {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, n);

    for (int i = 0; i < n; i++) {
        CU_ASSERT_EQUAL(arr[i], expected[i]);
    }
}

// Test case 2: Sorting a reverse sorted array
void testBubbleSort_ReverseSortedArray() {
    int arr[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, n);

    for (int i = 0; i < n; i++) {
        CU_ASSERT_EQUAL(arr[i], expected[i]);
    }
}

// Test case 3: Sorting an array with duplicate elements
void testBubbleSort_DuplicateElements() {
    int arr[] = {3, 2, 4, 1, 2, 3};
    int expected[] = {1, 2, 2, 3, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, n);

    for (int i = 0; i < n; i++) {
        CU_ASSERT_EQUAL(arr[i], expected[i]);
    }
}

// Test case 4: Sorting an empty array
void testBubbleSort_EmptyArray() {
    int arr[] = {};
    int expected[] = {};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, n);

    for (int i = 0; i < n; i++) {
        CU_ASSERT_EQUAL(arr[i], expected[i]);
    }
}

// Test case 5: Sorting an array with negative elements
void testBubbleSort_NegativeElements() {
    int arr[] = {-5, -2, -4, -1, -3};
    int expected[] = {-5, -4, -3, -2, -1};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, n);

    for (int i = 0; i < n; i++) {
        CU_ASSERT_EQUAL(arr[i], expected[i]);
    }
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("BubbleSort_Test_Suite", 0, 0);
    CU_add_test(suite, "test_sorted", testBubbleSort_SortedArray);
    CU_add_test(suite, "test_reverse_sorted", testBubbleSort_ReverseSortedArray);
    CU_add_test(suite, "test_duplicate_elements", testBubbleSort_DuplicateElements);
    CU_add_test(suite, "test_empty", testBubbleSort_EmptyArray);
    CU_add_test(suite, "test_negative_integers", testBubbleSort_NegativeElements);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}