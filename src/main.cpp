#include "Graph.h"
#include <fstream>
#include<iostream>
#include <cstdlib>
using namespace std;

int main(){


    Graph g;
    g.load("tree_shortest_paths.txt");
    ///cout<< g.is_connected("Dupnitsa") << endl;
    ///g.print_Euler_path();
    ///cout << g.is_connected("Dupnitsa") << endl;
    ///g.tree_shortest_paths("Shumen", "Dupnitsa");
    vector<string> closed;
    closed.push_back("Pernik");
    ///closed.push_back("")
    g.tree_shortest_paths(closed, "Shumen", "Dupnitsa");


    return 0;
}
