//Arista

class Edge{
private:	
	int src;
	int dst;
public:
	Edge(){
		src=-1;
		dst=-1;
	}
	Edge(int source,int dest){
		src=source;
		dst=dest;	
	}
	int source(){
		return src;
	}

	int dest(){
		return dst;
	}
	void set_values(int src,int dst){
		this->src=src;
		this->dst=dst;
	}
};