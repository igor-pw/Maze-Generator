#include "graph.h"

void find_exit(node_t node, bool *found)
{
	//sciezka od wierzcholka startowego do wyjscia zostala znaleziona
	if(node->end)
		*found = true;

	//wierzcholek ma przejscie oraz sciezka nie zostala jeszcze znaleziona
	if(node->edge > 0 && !(*found))
	{
		//rekurencyjne wywolanie funkcji find_exit dla nastepnych wierzcholkow
		for(int i = 0; i < node->edge; i++)
			find_exit(node->next_node[i], found);
	}
}

