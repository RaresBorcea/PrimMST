#include <stdio.h> 
#include <stdlib.h>
#include <limits.h> 

#define MAX 	1100
unsigned long long elem;//contor pentru oper. elementare

/*
 * Definirea structurilor de date
 */

//Definirea structurii unui nod din minheap
typedef struct heapNode 
{
	int v, cost;
}*HeapNode;

//Definirea structurii minheap-ului
typedef struct heap 
{
	HeapNode vector[MAX];
	int size;
	int capacity;
	int* poz;
}*Heap;

//Definirea structurii grafului
typedef struct graph 
{
	int V;
	int **w;
}*Graph;

/*
 * Functii generale, pentru manipularea grafului
 */
Graph initGraph(int V) //initializare
{
	int i;
	Graph g = (Graph) malloc(sizeof(struct graph));
	g->V = V;
	g->w = (int**) malloc(V * sizeof(int*));
	for (i = 0; i < V; i++)
		{
			g->w[i] = (int*) calloc(V, sizeof(int));
			elem += 5;//1 comparatie, 1 incrementare, 1 accesare tip '->', 1 indexare, 1 atribuire
		}
	elem += 2;//1 atribuire (i=0), 1 comparare finala
	elem += 6;//3 atribuiri, 2 accesari tip '->', 1 inmultire
	return g;
}

Graph insertEdge(Graph g, int u, int v, int cost) //adaugare muchie
{
	g->w[u][v] = cost;
	g->w[v][u] = cost;
	elem += 6;//2 atribuiri, 2 indexari, 2 accesari tip '->'
	return g;
}

//Functie care citeste din fisier si creeaza graful
Graph createGraph(char *input, int *n, int *m, int *s)
{
	FILE *file;
	int u, v, cost, i;
	file = fopen(input, "r");

	fscanf(file, "%d %d", m, n);
	fscanf(file, "%d", s);
	Graph g = initGraph(*n); //initializam cu n noduri
	for (i = 0; i < *m; i++) 
	{
		fscanf(file, "%d %d %d", &u, &v, &cost);
		g = insertEdge(g, u, v, cost); //inseram muchiile in graf
		elem += 6;//1 comparare, 1 incrementare, 3 atribuiri prin citirea u v cost,
				 //1 atribuire
	}

	fclose(file);
	elem += 2;//1 atribuire (i=0), 1 comparare finala
	elem += 5;//2 atribuiri, 3 atribuiri prin citirea m n s, 
	return g;
}

/*
 * Functii generale, pentru manipularea heap-ului
 */
HeapNode initHeapNode(int v, int cost)//initializarea unui nod
{ 
    HeapNode newN = (HeapNode) malloc(sizeof(struct heapNode));
    newN->v = v; 
    newN->cost = cost; 
    elem += 5;//3 atribuiri, 2 accesari tip '->'
    return newN; 
}

Heap initHeap()//initializarea heap-ului
{
	Heap h = (Heap) malloc(sizeof(struct heap));
	h->size = 0;
	h->capacity = MAX;
	h->poz = (int*) malloc(MAX * sizeof(int));
	elem += 7;//4 atribuiri, 3 accesari tip '->'
	return h;
}

Heap swapAndSiftDown(Heap h, int parent, int child)//interschimbare
{
	
	HeapNode aux = h->vector[parent];
	h->vector[parent] = h->vector[child];
	h->vector[child] = aux;
	elem += 11;//3 atribuiri, 4 indexari, 4 accesari tip '->'
	return h;
}

Heap siftDown(Heap h, int index)//shiftare in jos parinte<->fii
{
	
	HeapNode l, r;
	int pozmin = index;

	l = h->vector[2 * index + 1];
	if(2 * index + 1 <= h->size && l->cost < h->vector[pozmin]->cost) 
		{
			pozmin = 2 * index + 1; 
			elem += 3;//1 inmultire, 1 adunare, 1 atribuire
		}
	r = h->vector[2 * index + 2];
	if(2 * index + 2 <= h->size && r->cost < h->vector[pozmin]->cost) 
		{
			pozmin = 2 * index + 2; 
			elem += 3;//1 inmultire, 1 adunare, 1 atribuire
		}

	if(index != pozmin)
	{
		h->poz[h->vector[pozmin]->v] = index;
		h->poz[h->vector[index]->v] = pozmin;
		elem += 12;//6 accesari tip '->', 4 indexari, 2 atribuiri
 		swapAndSiftDown(h, index, pozmin);
		siftDown(h, pozmin);
	}
	elem += 32;//3 atribuiri, 10 accesari tip '->', 4 indexari, 4 inmultiri, 4 adunari, 4 comparari
			   //2 and-uri, 1 neegalitate
	return h;
}

Heap siftUp(Heap h, int index, int cost)//shiftare in sus fiu<->parinte
{

	int i = h->poz[index];
	h->vector[i]->cost = cost;

	while(i >= 1 && h->vector[i]->cost < h->vector[(i - 1)/2]->cost)
	{
		h->poz[h->vector[i]->v] = (i - 1)/2;
		h->poz[h->vector[(i - 1)/2]->v] = i;
		swapAndSiftDown(h, (i - 1)/2, i);
		i = (i - 1)/2;
		elem += 32;//2 comparari, 10 accesari tip '->', 1 and, 6 indexari, 5 scaderi
				  //5 impartiri, 3 atribuiri
	}
	elem += 2;//1 comparare, 1 and finale
	elem += 7;//2 atribuiri, 3 accesari tip '->', 2 indexari
	return h;
}

HeapNode extractMin(Heap h)//extragera minimului din varf/root
{
	if(h->size == 0)
		return NULL;

	HeapNode result;
	result = h->vector[0];
	h->vector[0] = h->vector[h->size - 1];
	h->poz[result->v] = h->size - 1;
	h->poz[h->vector[h->size - 1]->v] = 0;
	h->size = h->size - 1;
	siftDown(h, 0);

	elem += 30;//14 accesari tip '->', 1 egalitate, 6 indexari, 5 atribuiri, 4 scaderi
	return result;
}

void printFile(int* p, int* d, int n, int root)//listarea fisierului prim.out
{
	FILE *file;
	file = fopen("prim.out", "w");

	int cost = 0, i;
	for(i = 0; i < n; i++)
		{	
			if(i != root)
			{
				cost += d[i];
				elem += 3;//1 atribuire, 1 adunare, 1 indexare
			}
			elem += 3;//1 comparare, 1 incrementare, 1 inegalitate
		}
	fprintf(file, "%d\n", cost);

	for(i = 0; i < n; i++)
		{	
			if(i != root)
			{
				if(p[i] < i)
				{
					fprintf(file, "%d %d\n", p[i], i);
					elem += 1;//1 indexare
				}
				else
				{
					fprintf(file, "%d %d\n", i, p[i]);
					elem += 1;//1 indexare
				}
				elem += 2;//1 comparare, 1 indexare
			}
			elem += 3;//1 comparare, 1 incrementare, 1 inegalitate
		}

	elem += 6;//2 atribuiri, 2 initializari (i=0), 2 comparari finale
	fprintf(file, "%llu", elem);
	fclose(file);
}

void Prim(Graph g, int root)//implementarea algoritmului Prim
{
	int n = g->V;
	int d[n];
	int p[n];
	int i;

	Heap h = initHeap();
	for(i = 0; i < n; i++)
	{
		if(i != root)
		{
			d[i] = INT_MAX;
			p[i] = -1;
			h->vector[i] = initHeapNode(i, INT_MAX);
			h->poz[i] = i;
			elem += 10;//4 indexari, 2 accesari tip '->', 4 atribuiri
		}
		elem += 3;//1 comparare, 1 incrementare, 1 neegalitate
	}
	elem += 2;//1 initializare (i=0), 1 comparare finala

	//initializam separat datele din nodul de start
	d[root] = 0;
	h->vector[root] = initHeapNode(root, 0);
	h->poz[root] = root;
	h->size = n;
	siftUp(h, root, 0);

	while(h->size != 0)//cat timp heap-ul nu e vid
	{
		HeapNode node = extractMin(h);
		int u = node->v;
		for(i = 0; i < n; i++)
		{
			if(g->w[u][i] != 0)
				{
					if(h->poz[i] < h->size && g->w[u][i] < d[i])
					{
						d[i] = g->w[u][i];
						p[i] = u;
						elem += 8;//2 atribuiri, 2 accesari tip '->', 4 indexari
						siftUp(h, i, g->w[u][i]);
					}
					elem += 9;//3 accesari tip '->', 3 indexari,
					   		  //2 comparari, 1 and
				}	
			elem += 3;//1 accesare tip '->', 1 neegalitate, 1 indexare
		}
		elem += 5;//2 atribuiri, 1 accesare tip '->', 1 comparare finala, 1 initializ (i=0)
	}
	elem += 1;//1 neegalitate finala

	elem += 14;//5 accesari tip '->', 6 atribuiri, 3 indexari
	printFile(p, d, n, root);
}

int main()//functia principala a programului
{
	int n, m, s;
	Graph g = createGraph("prim.in", &n, &m, &s);
	elem += 1;//1 atribuire
	Prim(g, s);
	return 0;
}