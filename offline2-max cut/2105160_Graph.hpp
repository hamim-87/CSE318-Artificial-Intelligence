#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <bits/stdc++.h>

using namespace std;


class Graph{
    public:
        int num_edges;
        int num_vetices;
        

    

        vector<vector<pair<long long,int>>> adj_list;
        vector<pair<pair<int,int>,long long>> edges;

        Graph() {}
        Graph(int n, int m){
            this->num_vetices = n;
            this->num_edges = m;

            adj_list.resize(n+1);
            edges.resize(m+1);
        }

        

        void add_edges(int u, int v, long long w){
            adj_list[u].push_back({w,v});
            adj_list[v].push_back({w,u});

            edges.push_back({{u,v},w});
        }

        int get_vertice_count(){ return num_vetices; }

        long long max_cut(vector<int> flip_color_assignments){
            long long cut =0;

            for(auto edge: edges){
                int _u = edge.first.first;
                int _v = edge.first.second;
                long long _w = edge.second;

                cut += (flip_color_assignments[_u] == flip_color_assignments[_v]? 0 : _w);

            }

            return cut;
        }

        long long max_cut(int idx,vector<int> flip_color_assignments,long long prev_cut){
            
            long long cut = prev_cut;

            for(auto item: adj_list[idx]){
                int _v = item.second;
                long long _w = item.first;

                cut +=(flip_color_assignments[_v] == flip_color_assignments[idx]? _w : -_w);
            }

            return cut;
        }

        pair<pair<int,int>,long long>  max_weighted_edges(){
            
            long long weignt = -1;
            pair<pair<int,int>,long long> max_edge;
            for(auto edge : edges){
                long long _w = edge.second;
                
                if(weignt<_w){
                    max_edge = edge;
                }
            }

            return max_edge;
        }

        
};



#endif