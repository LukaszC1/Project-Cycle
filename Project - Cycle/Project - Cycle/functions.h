/** @file */
#ifndef FUNCTIONS_H  
#define FUNCTIONS_H 

#include "structures.h"

/** 
*The function for reading edges of a directed graph into a vector containing edges
*@param file_name of file to read the edges of a directed graph from
*@return vector containing all the edges
*/
std::vector<int> reading_from_file(const std::string& file_name);

/** 
*The function for creating an adjacency list of a graph with given edges
*@param edges vector with all the edges read from a file
*@return graph with the given edges
*/
graph creating_graph (const std::vector<int> &edges);

/** 
*The void function for printing the graph to the standard output
*@param g vector with all the edges read from a file
*/
void print_graph(const graph &g);

/**
*This function performs the DFS algorithm
*@param g adjacency list - graph
*@param starting_node starting node number
*@param cycle a stack that will store the current found cycle
*@param result a vector that will contain all of the found cycles
*/
void DFS(graph& g, int starting_node, std::stack<int> &cycle,cycles &result);

/**
*This function is used recursively inside the DFS function to explore the neighbours of a given node
*@param g adjacency list - graph
*@param starting_node starting node number
*@param cycle a stack that will store the current found cycle
*@param result a vector that will contain all of the found cycles
*/
void DFS_visiting_neighbours(graph& g, int starting_node,std::stack<int> &cycle,cycles &result);

/**
*This function saves all the found cycles in a file
*@param result a vector of vectors containing all of the found cycles
*@param file_name a name of a file to save the cycles to
*/
void print_to_file(const cycles& result, std::string const &file_name);

/**
*This function test if the arguments passed to the main are correctr
*@param argc number of passed arguments 
*@param argv all the passed arguments
* @return true or false 
*/
bool check_parameters(int argc, char* argv[]);

/**
*This function assigns correct file_names for reading and printing 
*@param file_read a name of a file to read from
*@param file_write a name of a file to print to
*@param argc number of passed arguments 
*@param argv all the passed arguments

*/
void assign_parameters(std::string & file_read, std::string& file_write,int argc, char* argv[]);
#endif  


