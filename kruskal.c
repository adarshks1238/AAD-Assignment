#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int src, dest, weight;
};


struct subset {
    int parent;
    int rank;
};


int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);
int compare(const void* a, const void* b);
void KruskalMST(struct Edge* edges, int V, int E);


int find(struct subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}


void Union(struct subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}


int compare(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight - b1->weight; 
}


void Kruskal(struct Edge* edges, int V, int E) {
    struct Edge* result = (struct Edge*)malloc((V - 1) * sizeof(struct Edge)); 
    if (result == NULL) {
        printf("Memory allocation failed for result array.\n");
        return;
    }

    int e = 0;  
    int i = 0;  

    
    qsort(edges, E, sizeof(edges[0]), compare);

   
    struct subset* subsets = (struct subset*)malloc(V * sizeof(struct subset));
    if (subsets == NULL) {
        printf("Memory allocation failed for subsets array.\n");
        free(result);
        return;
    }

    
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    
    while (e < V - 1 && i < E) {
        struct Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

       
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
       
    }

    
    int totalCost = 0;
    printf("Following are the edges in the constructed MST:\n");
    for (i = 0; i < e; ++i) {
        printf("%d -- %d == %d\n", result[i].src + 1, result[i].dest + 1 , result[i].weight);
        totalCost += result[i].weight;
    }
    printf("Total cost of MST: %d\n", totalCost);

    free(subsets);
    free(result);
}

int main() {
    int V, E;


    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);
    struct Edge* edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    if (edges == NULL) {
        printf("Memory allocation failed for edges array.\n");
        return 1;
    }
    printf("Enter the edges (source, destination, weight):\n");
    for (int i = 0; i < E; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
        edges[i].src--;  
        edges[i].dest--;
    }

    Kruskal(edges, V, E);

 
    free(edges);

    return 0;
}
