/** @file */
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <unordered_map>

#include "functions.h" 
#include "structures.h"

int main(int argc, char* argv[])
{
	if (argc == 0 || argv[1] == "-h") // printing a short manual in case the program is run with no parameters or "-h" parameter
	{
		std::cout << "The program is run with the following commands: " << std::endl
				<< "-g file_name with input file name" << std::endl
				<< "-c file_name with output file name";
		return 0;
	}

	std::string nazwapliku_odczyt, nazwapliku_zapis;
	if (check_parameters(argc,argv))  // if the parameters are correct the program will run 
	{
		std::string nazwapliku_odczyt, nazwapliku_zapis;
		// assigning correct names to read and print from
		assign_parameters(nazwapliku_odczyt, nazwapliku_zapis,argc,argv);
		// declaring a data structure
		graph graph1;
		// creating a vector with edges using two functions - one to read from the file and the second one to create the graph
		std::vector<int> edges;
		edges = reading_from_file(nazwapliku_odczyt);
		if (edges.size()) // this part of code can only be run if the input file is not empty
		{
			//creating a graph using a creating_graph function
			graph1 = creating_graph(edges);
			// printing the graph to the standard output using a function
			print_graph(graph1);
			// running the DFS on a given graph - with the first key value in the unordered map
			std::stack<int> cycle;
			cycles result;
			int starting_node = graph1.nodes.begin()->first;
			DFS(graph1, starting_node, cycle, result);
			print_to_file(result, nazwapliku_zapis);
		}
		else
			std::cout << "The input file doesn`t contain any numbers!";
	}
	else
	std::cout << "The parameters are incorrect!";

	return 0;
}
