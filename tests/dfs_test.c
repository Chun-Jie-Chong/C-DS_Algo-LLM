#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/dfs.c"

// Test case for DFS with a graph containing a path from source to destination
void testDFS_PathExists() {
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

    Vertex src = 0;
    Vertex dest = 4;
    CU_ASSERT_TRUE(dfs(g, V, src, dest));

    freeGraph(g);
}

// Test case for DFS with a graph containing no path from source to destination
void testDFS_NoPathExists() {
    int V = 5;
    Graph g = newGraph(V);

    Edge e1 = {0, 1};
    Edge e2 = {0, 2};
    Edge e3 = {1, 2};
    Edge e4 = {1, 3};

    insertEdge(g, e1);
    insertEdge(g, e2);
    insertEdge(g, e3);
    insertEdge(g, e4);

    Vertex src = 0;
    Vertex dest = 4;
    CU_ASSERT_FALSE(dfs(g, V, src, dest));

    freeGraph(g);
}

// Test case for DFS with a graph containing a self-loop
void testDFS_SelfLoop() {
    int V = 3;
    Graph g = newGraph(V);

    Edge e1 = {0, 1};
    Edge e2 = {1, 1};
    Edge e3 = {1, 2};

    insertEdge(g, e1);
    insertEdge(g, e2);
    insertEdge(g, e3);

    Vertex src = 0;
    Vertex dest = 2;
    CU_ASSERT_TRUE(dfs(g, V, src, dest));

    freeGraph(g);
}

// Test case for DFS with an empty graph
void testDFS_EmptyGraph() {
    int V = 0;
    Graph g = newGraph(V);

    Vertex src = 0;
    Vertex dest = 1;
    CU_ASSERT_FALSE(dfs(g, V, src, dest));

    freeGraph(g);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("DFS_Test_Suite", 0, 0);
    CU_add_test(suite, "testDFS_PathExists", testDFS_PathExists);
    CU_add_test(suite, "testDFS_NoPathExists", testDFS_NoPathExists);
    CU_add_test(suite, "testDFS_SelfLoop", testDFS_SelfLoop);
    CU_add_test(suite, "testDFS_EmptyGraph", testDFS_EmptyGraph);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}