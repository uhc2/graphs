#include <stdio.h> //printf
#include <string.h> //memset

//i apologize for the ugly and unreadable code

//dijkstras algorithm
//change the graph defs, num_nodes, to_node and
//from_node at your wish, here set to test values
//platform independant, tested with the arguments below
//currently needs to recompile for every change in arguments(fix this later)

//unfinished, there is a number of things to add/modify

#define TEST_TO 1
#define TEST_FROM 2


#define NO_CONN 0
#define INFINITY 999999	//hope for the best
#define NOT_MEASURED -1
#define MAX_NODES 50

#define PERM 1 //label type
#define TEMP 0

int graph[MAX_NODES][MAX_NODES]; //graph[a][b] = distance from a to b, 0= no conn
struct node_state{
	int len;
	int measured_from;
	int label_type;
};
struct node_state g_state[MAX_NODES]; //g is for global
int main(int argc,const char **argv)
{
	int to_node = TEST_TO;
	int from_node = TEST_FROM;
	int i,current_min,num_nodes,work_node;
	num_nodes=5;	//num of nodes for this graph(see below)

	//init
	for(i=0;i<num_nodes;i++)
	{
		g_state[i].len = INFINITY;
		g_state[i].measured_from = NOT_MEASURED;
		g_state[i].label_type = TEMP;
	}
	memset(graph,NO_CONN,sizeof(graph)); //set graph to NO_CONN(0)

	//bidirectional test graph, for image see below

	graph[0][1] = 1;
	graph[1][0] = 1;

	graph[2][3] = 2;
	graph[3][2] = 2;

	graph[3][4] = 3;
	graph[4][3] = 3;

	graph[4][0] = 2;
	graph[0][4] = 2;

	graph[2][4] = 1;
	graph[4][2] = 1;
	/*
	(x) denotes weight, z denotes the node number
	0--(1)--1
	|
	(2)
	|
	4--(1)--2
	|       |
	(3)     |
	|       |
	3------(2)
	*/

	g_state[to_node].len = 0;
	g_state[to_node].label_type = PERM;
	work_node = to_node;
	while(work_node != from_node)
	{

		//label the neighbours
		for(i=0;i<num_nodes;i++)
			if((graph[work_node][i]) && !(g_state[i].label_type))
			{
				//every temp one with a connection to the worknode

				//2 if statements because block would be too big
				//is the dist source->worknode + dist worknode->new <
				//dist source->new? if so, we have a shorter path
				if((g_state[work_node].len + graph[work_node][i]) < (g_state[i].len))
				{
					g_state[i].measured_from = work_node;
					g_state[i].len = g_state[work_node].len + graph[work_node][i];
				}
			}

		//check for new worknode(smallest temp label)
		current_min = INFINITY;
		for(i=0;i<num_nodes;i++)
			if(!(g_state[i].label_type)&&(g_state[i].len < current_min))
			{
 				//serach for smallest temp node, make it the new worknode
				work_node = i;
				current_min = g_state[i].len;
			}
		g_state[work_node].label_type = PERM; //worknode has label set to perm
	}
	printf("path from %d to %d,total length: %d\n", from_node, to_node, g_state[from_node].len);
	while(g_state[work_node].len)
	{
		printf("%d -> ", work_node); //traverse the worked out shortest path
		work_node = g_state[work_node].measured_from; //go backwards

		/*note: graph bidirectional -> a ->b = b->a, so it doesnt matter
		if we start with to_node or from_node as worknode.
		we start with to_node because every node gets labelled with
		the node measured_from, the worknode of the last round
		if we wanted to start with from_node(the logical start),
		we would have to search all the nodes for the ones measured shortest
		from the current one */
	}
	printf("%d\n", to_node); //print to_node

	return 0;
}
