//#include "Edge.h"
#include "Subset.h"
#include "Grafo.h"
#include <random>
#include <iostream>
#include <fstream>

int find(Subset subsets[], int i,bool show){
	if(show){
		std::cout<<subsets[i].parent();
	}
	if(subsets[i].parent()!=i){
		subsets[i].set_parent(find(subsets, subsets[i].parent(),false));	
	} 
    return subsets[i].parent();
}

void contract(Subset subsets[],int s1,int s2){
	int raiz_s1 = find(subsets, s1,false); 
    int raiz_s2 = find(subsets, s2,false); 
  
  	//union by rank. Se une el subset de menor
  	//ranking a la raiz del subset con mayor ranking
    if(subsets[raiz_s1].rank()<subsets[raiz_s2].rank()){
    	subsets[raiz_s1].set_parent(raiz_s2);
    } 
    else if (subsets[raiz_s1].rank()>subsets[raiz_s2].rank()){
    	subsets[raiz_s2].set_parent(raiz_s1);
    } 
    // en caso de ranking igual, hacer uno de
    //ellos raiz e incrementar su ranking en 1
    else{ 
        subsets[raiz_s2].set_parent(raiz_s1);
        subsets[raiz_s1].add_rank(); 
    } 
}

int kargerMinCut(Grafo graph){
	int v=graph.nVertices();
    int a=graph.nAristas();
    Edge *aristas = graph.aristas();
	
	//inicializar los subsets de 
    //todos los vertices
    Subset *subsets = new Subset[v];
	for (int i =0; i<v; ++i){ 
        subsets[i].set_parent(i); 
        subsets[i].set_rank(0); 
    }

	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<uint32_t> distAristas(0,graph.nAristas()-1);

    while(v>2){
    	//seleccionar arista aleatoria
    	uint32_t index_arista = distAristas(mt);
    	//buscar vertices en los subsets
    	int set1=find(subsets,aristas[index_arista].source(),false);
    	int set2=find(subsets,aristas[index_arista].dest(),false);
    	if(set1!=set2){
    		v--;
    		contract(subsets,set1,set2);
    	}
    } 

    int aristas_finales = 0; 
    //std::cout<<a<<std::endl;
    for(int i=0; i<a;i++){ 
        int set1 = find(subsets,aristas[i].source(),false); 
        std::cout<<std::endl;
        int set2 = find(subsets,aristas[i].dest(),false); 
        std::cout<<std::endl;
        if (set1!= set2){ 
          aristas_finales++; 
    	}
    } 
  	// for (int i = 0; i < graph.nVertices(); ++i){
  	// 	std::cout<<subsets[i]<<std::endl;
  	// 	// for (int j = 0; j < count; ++i)
  	// 	// {
  	// 	// 	/* code */
  	// 	// }
  	// 	std::cout<<std::endl;
  	// }
  	return aristas_finales;
}

void generarResultados(Grafo graph,int numPruebas,int pruebas[],int& minCut,int& maxCut,
	std::ofstream& g,bool show_subsets){
	for (int i = 0; i < numPruebas; ++i){
    	pruebas[i]=kargerMinCut(graph);
    	if(i==0){
    		minCut=pruebas[i];
    		maxCut=pruebas[i];
    	}
    	else{
    		if(pruebas[i]<minCut){minCut=pruebas[i];}
    		if(pruebas[i]>maxCut){maxCut=pruebas[i];}	
    	}
    }
    std::cout<<"El minimo corte es "<<minCut<<std::endl;
    std::cout<<"El maximo corte es "<<maxCut<<std::endl;
    std::cout<<std::endl;
    for (int i = 0; i < numPruebas; ++i)
    {
    	std::string to_plot=std::to_string(i)+"  "+std::to_string(pruebas[i]);
		g<<to_plot<<std::endl;
    }
    if(show_subsets){
    	std::cout<<"Hay subsets"<<std::endl;
    }

}

int main(){
	int V = 4;  // Number of vertices in graph 
    int E = 5;  // Number of edges in graph 
    int numPruebas=1;
    int pruebas[numPruebas];
    int minCut,maxCut;
    bool show_subsets=false;
    std::ofstream g;
    g.open("results.txt");

    Grafo graph(V,E);
    // add edge 0-1 
    graph.addEdge(0,1);
    
    // add edge 0-2 
    graph.addEdge(0,2);
    
    // add edge 0-3 
    graph.addEdge(0,3);
    
    // add edge 1-3 
    graph.addEdge(1,3);
    
    // add edge 2-3 
    graph.addEdge(2,3);
    generarResultados(graph,numPruebas,pruebas,minCut,maxCut,g,show_subsets);
}
