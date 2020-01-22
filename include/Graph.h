#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <utility>
#include <map>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>
#include <cassert>

///directed graph
class Graph{
    private:
        struct Node{
            std::string name;
            int in_edges;
            std::vector<std::pair<int, Node*>> paths;

            Node (std::string _name): name(_name){
                in_edges = 0;
            }

            void add_path (int weight, Node *location){
                paths.push_back({weight, location});
                location->in_edges ++;
            }

            void pop_edge(){
                paths.back().second->in_edges--;
                paths.pop_back();
            }
        };

        std::unordered_map <std::string, Node*> locations;
        std::unordered_map<Node*, bool> closed;

        void load (std::istream& in);
        bool has_path (const Node* from, const Node* to, std::unordered_map<Node*, bool>& used);
        bool all_locations_used(std::unordered_map<Node*, bool> used);
        std::vector<std::pair<int, std::vector<Node*>>> three_shortest_paths (Node* from, Node* to); /// yen or epstein 2
        bool detect_cycle(Node* from, Node* curr, std::unordered_map<Node*, bool>& used);
        void is_connected (const Node* from, std::unordered_map<Node*, bool>& used);
        bool has_accessible_closed();
        bool has_Euler_cycle() const;
        std::pair<Node*, Node*> has_Euler_path () const;
        void find_Euler_cycle (Node* from, std::vector<Node*>& path, std::map<std::pair<Node*, Node*>, bool>& used_edges);
        void print_path(const std::vector<Node*>& path) const;

    public:
        Graph();
        void load (std:: string  file_name);
        void save (std:: string file_name);
        bool has_path (const std::string from, const std::string to); /// dfs 1
        std::vector<std::vector<std::string>> three_shortest_paths (const std::string from, const std::string to); /// epstein 2
        std::vector<std::vector<std::string>> three_shortest_paths_closed (std::vector<std::string> closed_locations, const std::string from, const std::string to); /// epstein 3
        bool detect_cycle(std::string from); ///  4
        void print_Euler_path(); /// 5
        bool is_connected (std::string from); ///has_path_to_each_other 6
        std::vector<std::pair<std::string, std::string>> find_dead_ends() const; /// 7

        ///Bonus
        bool exist_location(const std::string& check_location); /// existing location
        bool valid_location(const std::string& check_location); /// existing and not closed location
        void print_neighbours(std::string my_location);
        void print_closed_locations();
        void close_location(std::string location);
        void open_location(std::string location);


};

void split(const std::string& , std::vector <std::string>&, char ch);

#endif // GRAPH_H
