#include <iostream>
#include "../include/Graph.h"
#include <cstdlib>
#include <queue>

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

/**
bool cmp(const std::pair<int, std::vector<Node*>>& v1, const std::pair<int, std::vector<Node*>>& v2){
    if(v1.first == v2.first){
        if(v1.second.size() == v2.second.size()){
            for(int i = 0; i < v1.size(); i ++){
                if((long)v1[i] < (long)v2[i]){
                    return 1;
                }
            }
            return 0;
        }
        return v1.size() < v2.size();
    }
    return v1.first < v2.first;
}
**/

std::vector<std::pair< int, std::vector<Graph::Node*>>> Graph::three_shortest_paths (Node* from, Node* to) const{

    std::priority_queue<std::pair <int, std::vector<Node*>>,
                        std::vector<std::pair<int, std::vector<Node*>>>,
                        std::greater<std::pair<int, std::vector<Node*>>>> potential_paths;
    potential_paths.push({0, std::vector<Node*>({from})});
    std::unordered_map<Node*, int> used;
    std::vector<std::pair<int, std::vector<Node*>>> shortest_paths;

    while(!potential_paths.empty() && used[to] < 3){
        std::pair<int, std::vector<Node*>> curr_path = potential_paths.top();
        potential_paths.pop();
        Node* curr_vertex = curr_path.second.back();
        used[curr_vertex]++;
        if(used[curr_vertex] > 3){
            continue;
        }
        if(curr_vertex == to){
            shortest_paths.push_back(curr_path);
        }
        for(std::pair<int, Node*> next_vertex : (curr_vertex -> paths)){
            int new_cost = curr_path.first + next_vertex.first;
            curr_path.second.push_back(next_vertex.second);
            std::vector<Node*> new_potential_path = curr_path.second;
            curr_path.second.pop_back();
            potential_paths.push({new_cost, new_potential_path});
        }
    }
    return shortest_paths;
}

void Graph:: three_shortest_paths (const std::string from, const std::string to){
    std::vector<std::pair<int, std::vector<Node*>>> shortest_paths = three_shortest_paths(locations[from], locations[to]);
    if(shortest_paths.size() < 3){
        std::cout << "There aren't three shortest paths." << std::endl;
        return;
    }
    for(int i = 0; i < shortest_paths.size(); i++){
        for(int j = 0; j < shortest_paths[i].second.size(); j++){
            std::cout << shortest_paths[i].second[j]->name << " ";
        }
        std::cout << "; length: " << shortest_paths[i].first;
        std::cout << std::endl;
    }
}

std::vector<std::pair<int,std::vector<Graph::Node*>>> Graph::three_shortest_paths (std::vector<Node*> closed_locations,
                                                                                  Node* from,
                                                                                  Node* to) const{
    std::unordered_map<Node*, bool> temporary_closed;
    std::priority_queue<std::pair <int, std::vector<Node*>>,
                        std::vector<std::pair<int, std::vector<Node*>>>,
                        std::greater<std::pair<int, std::vector<Node*>>>> potential_paths;
    potential_paths.push({0, std::vector<Node*>({from})});
    std::unordered_map<Node*, int> used;
    std::vector<std::pair<int, std::vector<Node*>>> shortest_paths;


    for(int i = 0; i < closed_locations.size(); i++){
        temporary_closed[closed_locations[i]] = 1;
    }
    if(temporary_closed[from]){
        return shortest_paths;
    }

    while(!potential_paths.empty() && used[to] < 3){
        std::pair<int, std::vector<Node*>> curr_path = potential_paths.top();
        potential_paths.pop();
        Node* curr_vertex = curr_path.second.back();
        used[curr_vertex]++;

        if(used[curr_vertex] > 3){
            continue;
        }
        if(curr_vertex == to){
            shortest_paths.push_back(curr_path);
        }
        for(std::pair<int, Node*> next_vertex : (curr_vertex -> paths)){
            if(temporary_closed[next_vertex.second]){
                continue;
            }
            int new_cost = curr_path.first + next_vertex.first;
            curr_path.second.push_back(next_vertex.second);
            std::vector<Node*> new_potential_path = curr_path.second;
            curr_path.second.pop_back();
            potential_paths.push({new_cost, new_potential_path});
        }
    }
    return shortest_paths;
}

void Graph::three_shortest_paths (std::vector<std::string> closed_locations, const std::string from, const std::string to){

    std::vector<Node*> to_close;

    for(int i = 0; i < closed_locations.size(); i++){
        to_close.push_back(locations[closed_locations[i]]);
    }

    std::vector<std::pair<int, std::vector<Node*>>> shortest_paths = three_shortest_paths(to_close, locations[from], locations[to]);
    if(shortest_paths.size() < 3){
        std::cout << "There aren't three shortest paths." << std::endl;
        return;
    }

    for(int i = 0; i < shortest_paths.size(); i++){
        for(int j = 0; j < shortest_paths[i].second.size(); j++){
            std::cout << shortest_paths[i].second[j]->name << " ";
        }
        std::cout << "; length: " << shortest_paths[i].first;
        std::cout << std::endl;
    }

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

