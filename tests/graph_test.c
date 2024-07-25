#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/graph.c"

void testGraph() {
    // Create a new graph with 3 vertices
    Graph g = newGraph(3);

    // Test adjacency after inserting edges
    Edge e1 = {0, 1};
    Edge e2 = {1, 2};
    insertEdge(g, e1);
    insertEdge(g, e2);
    CU_ASSERT_TRUE(adjacent(g, 0, 1));
    CU_ASSERT_TRUE(adjacent(g, 1, 0));
    CU_ASSERT_TRUE(adjacent(g, 1, 2));
    CU_ASSERT_TRUE(adjacent(g, 2, 1));
    CU_ASSERT_FALSE(adjacent(g, 0, 2));
    CU_ASSERT_FALSE(adjacent(g, 2, 0));

    // Test adjacency after removing an edge
    removeEdge(g, e1);
    CU_ASSERT_FALSE(adjacent(g, 0, 1));
    CU_ASSERT_FALSE(adjacent(g, 1, 0));

    // Free the graph
    freeGraph(g);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Graph_Test_Suite", 0, 0);
    CU_add_test(suite, "testGraph", testGraph);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}