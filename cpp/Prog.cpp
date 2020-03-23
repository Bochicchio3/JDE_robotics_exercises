// In double-subscripted arrays the first subscript is often called the row subscript, and the
///		second one is called the column subscript.
// If double-subscripted array b is initialized as b[m][n] then it is called an m-by-n array.
// You see that each group of numbers initialize the rows respectively.
// Undefined elements are set to 0.
// When using Multidimentional Arrays in function prototypes the 2nd, 3rd,... subscripts 
//		must be mentioned in the function prototype.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#define INT_MAX 10000000

using namespace std;

class Node;
class Edge;

void DijkstrasTest();
void PrintArray (char [][6]); // The 2nd subscript must be mentioned.void Dijkstras();
vector<Node*>* AdjacentRemainingNodes(Node* node);
Node* ExtractSmallest(vector<Node*>& nodes);
int Distance(Node* node1, Node* node2);
bool Contains(vector<Node*>& nodes, Node* node);
void PrintShortestRouteTo(Node* destination);
void Dijkstras();


vector<Node*> nodes;
vector<Edge*> edges;


class Node
{
public:
	Node(char id, int x, int y) 
		: id(id), previous(NULL), distanceFromStart(INT_MAX), x(x), y(y)
	{
		nodes.push_back(this);
	}
public:
	char id;
	int x;
	int y;
	Node* previous;
	int distanceFromStart;
};

class Edge
{
public:
	Edge(Node* node1, Node* node2, int distance) 
		: node1(node1), node2(node2), distance(distance)
	{
		edges.push_back(this);
	}

	bool Connects(Node* node1, Node* node2)
	{
		return (
			(node1 == this->node1 &&
			node2 == this->node2) ||
			(node1 == this->node2 && 
			node2 == this->node1));
	}
public:
	Node* node1;
	Node* node2;
	int distance;
};



int main()
{
	int counter= 68;
	
	// vector<Node*>* Graph = new vector<Node*>();
	char x;
	char Array1[6][6];

    ifstream inFile;
    
    inFile.open("test3.txt");

   if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
	Node* tmp= NULL;
	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < 6; j++)
		{
			inFile >> x;

			// if (x!= '#' or x !='.')
			// {
			// cerr << "Cannot create file!" << endl;
			// exit(1);
			// }
			
			Array1[i][j]=x;
			if (x=='.')
			{
				counter++;
				tmp->x=i;
				tmp->y=j;
				tmp->id= char(counter);
				// Graph->push_back(tmp);

			}
		
		}
		
	}
    
    inFile.close();


	PrintArray(Array1);


	return 0;
}


// vector<tuple<int, int, int> > v; 

	// for (size_t i = 0; i < 6; i++)
	// {
	// if (Array1[0][i]=='.')
	// 	{
	// 	A
	// 	v.push_back(make_tuple(0,i,1));
	// 	}
	// }
 

    // for (int i = 0; i < v.size(); i++)  
    //     cout << get<0>(v[i]) << " " 
    //          << get<1>(v[i]) << " " 
    //          << get<2>(v[i]) << "\n"; 





void PrintArray (char ArrayName [][6])
{
	for (int i = 0 ; i < 6 ; i++)
	{
		for (int j = 0 ; j < 6 ; j++)
			cout << setw(4) << setiosflags (ios::left) << ArrayName[i][j];
		cout << endl;
	}
	cout << endl;
}



void DijkstrasTest()
{
	// Node* a = new Node('a');
	// Node* a = new Node('b');
	// Node* c = new Node('c');
	// Node* d = new Node('d');
	// Node* e = new Node('e');
	// Node* f = new Node('f');
	// Node* g = new Node('g');

	// Edge* e1 = new Edge(a, c, 1);
	// Edge* e2 = new Edge(a, d, 1);
	// Edge* e3 = new Edge(b, c, 1);
	// Edge* e4 = new Edge(c, d, 1);
	// Edge* e5 = new Edge(b, f, 1);
	// Edge* e6 = new Edge(c, e, 1);
	// Edge* e7 = new Edge(e, f, 1);
	// Edge* e8 = new Edge(d, g, 1);
	// Edge* e9 = new Edge(g, f, 1);

	// a->distanceFromStart = 0; // set start node
	Dijkstras();

	// PrintShortestRouteTo(f);
}

///////////////////

void Dijkstras()
{
	while (nodes.size() > 0)
	{
		Node* smallest = ExtractSmallest(nodes);
		vector<Node*>* adjacentNodes = 
			AdjacentRemainingNodes(smallest);

		const int size = adjacentNodes->size();
		for (int i=0; i<size; ++i)
		{
			Node* adjacent = adjacentNodes->at(i);
			int distance = Distance(smallest, adjacent) +
				smallest->distanceFromStart;
			
			if (distance < adjacent->distanceFromStart)
			{
				adjacent->distanceFromStart = distance;
				adjacent->previous = smallest;
			}
		}
		delete adjacentNodes;
	}
}

// Find the node with the smallest distance,
// remove it, and return it.

Node* ExtractSmallest(vector<Node*>& nodes)
{
	int size = nodes.size();
	if (size == 0) return NULL;
	int smallestPosition = 0;
	Node* smallest = nodes.at(0);
	for (int i=1; i<size; ++i)
	{
		Node* current = nodes.at(i);
		if (current->distanceFromStart <
			smallest->distanceFromStart)
		{
			smallest = current;
			smallestPosition = i;
		}
	}
	nodes.erase(nodes.begin() + smallestPosition);
	return smallest;
}

// Return all nodes adjacent to 'node' which are still
// in the 'nodes' collection.

vector<Node*>* AdjacentRemainingNodes(Node* node)
{
	vector<Node*>* adjacentNodes = new vector<Node*>();

	const int size = edges.size();
	for(int i=0; i<size; ++i)
	{
		Edge* edge = edges.at(i);
		Node* adjacent = NULL;
		if (edge->node1 == node)
		{
			adjacent = edge->node2;
		}
		else if (edge->node2 == node)
		{
			adjacent = edge->node1;
		}


		if (adjacent && Contains(nodes, adjacent))
		{
			adjacentNodes->push_back(adjacent);
		}
	}
	return adjacentNodes;
}

// Return distance between two connected nodes
int Distance(Node* node1, Node* node2)
{
	const int size = edges.size();
	for(int i=0; i<size; ++i)
	{
		Edge* edge = edges.at(i);
		if (edge->Connects(node1, node2))
		{
			return edge->distance;
		}
	}
	return -1; // should never happen
}

// Does the 'nodes' vector contain 'node'
bool Contains(vector<Node*>& nodes, Node* node)
{
	const int size = nodes.size();
	for(int i=0; i<size; ++i)
	{
		if (node == nodes.at(i))
		{
			return true;
		}
	}
	return false;
}

///////////////////

void PrintShortestRouteTo(Node* destination)
{
	Node* previous = destination;
	cout << "Distance from start: " 
		<< destination->distanceFromStart << endl;
	while (previous)
	{
		cout << previous->id << " ";
		previous = previous->previous;
	}
	cout << endl;
}