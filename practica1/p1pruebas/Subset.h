//Subset para usar
//la estructura de datos
//union-find

class Subset{
private:	
	int padre;
	int ranking;
public:
	int parent(){
		return padre;
	}

	int rank(){
		return ranking;
	}

	void set_parent(int parent){
		padre=parent;
	}

	void add_rank(){
		ranking=ranking+1;
	}

	void set_rank(int rank){
		ranking=rank;
	}
};