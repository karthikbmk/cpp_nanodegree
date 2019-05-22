#include "route_model.h"
#include <iostream>
#include <vector>
#include <limits>

using std::vector;
using std::numeric_limits;


RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
    vector <Model::Node> nodes = this->Nodes();
    int i = 0;
    for(Model::Node node : nodes){
        RouteModel::Node rm_node = RouteModel::Node(i, this, node);
        m_Nodes.push_back(rm_node);
        i+=1;
    }

}

void RouteModel::CreateNodeToRoadHashMap(){
    for(Road road : Roads()){
        if (road.type != Model::Road::Type::Footway){
            for (int node_idx : Ways()[road.way].nodes){
                 if (node_to_road.find(node_idx) == node_to_road.end()){
                    node_to_road[node_idx] = vector <const Model::Road*> ();
                }
                node_to_road[node_idx].push_back(&road);
            }
        }
    }
}

RouteModel::Node* RouteModel::Node::FindNeighbor(vector<int> node_indices){
    float closest_dist = numeric_limits<float>::max();
    RouteModel::Node *closest_node = nullptr;
    for(int node_idx : node_indices){
        RouteModel::Node tmp_node = parent_model->SNodes()[node_idx];
        bool is_visited = tmp_node.visited;
        float dist = RouteModel::Node::distance(tmp_node);
        if (!is_visited && dist > 0){
            if (dist < closest_dist){
                closest_dist = dist;
                closest_node = &tmp_node;
            }
        }
    }
    return closest_node;
}

void RouteModel::Node::FindNeighbors(){
    vector<const Model::Road*> road_ptrs = parent_model->node_to_road[this->index];
    for(const Road* road_ptr : road_ptrs){
        vector <int> nodes = parent_model->Ways()[road_ptr->way].nodes;
        RouteModel::Node *closest_node = FindNeighbor(nodes);
        if (closest_node != nullptr){
            this->neighbors.push_back(closest_node);
        }
    }
}

RouteModel::Node & RouteModel::FindClosestNode(float x, float y){
    RouteModel::Node user_node;
    user_node.x = x;
    user_node.y = y;

    float min_dist = numeric_limits<float>::max();
    int closest_idx = -1;

    for (Road road : Roads()){
        if (road.type != Model::Road::Type::Footway){
            for (int node_idx : Ways()[road.way].nodes){
                float tmp_dist = user_node.distance(SNodes()[node_idx]);
                if (tmp_dist  < min_dist){
                    min_dist = tmp_dist;
                    closest_idx = node_idx;
                }

            }
        }
    }
    return SNodes()[closest_idx];

}
