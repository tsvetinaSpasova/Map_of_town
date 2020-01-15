#include <iostream>
#include "../include/Graph.h"
#include <cstdlib>

Graph::Graph(){
}

Graph::Graph(std::string name){
    locations[name] = new Node (name);
}


void Graph::split(const std::string &text, std::vector<std::string> &words, char ch){
    std::string curr = "";
    for(int i = 0; i < text.size(); i ++){
        if(text[i] == ch){
            if(curr != ""){
                words.push_back(curr);
                curr = "";
            }
        }
        else{
            curr += text[i];
        }
    }
    if(curr != ""){
        words.push_back(curr);
    }
}

void Graph::load(std::istream& in) {

    std::string line;
    while(getline(in, line)){

        std::vector<std::string> words;

        split(line, words, ' ');

        if(locations.find(words[0]) == locations.end()){
            locations[words[0]] = new Node(words[0]);
        }

        for (int i = 1; i < words.size(); i += 2){
            if(locations.find(words[i]) == locations.end()){
                locations[words[i]] = new Node(words[i]);
            }

            int length = atoi(words[i + 1].c_str());
            locations[words[0]] -> add_path (length , locations[words[i]]);
        }
    }

}


void Graph::load (std::string  file_name){
    std::ifstream in(file_name);
    load(in);
    in.close();
}

/*
void Graph:: save(std:: ofstream& out){
    for(auto it: locations){

    }
}

void Graph:: save (std:: string file_name){
    std:: ofstream out(filename);
    save(out);
    out.close();
}
*/

bool Graph::has_path (const Node* from, const Node* to, std::unordered_map<Node*, bool>& used) const {

    if(from == to){
        return true;
    }

    for(std::pair<int, Node*> next : from->paths){

        if(used.find(next.second) == used.end()){
            used[next.second] = 1;

            if(has_path(next.second, to, used)){
                return true;
            }
        }
    }

    return false;
}


bool Graph::has_path(const std::string from, const std::string to){

    std::unordered_map<Node*, bool> used;
    used[locations[from]] = 1;
    return has_path(locations[from], locations[to], used);

}

///TODO
bool Graph::tree_shortest_paths (const Node* from, const Node* to) const{


}

bool Graph::tree_shortest_paths (std::list<Node*> closed_locations, const Node* from, const Node* to) const{

}

bool Graph::detect_cycle(Node* from, std::unordered_map<Node*, bool>& used) const{

    int num_of_paths_from = from -> paths.size();

    for(std::pair<int, Node*> next : from -> paths){
       if(used[next.second] == 0){

            used[next.second] = 1;

            if(detect_cycle(next.second, used)){
                return true;
            }
        }
        else{
            return true;
        }

    }

    return false;
}

bool Graph::detect_cycle(std::string from){

    std::unordered_map<Node*, bool> used;
    return detect_cycle(locations[from], used);

}


bool Graph::has_Euler_cycle() const{

    for(auto curr : locations){
        if((curr.second->in_edges) != (curr.second->paths).size()){
            return false;
        }
    }
    return true;
}

std::pair<Graph::Node*,Graph::Node*> Graph::has_Euler_path () const{

    Node* from = nullptr;
    Node* to = nullptr;
    int counter = 0;

    for(auto curr : locations){

        if(curr.second->in_edges - 1 == (curr.second->paths).size()){
            from = curr.second;
            counter++;
        }
        else if(curr.second->in_edges + 1 == (curr.second->paths).size()){
            to = curr.second;
            counter++;
        }
        else if((curr.second->in_edges) != (curr.second->paths).size()){
            return {nullptr,nullptr};
        }
    }

    if(counter == 2){
        return {from,to};
    }

    return {nullptr,nullptr};
}

void Graph::find_Euler_cycle (Node* vertex, std::vector<Node*>& path, std::map<std::pair<Node*,Node*>, bool>& used_edges){ ///dfs

    for(std::pair<int, Node*> curr_edge : vertex -> paths){
        if(used_edges[{vertex, curr_edge.second}] == 0){
            used_edges[{vertex, curr_edge.second}] = 1;
            find_Euler_cycle(curr_edge.second, path, used_edges);
        }
    }
    path.push_back(vertex);
}

void Graph::print_path(const std::vector<Node*>& path) const{

    for(int i = path.size() - 1; i > 0; i--){
        std::cout << path[i]->name << " -> ";
    }
    std::cout << path[0]->name << std::endl;
}

void Graph:: print_Euler_path(){

    std::vector<Node*> path;
    std::map<std::pair<Node*,Node*>, bool> used_edges;

    if(has_Euler_cycle()){
        find_Euler_cycle(locations.begin()->second, path, used_edges);
        print_path(path);
        return;
    }
    else if(has_Euler_path().first){
        std::pair<Node*, Node*> add_edge = has_Euler_path();
        add_edge.first->add_path(0, add_edge.second);
        find_Euler_cycle(locations.begin()->second, path, used_edges);

        for(int i = 0; i < path.size() - 1; i++){
            if(path[i+1] == add_edge.first && path[i] == add_edge.second){

                print_path(std::vector<Node*>(path.begin(), path.begin() + i + 1));
                if(i + 2 < path.size()){
                    std::cout<< " -> ";
                    print_path(std::vector<Node*>(path.begin() + i + 1, path.end()));
                }
            }
        }
        add_edge.first->pop_edge ();

        return;
    }
    else{
        std::cout << "There is not path that is passing from all the streets." << std::endl;
    }
}

bool Graph::all_locations_used(std::unordered_map<Node*, bool> used) const{

    for (auto& it : locations){
        if(used[it.second] == 0){
            return false;
        }
    }
    return true;
}

bool Graph::is_connected(const Node* from, std::unordered_map<Node*, bool>& used) const{

    int num_of_paths_from = from -> paths.size();

    if (all_locations_used(used)){
        return true;
    }

    for(std::pair<int, Node*> next : from -> paths){
       if(used[next.second] == 0){

            used[next.second] = 1;

            if(is_connected(next.second, used)){
                return true;
            }
        }
    }

    return false;
}

bool Graph::is_connected (std::string from){

    std::unordered_map<Node*, bool> used;
    used[locations[from]] = 1;
    return is_connected(locations[from], used);
}


std::vector<std::string> Graph::find_dead_ends() const{

    std::vector<std::string> dead_ends;

    for(auto& it : locations){
        if((it.second -> paths).size() == 0){
            dead_ends.push_back(it.first);
        }
    }
    return dead_ends;
}


