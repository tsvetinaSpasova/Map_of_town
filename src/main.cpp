#include "Graph.h"
#include <fstream>
#include<iostream>
#include <cstdlib>
using namespace std;

int main(){


    Graph g;
    g.load("input.txt");
    cout<< g.is_connected("tsvetina") << endl;
    g.print_Euler_path();
    cout << g.is_connected("tsvetina") << endl;


    return 0;
}
