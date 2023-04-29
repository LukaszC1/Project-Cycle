/** @file */
#ifndef STRUCTURES_H  
#define STRUCTURES_H 

#include <vector> 
#include <unordered_map> 

typedef std::vector<std::vector<int>> cycles; // a vector of vectors used to store all of the found cycles
/** The structure that is used to represent every single node of the directed graph*/
struct node
{
	bool on_stack;						/**< Information whether a node is present on the stack.*/
	bool if_visited;					/**< Information whether a node was visited.*/
	std::vector<int> neighbours;		/**< Vector storing all the neigbours of a node.*/
};

/** The structure that is used to store the graph in the program*/
struct graph 
{
	std::unordered_map<int, node> nodes; /** A map consisting of a node number and a vector with its neigbours */
			//node     neigbours - with their state - visited or not visited
};

#endif  