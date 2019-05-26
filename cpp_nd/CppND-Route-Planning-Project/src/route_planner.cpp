#include "route_planner.h"
#include <algorithm>
#include <vector>

using std::vector;
using std::cout;
using std::sort;

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    start_node  = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);


}

vector <RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node){
    vector <RouteModel::Node>  path_found = {};

    distance = 0.0f;
    
    while(current_node->parent != nullptr){
        path_found.push_back(*current_node);
        
        float tmp_dist = current_node->distance(*(current_node->parent));
        distance += tmp_dist;

        current_node = current_node->parent;
    }

    path_found.push_back(*current_node);
    distance *= m_Model.MetricScale();
    return path_found;
}


void RoutePlanner::AStarSearch(){
    start_node->visited = true;
    open_list.push_back(start_node);
    RouteModel::Node *current_node = nullptr;
    
    while( open_list.size() > 0 ){
        current_node = NextNode();
        if (current_node->distance(*end_node) == 0){
            m_Model.path = ConstructFinalPath(current_node);
            return;
        }
        else{
            AddNeighbors(current_node);
        }
    }
}


float RoutePlanner::CalculateHValue(const RouteModel::Node * cur_node){
    float h_val;
    h_val = cur_node->distance(*end_node);
    return h_val;
}

RouteModel::Node * RoutePlanner::NextNode(){
    sort(open_list.begin(), open_list.end(),[] (const auto &l1, const auto &l2){
        return l1->h_value + l1->g_value < l2->h_value + l2->g_value;
    });

    RouteModel::Node * nearest_next = open_list.front();
    open_list.erase(open_list.begin());
    return nearest_next;
}


void RoutePlanner::AddNeighbors(RouteModel::Node * current_node){
    current_node->FindNeighbors();
    for(RouteModel::Node * neighbor : current_node->neighbors){
        neighbor->parent = current_node;
        neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
        neighbor->h_value = CalculateHValue(neighbor);
        open_list.push_back(neighbor);
        
        neighbor->visited = true;
    }
}
