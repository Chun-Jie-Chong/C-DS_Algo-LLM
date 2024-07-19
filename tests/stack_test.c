#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/stack.c"

// Test case to check if the stack is empty after creation
void testIsEmptyAfterCreation() {
    Stack *stack = createStack(MAX_CAPACITY);
    CU_ASSERT_TRUE(isEmpty(stack));
    // destroyStack(stack);
}

// Test case to check the size of the stack after pushing elements
void testSizeAfterPush() {
    Stack *stack = createStack(MAX_CAPACITY);
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    CU_ASSERT_EQUAL(size(stack), 3);
    // destroyStack(stack);
}

// Test case to check if the top element is correct after pushing elements
void testTopAfterPush() {
    Stack *stack = createStack(MAX_CAPACITY);
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    CU_ASSERT_EQUAL(top(stack), 30);
    // destroyStack(stack);
}

// Test case to check if the stack is empty after popping all elements
void testIsEmptyAfterPop() {
    Stack *stack = createStack(MAX_CAPACITY);
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    pop(stack);
    pop(stack);
    pop(stack);
    CU_ASSERT_TRUE(isEmpty(stack));
    // destroyStack(stack);
}

// Test case to check if the popped element is correct
void testPop() {
    Stack *stack = createStack(MAX_CAPACITY);
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    CU_ASSERT_EQUAL(pop(stack), 30);
    // destroyStack(stack);
}

// Main function to run the test suite
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Stack_Test_Suite", 0, 0);
    CU_add_test(suite, "Test if stack is empty after creation", testIsEmptyAfterCreation);
    CU_add_test(suite, "Test size of stack after pushing elements", testSizeAfterPush);
    CU_add_test(suite, "Test top element after pushing elements", testTopAfterPush);
    CU_add_test(suite, "Test if stack is empty after popping all elements", testIsEmptyAfterPop);
    CU_add_test(suite, "Test popped element", testPop);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}