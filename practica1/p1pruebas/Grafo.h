#include <iostream>
#include "Edge.h"

class Grafo{
private:
	int numVertices;
	int numAristas;
	int aristas_anyadidas;
	Edge* edges;
public:
	Grafo(int numV,int numA){
		numVertices=numV;
		numAristas=numA;
		aristas_anyadidas=0;
		edges=new Edge[numA];
	}
	int nVertices(){
		return numVertices;
	}
	int nAristas(){
		return numAristas;
	}

	void addEdge(int src,int dst){
		edges[aristas_anyadidas]=Edge(src,dst);
		aristas_anyadidas++;
	}

	Edge* aristas(){
		return edges;
	} 
};