#include "Graph.h"
#include "Interface.h"
#include <fstream>
#include<iostream>
#include <cstdlib>
using namespace std;

int main(){

    Interface user;
    user.execute("euler_cycle.txt");
    ///Graph g;
    ///g.load("three_shortest_paths.txt");
    ///g.print_Euler_path();
    ///cout<< g.is_connected("Dupnitsa") << endl;
    ///g.print_Euler_path();
    ///cout << g.is_connected("Dupnitsa") << endl;
    ///g.three_shortest_paths("Shumen", "Dupnitsa");
    /**
    vector<string> closed;
    closed.push_back("Burgas");
    closed.push_back("")
    g.three_shortest_paths(closed, "Shumen", "Dupnitsa");
    **/
    return 0;
}
