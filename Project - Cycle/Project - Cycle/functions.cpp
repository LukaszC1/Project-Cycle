/** @file */
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <stack>

#include "functions.h" 
#include "structures.h"

std::vector<int> reading_from_file(const std::string& file_name)
{
	std::ifstream file(file_name);
	int a;                              // a variable that is used to read integers from each word
	std::string word;
	std::string line;
	std::vector<int> numbers;
	if (file)
	{
		while (getline(file, line))
		{
			std::stringstream ss(line);
			while (ss >> word)
			{
				if (std::stringstream(word) >> a)
				{
					numbers.push_back(a); // all the edges stored in a vector
				}
			}
		}
	}
	file.close();
	return numbers;
}

graph creating_graph(const std::vector<int>  &edges)
{
		graph g;
		for (size_t j = 0; j < edges.size() - 1; j += 2)
		{		//key == node            neighbour of a node 
			g.nodes[edges[j]].neighbours.push_back(edges[j + 1]);
			g.nodes[edges[j + 1]];							// adding the end node as a key to the map
			g.nodes[edges[j]].if_visited = false;			// setting the nodes to be in a state "unvisited" 
			g.nodes[edges[j + 1]].if_visited = false;
		}
		return g;
}

void print_graph(const graph & g )
{
	for (auto n : g.nodes)                           // for each node
	{
		std::cout << "Node: " << n.first;            // print the key
		std::cout << std::endl;
		std::cout << "neigbours: ";
		for (auto neighbours : n.second.neighbours)  // print all the neigbours
		{
			std::cout << neighbours << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}
void DFS_visiting_neighbours(graph &g, int starting_node,std::stack<int> &cycle,cycles &result)	 // this function can explore all neighbour of a given node
{
	g.nodes[starting_node].if_visited = true;	// setting the state of current node as visited
	
	for (auto neighbour : g.nodes[starting_node].neighbours) // for each neighbour 
	{		
		if (!g.nodes[neighbour].if_visited)
			//if not - run the DFS recursively for each child node - stopping condition 
		{
			g.nodes[starting_node].on_stack = true;					// marking each node as present on the stack
			cycle.push(starting_node);
			DFS_visiting_neighbours(g, neighbour, cycle, result);   // recursive step
		}
		else if (g.nodes[neighbour].on_stack)						// there is a cycle only if this node is present on the stack
		{
				cycle.push(starting_node);	
				g.nodes[starting_node].on_stack = true;				
				
				std::vector<int> cycle_found;
				while (cycle.top() != neighbour)					// while loop breaks when it reaches the final node that creates the cycle
				{
					cycle_found.push_back(cycle.top());
					g.nodes[cycle.top()].on_stack = false;
					cycle.pop();
				}
				cycle_found.push_back(cycle.top());					// adding the last element of the cycle
				g.nodes[cycle.top()].on_stack = false;
				cycle.pop();
				
				result.push_back(cycle_found);
		}
	}
}

void DFS(graph &g, int starting_node, std::stack<int> &cycle, cycles &result)						
{
		for (auto node : g.nodes)										//starting the search for every node - key in the unordered map
		{
			if (!node.second.if_visited)
			{
				node.second.if_visited = true;							// mark this node  as visited
				DFS_visiting_neighbours(g, node.first,cycle,result);	//using DFS_visiting_neigbours function
			}
		}
}

void print_to_file(const cycles& result, std::string const &file_name)
{
		std::ofstream file(file_name);
		size_t counter = 1;
		if (file)
		{
			if (result.size() == 0)					//if the vector of vectors is empty then it means that there are no cycles
			{
				file << "There are no cycles! ";
				return;
			}
			for (auto vector : result)
			{
				file << vector[vector.size() - 1]; // the last element of a vector is always the starting and ending node of a cycle
				file << " <- ";
				for (auto element : vector)
				{
					file << element;
					if (counter < vector.size()) // a condition so that the "->" will not be printed after the last node in the cycle
						file << " <- ";

					counter++;
				}
				file << std::endl;
				counter = 1;					   // resetting the counter
			}
			file.close();
		}
}

bool check_parameters(int argc, char* argv[])	  // checking the number of arguments and if the second and fourth arguments are strings - they are used as file_names 
{
	int counter = 0;
	if (argc != 5)								  // the number of parameters has to be equal to exact 5
		return false;
	else
	{
		for (int i = 1; i < argc - 1; ++i) // reading proper file_name to a proper argument
		{
			std::string arg = argv[i];
			
			if (arg == "-g")
			{
				std::ifstream file(argv[i + 1]);
				if (file.is_open())		// if it was opened increment counter and close it else it failed so it wasnt opened
				{
					counter++;
					file.close();
				}
				else
					std::cout << "File: " << argv[i + 1] << " not found!" << std::endl;
			}
			if (arg == "-c")
			{		
				counter++;
				
			}
		}
			if (counter == 2)		  // both arguments -g and -c have to be correct for the program to work
				return true;
			else
				return false;
	}
}

void assign_parameters(std::string & file_read, std::string & file_write, int argc, char* argv[])
{

	for (int i = 1; i < argc - 1; ++i) // reading proper file_name to a proper argument
	{
		std::string arg = argv[i];
		if (arg == "-g")
		{
			file_read = argv[i + 1];
		}
		if (arg == "-c")
		{
			file_write = argv[i + 1];
		}
	}

}