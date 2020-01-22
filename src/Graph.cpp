#include <iostream>
#include "../include/Graph.h"
#include <cstdlib>
#include <queue>
#include <assert.h>

Graph::Graph(){
}

void split(const std::string &text, std::vector<std::string> &words, char ch){
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
            assert(length > 0 && "Street is with invalid length");
            locations[words[0]] -> add_path (length , locations[words[i]]);
        }
    }

}

void Graph::load (std::string  file_name){
    std::ifstream in(file_name);
    load(in);
    in.close();
}

bool Graph::has_path (const Node* from, const Node* to, std::unordered_map<Node*, bool>& used){
    if(from == to){
        return true;
    }
    for(std::pair<int, Node*> next : from->paths){
        if(closed[next.second] == 1){
            continue;
        }
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

std::vector<std::pair<int, std::vector<Graph::Node*>>> Graph::three_shortest_paths (Node* from, Node* to){

    std::priority_queue<std::pair <int, std::vector<Node*>>,
                        std::vector<std::pair<int, std::vector<Node*>>>,
                        std::greater<std::pair<int, std::vector<Node*>>>> potential_paths;
    potential_paths.push({0, std::vector<Node*>({from})});
    std::unordered_map<Node*, int> used;
    std::vector<std::pair<int, std::vector<Node*>>> shortest_paths;

    while(!potential_paths.empty() && used[to] < 3){
        std::pair<int, std::vector<Node*>> curr_path = potential_paths.top();
        potential_paths.pop();
        Node* curr_Node = curr_path.second.back();
        used[curr_Node]++;
        if(used[curr_Node] > 3){
            continue;
        }
        if(curr_Node == to){
            shortest_paths.push_back(curr_path);
        }
        for(std::pair<int, Node*> next_Node : (curr_Node -> paths)){
            if(closed[next_Node.second] == 1){
                continue;
            }
            int new_cost = curr_path.first + next_Node.first;
            curr_path.second.push_back(next_Node.second);
            std::vector<Node*> new_potential_path = curr_path.second;
            curr_path.second.pop_back();
            potential_paths.push({new_cost, new_potential_path});
        }
    }

    return shortest_paths;
}

std::vector<std::vector<std::string>> Graph::three_shortest_paths (const std::string from, const std::string to){
    std::vector<std::pair<int, std::vector<Node*>>> shortest_paths = three_shortest_paths(locations[from], locations[to]);
    std::vector<std::vector<std::string>> paths(shortest_paths.size());
    for(int i = 0; i < shortest_paths.size(); i++){
        for(int j = 0; j < shortest_paths[i].second.size(); j++){
            paths[i].push_back(shortest_paths[i].second[j]->name);
        }
    }
    return paths;
}

std::vector<std::vector<std::string>> Graph::three_shortest_paths_closed (std::vector<std::string> closed_locations, const std::string from, const std::string to){

    for(std::string curr_closed : closed_locations){
       close_location(curr_closed);
    }
    std::vector<std::vector<std::string>> shortest_paths = three_shortest_paths(from, to);
    for(std::string curr_closed : closed_locations){
        open_location(curr_closed);
    }
    return shortest_paths;
}

bool Graph::detect_cycle(Node* from, Node* curr, std::unordered_map<Node*, bool>& used){
    int num_of_paths_from = curr -> paths.size();

    for(std::pair<int, Node*> next : curr -> paths){
        if(closed[next.second] == 1){
            continue;
        }
        if(used[next.second] == 0){
            used[next.second] = 1;
            if(detect_cycle(from, next.second, used)){
                return true;
            }
        }
        else if(from == next.second){
            return true;
        }
    }
    return false;
}

bool Graph::detect_cycle(std::string from){

    std::unordered_map<Node*, bool> used;
    return detect_cycle(locations[from], locations[from], used);

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

void Graph::find_Euler_cycle (Node* from, std::vector<Node*>& path, std::map<std::pair<Node*,Node*>, bool>& used_edges){ ///dfs

    for(std::pair<int, Node*> curr_edge : from -> paths){
        if(used_edges[{from, curr_edge.second}] == 0){
            used_edges[{from, curr_edge.second}] = 1;
            find_Euler_cycle(curr_edge.second, path, used_edges);
        }
    }
    path.push_back(from);
}

void Graph::print_path(const std::vector<Node*>& path) const{

    for(int i = path.size() - 1; i > 0; i--){
        std::cout << path[i]->name << " -> ";
    }
    std::cout << path[0]->name << std::endl;
}

bool Graph::has_accessible_closed(){
    for(auto curr : closed){
        if(curr.second && curr.first->in_edges + curr.first->paths.size() > 0)
            return true;
    }
    return false;
}

void Graph:: print_Euler_path(){

    std::vector<Node*> path;
    std::map<std::pair<Node*,Node*>, bool> used_edges;

    if(has_accessible_closed()){

        std::cout << "A tour doesn't exist." << std::endl;
        return;
    }

    if(has_Euler_cycle()){
        find_Euler_cycle(locations.begin()->second, path, used_edges);
        print_path(path);
        return;
    }
    if(has_Euler_path().first){
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
    std::cout << "A tour doesn't exist." << std::endl;
}

bool Graph::all_locations_used(std::unordered_map<Node*, bool> used){

    for (auto& it : locations){
        if(used[it.second] == 0 && closed[it.second] == 0){
            return false;
        }
    }
    return true;
}

void Graph::is_connected(const Node* from, std::unordered_map<Node*, bool>& used){

    for(std::pair<int, Node*> next : from -> paths){

        if(closed[next.second] == 1){
            continue;
        }
        if(used[next.second] == 0){
            used[next.second] = 1;
            is_connected(next.second, used);
        }
    }
}

bool Graph::is_connected (std::string from){

    std::unordered_map<Node*, bool> used;
    used[locations[from]] = 1;
    is_connected(locations[from], used);
    return all_locations_used(used);
}

std::vector<std::pair<std::string, std::string>> Graph::find_dead_ends() const{

    std::vector<std::pair<std::string, std::string>> dead_ends;

    for(auto& it : locations){
        for(std::pair<int, Node*> nb : it.second->paths){
            if(nb.second->paths.size() == 0){
                dead_ends.push_back({it.first, nb.second->name});
            }
        }
    }
    return dead_ends;
}

///Bonus
bool Graph::exist_location(const std::string& check_location){
    return locations.find(check_location) != locations.end();
}

bool Graph::valid_location(const std::string& check_location){
    return exist_location(check_location) && !closed[locations[check_location]];
}

void Graph::close_location(std::string location){
    closed[locations[location]] = 1;
}

void Graph::open_location(std::string location){
    closed[locations[location]] = 0;
}

void Graph::print_neighbours(std::string my_location){
    Node* curr_location = locations[my_location];
    std::cout << " | ";
    for(std::pair<int, Node*> neighbour : curr_location -> paths){
        if(closed[neighbour.second] == 1){
            continue;
        }
        std::cout << neighbour.second -> name << " | ";
    }
    std::cout << std::endl;
}

void Graph::print_closed_locations(){
    std::cout << " | ";
    for(auto curr : closed){
        if(curr.second == 1){
            std::cout << curr.first -> name << " | ";
        }
    }
    std::cout << std::endl;
}
