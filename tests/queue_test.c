#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/queue.c"

void testEnqueueDequeue() {
    struct queue *q = create();
    enqueue(q, 10);
    enqueue(q, 20);
    CU_ASSERT_EQUAL(dequeue(q), 10);
    CU_ASSERT_EQUAL(dequeue(q), 20);
    CU_ASSERT_EQUAL(size(q), 0);
    CU_ASSERT_EQUAL(dequeue(q), -1); // Dequeue from an empty queue
    CU_ASSERT_EQUAL(size(q), 0);
    enqueue(q, 30);
    CU_ASSERT_EQUAL(dequeue(q), 30);
    CU_ASSERT_EQUAL(size(q), 0);
}

void testSize() {
    struct queue *q = create();
    CU_ASSERT_EQUAL(size(q), 0);
    enqueue(q, 10);
    CU_ASSERT_EQUAL(size(q), 1);
    enqueue(q, 20);
    CU_ASSERT_EQUAL(size(q), 2);
    dequeue(q);
    CU_ASSERT_EQUAL(size(q), 1);
    dequeue(q);
    CU_ASSERT_EQUAL(size(q), 0);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Queue_Test_Suite", NULL, NULL);
    CU_add_test(suite, "Enqueue and Dequeue Test", testEnqueueDequeue);
    CU_add_test(suite, "Size Test", testSize);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}