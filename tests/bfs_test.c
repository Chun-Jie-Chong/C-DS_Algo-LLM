#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/bfs.c"

void testBFS_NoEdges() {
    int V = 5;
    Graph g = newGraph(V);

    // No edges in the graph

    CU_ASSERT_FALSE(bfs(g, V, 0, 4));

    freeGraph(g);
}

void testBFS_SingleEdge() {
    int V = 5;
    Graph g = newGraph(V);

    Edge e = {0, 1};
    insertEdge(g, e);

    CU_ASSERT_TRUE(bfs(g, V, 0, 1));
    CU_ASSERT_FALSE(bfs(g, V, 0, 2));

    freeGraph(g);
}

void testBFS_MultipleEdges() {
    int V = 5;
    Graph g = newGraph(V);

    Edge e1 = {0, 1};
    Edge e2 = {0, 2};
    Edge e3 = {1, 2};
    Edge e4 = {1, 3};
    Edge e5 = {2, 4};

    insertEdge(g, e1);
    insertEdge(g, e2);
    insertEdge(g, e3);
    insertEdge(g, e4);
    insertEdge(g, e5);

    CU_ASSERT_TRUE(bfs(g, V, 0, 4));
    CU_ASSERT_TRUE(bfs(g, V, 1, 3));
    CU_ASSERT_FALSE(bfs(g, V, 0, 3));

    freeGraph(g);
}

void testBFS_SelfLoop() {
    int V = 5;
    Graph g = newGraph(V);

    Edge e1 = {0, 0}; // Self-loop

    insertEdge(g, e1);

    CU_ASSERT_TRUE(bfs(g, V, 0, 0));
    CU_ASSERT_FALSE(bfs(g, V, 0, 1));

    freeGraph(g);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("BFS_Test_Suite", 0, 0);
    CU_add_test(suite, "Test BFS on a graph with no edges", testBFS_NoEdges);
    CU_add_test(suite, "Test BFS on a graph with a single edge", testBFS_SingleEdge);
    CU_add_test(suite, "Test BFS on a graph with multiple edges", testBFS_MultipleEdges);
    CU_add_test(suite, "Test BFS on a graph with a self-loop", testBFS_SelfLoop);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}