#include <stdio.h> 
#include <stdlib.h>
#include <limits.h> 

#define MAX 	1100
unsigned long long elem;//contor pentru oper. elementare

/*
 * Definirea structurilor de date
 */
//Definirea structurii nod - cost
typedef struct pair 
{
	int v, cost;
} Pair;

//Definirea structurii listei
typedef struct list 
{
	Pair data;
	struct list *next;
}*List;

//Definirea structurii grafului
typedef struct graph 
{
	int V;
	List *adjLists;
}*Graph;

/*
 * Functii generale, pentru manipularea listelor
 */
List initList(Pair data) //initializare
{
	List newL;
	newL = (List) malloc(sizeof(struct list));
	newL->data = data;
	newL->next = NULL;
	elem += 5; //3 atribuiri, 2 accesari tip '->'
	return newL;
}

List add(List list, Pair data) //adaugare in lista
{
	List newEl, temp = list;
	newEl = initList(data);
	if (list == NULL) 
		return newEl; 
	else while(temp->next != NULL) 
		{
			temp = temp->next;
			elem += 4;//2 accesari tip '->', 1 neegalitate, 1 atribuire
		}
	temp->next = newEl;
	elem += 2;//o data in plus conditia din while: 1 accesare tip '->', 1 inegalitate
	elem += 5;//in afara while: 3 atribuiri, 1 egalitate, 1 accesare tip '->'
	return list;
}

/*
 * Functii generale, pentru manipularea grafului
 */
Graph initGraph(int V) //initializare
{
	int i;
	Graph g = (Graph) malloc(sizeof(struct graph));
	g->V = V;
	g->adjLists = (List*) malloc(V * sizeof(List));
	for (i = 0; i < V; i++)
		{
			g->adjLists[i] = NULL;
			elem += 5;//1 comparare, 1 incrementare, 1 accesare tip '->', 1 indexare, 1 atribuire
		}
	elem += 2;//1 atribuire (i=0), 1 comparare finala
	elem += 6;//3 atribuiri, 2 accesari tip '->', 1 inmultire
	return g;
}

Graph insertEdge(Graph g, int u, int v, int cost) //adaugare muchie
{
	Pair p;
	p.cost = cost;
	p.v = v;
	g->adjLists[u] = add(g->adjLists[u], p);
	p.v = u;
	g->adjLists[v] = add(g->adjLists[v], p);
	elem += 16;//3 accesari tip struct.x, 5 atribuiri, 4 accesari tip '->', 4 indexari
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
 * Functii generale, pentru manipularea vectorului
 */
void sort(Pair* s, int n, int* poz)//sortarea
{
	int done = 0, i;
	Pair aux;
	while(!done) 
	{
		done = 1;
		for(i = 0; i < n - 1; i++)
			{
				if(s[i].cost > s[i + 1].cost) 
				{
					done = 0;
					poz[s[i].v]++;
					poz[s[i + 1].v]--;
					aux = s[i];
					s[i] = s[i + 1];
					s[i + 1] = aux;
					elem += 19;//4 atribuiri, 8 indexari, 2 accesari tip struct.x
							   //1 incrementare, 1 decrementare, 3 adunari
				}
				elem += 9;//2 comparari, 1 incrementare, 1 scadere, 2 indexari
						  //2 accesari tip struct.x, 1 adunare
			}
		elem += 4;//2 atribuiri, 1 comparare finala, 1 scadere finala
	}
	elem += 2;//1 atribuire, 1 inegalitate finala
}

int extractMin(Pair* s, int *n, int* poz)//extragerea primului element (minimul)
{
	int r = s[0].v, i;
	for(i = 0; i < (*n) - 1; i++)
	{
		poz[s[i + 1].v]--;
		s[i] = s[i + 1];
		elem += 12;//1 comparare, 1 scadere, 1 incrementare, 4 indexari, 1 decrementare
				   //1 accesare tip struct.x, 2 adunari, 1 atribuire
	}
	poz[r] = (*n) - 1;
	(*n)--;
	elem += 10;//3 atribuiri, 1 comparare finala, 2 indexari, 1 accesare tip struct.x
			   //1 scadere, 1 decrementare, 1 scadere finala
	return r;
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
	int poz[n];//pozitia elem. in vectorul sortat
	Pair s[n];//vectorul sortat
	int i, size;

	for(i = 0; i < n; i++)
	{
		if(i != root)
		{
			d[i] = INT_MAX;
			p[i] = -1;
			s[i].v = i;
			s[i].cost = INT_MAX;
			poz[i] = i;
			elem += 12;//5 indexari, 2 accesari tip struct.x, 5 atribuiri
		}
		elem += 3;//1 comparare, 1 incrementare, 1 neegalitate
	}
	elem += 2;//1 initializare (i=0), 1 comparare finala

	//initializam separat datele din nodul de start
	d[root] = 0;
	s[root].v = root;
	s[root].cost = 0;
	poz[root] = root;
	size = n;
	sort(s, size, poz);

	List* adiac = g->adjLists;

	while(size != 0)//cat timp heap-ul nu e vid
	{
		int u = extractMin(s, &size, poz);
		List vec = adiac[u];
		while(vec != NULL)
		{
			int v = vec->data.v;
			if(poz[v] < size && vec->data.cost < d[v])
			{
				d[v] = vec->data.cost;
				p[v] = u;
				elem += 8;//3 atribuiri, 2 accesari tip '->', 3 accesari tip struct.x
						  //4 indexari
				s[poz[v]].cost = vec->data.cost;
				sort(s, size, poz);
			}
			vec = vec->next;
				
			elem += 12;//3 accesari tip '->', 2 accesari tip struct.x, 2 indexari,
					   //2 atribuiri, 2 comparari, 1 and
		}
		elem += 4;//2 atribuiri, 1 indexare, 1 neegalitate finala
	}
	elem += 1;//1 neegalitate finala

	elem += 14;//2 accesari tip '->', 2 accesari tip struct.x, 6 atribuiri, 4 indexari
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