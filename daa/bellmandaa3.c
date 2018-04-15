#include<stdio.h>

typedef struct graph
{
	int v1;
	int v2;
	int weight;
}graph;

graph g[20];
int nV, nE, dist[20], s, parent[20];

int relax(int u, int v, int w){
	if (dist[v] > dist[u] + w)
	{
		dist[v] = dist[u] + w;
		parent[v] = u;
	}
}

int bellmanford(){
	int i,j;
	for(i = 0; i < nV; i++){
		dist[i] = 9999;
		parent[i] = -1;
	}

	dist[s] = 0;
	parent[s] = 0;

	for(i = 1; i < nV - 1; i++){
		for (j = 0; j < nE; j++)
		{
			relax(g[j].v1, g[j].v2, g[j].weight);
		}

	}

	for (i = 0; i < nE; i++)
	{
		if (dist[g[i].v2] > dist[g[i].v1] + g[i].weight)
		{
			return -1;
		}
	}

	return 0;
}
void main(int argc, char const *argv[])
{	
	

	printf("Enter the number of Vertices: ");
	scanf("%d", &nV);
	printf("Enter the number of Edges: ");
	scanf("%d", &nE);

	int i;

	for (i = 0; i < nE; i++)
	{
		printf("Enter U of EDGE [%d]\t[U]---W--->[V]\t: ", i+1 );
		scanf("%d", &g[i].v1);
		printf("Enter V of EDGE [%d]\t[%d]---W--->[V]\t: ", i+1 , g[i].v1 );
		scanf("%d", &g[i].v2);
		printf("Enter W of EDGE [%d]\t[%d]---W--->[%d]\t: ",i+1, g[i].v1, g[i].v2);
		scanf("%d", &g[i].weight);
	}

	printf("Enter Source Vertex of the graph: ");
	scanf("%d", &s);

	int result = bellmanford();  
    
    if(result == -1)
    
   	{
         printf("Graph has a negative edge cycle.Therefore no solution\n");
    }
    else
    {
        printf("Solution :: \n");
        for(i = 0;i < nV; i++)
        {
            printf("Distance of [%d] from source : %d\n",i,dist[i]);
            printf("Parent of [%d] : [%d] \n", i, parent[i] );
        }
    }
}