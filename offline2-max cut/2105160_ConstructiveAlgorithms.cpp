
#include "2105160_ConstructiveAlgorithms.hpp"

ConstructiveAlgorithms :: ConstructiveAlgorithms(Graph _graph){
    this->graph = _graph;
}



Greedy1 :: Greedy1(Graph _graph) : ConstructiveAlgorithms(_graph) {
    
}

vector<int> Greedy1 :: assign() {

    auto largest_weight_edge = this->graph.max_weighted_edges();

    

    int n = this->graph.get_vertice_count();

    vector<int> assignments(n+1,-1);

    int u = largest_weight_edge.first.first;
    int v = largest_weight_edge.first.second;
    int w = largest_weight_edge.second;

    assignments[u] = 0;
    assignments[v] = 1;

    for(int i =0;i<n;i++){

        if(assignments[i] != -1) continue;

        long long wX = 0;
        long long wY = 0;

        for(auto it: this->graph.adj_list[i]){

            int _v = it.second;
            long long _w = it.first;

            if(assignments[_v] == 0){
                wX += _w;
            }else if(assignments[_v] == 1){
                wY += _w;
            }
        }

        assignments[i] = (wX>=wY ? 1 : 0);
        
    }

    return assignments;


    // auto largest_weight_edge = this->graph.max_weighted_edges();

    // int n = this->graph.get_vertice_count();
    // vector<int> assignments(n + 1, -1);

    // int u = largest_weight_edge.first.first;
    // int v = largest_weight_edge.first.second;

    // assignments[u] = 0;
    // assignments[v] = 1;

    // for (int i = 0; i < n; i++) {
    //     if (assignments[i] != -1) continue;

    //     long long score_if_0 = 0;
    //     long long score_if_1 = 0;

    //     for (auto it : this->graph.adj_list[i]) {
    //         int _v = it.second;
    //         long long _w = it.first;

    //         if (assignments[_v] == 0) {
    //             score_if_1 += _w;
    //         } else if (assignments[_v] == 1) {
    //             score_if_0 += _w;
    //         }
    //     }

    //     assignments[i] = (score_if_0 >= score_if_1 ? 0 : 1);
    // }

    // return assignments;

}


////////////////////////////// Randomize 1 Algorithms ////////////////////////////


Randomize1 :: Randomize1(Graph _graph) : ConstructiveAlgorithms(_graph){

}

vector<int> Randomize1 :: assign() {
    int n = this->graph.get_vertice_count();

    vector<int> assignments(n+1);
    for(int i =0;i<n;i++) {
        assignments[i] = rand() %2;
    }

    return assignments;
}

long long Randomize1 :: get_avg_random_max_cut() {

    int n = this->graph.get_vertice_count();

    long long total_cut = 0;

    for(int i=1;i<=n;i++){
        auto assignments = assign();
        long long max_cut = this->graph.max_cut(assignments);

        total_cut+=max_cut;
    }

    return (ceil(total_cut/(1.0*n)));
}


SemiGreedy1 :: SemiGreedy1(Graph _graph, double _alpha) : ConstructiveAlgorithms(_graph) {

    this->alpha = _alpha;
}

vector<int> SemiGreedy1 :: assign() {
    auto largest_edge = this->graph.max_weighted_edges();

    int n = this->graph.get_vertice_count();
    vector<int> assignments(n+1,-1);




    int _u = largest_edge.first.first;
    int _v = largest_edge.first.second;
    int _w = largest_edge.second;


    assignments[_u] = 0;
    assignments[_v] = 1;

    while(1) {
        vector<int> non_taken_vertices;
        unordered_map<int,pair<long long,long long>> sigma_mapping;
        vector<long long> max_value;

        for(int v =0;v<n;v++) {
            if(assignments[v] != -1) continue;

            non_taken_vertices.push_back(v);

            long long sigmaX = 0, sigmaY = 0;

            for(auto nb : this->graph.adj_list[v]) {
                long long __w = nb.first;
                int __u = nb.second;

                if(assignments[__u] == 0) {
                    sigmaX += __w;
                }else if( assignments[__u] == 1){
                    sigmaY += __w;
                }

            }

            sigma_mapping[v] = { sigmaX, sigmaY};
            max_value.push_back(max(sigmaX,sigmaY));
        }

        if(non_taken_vertices.empty()) break;

        //
        long long Wmin = *min_element(max_value.begin(),max_value.end());
        long long Wmax = *max_element(max_value.begin(),max_value.end());

        long long meuw = Wmin + this->alpha *(Wmax - Wmin);

        vector<int> RCL;

        for(auto v : non_taken_vertices){
            long long value = max(sigma_mapping[v].first,sigma_mapping[v].second);

            if(value>=meuw){
                RCL.push_back(v);
            }
        }

        if(RCL.empty()) {
            RCL = non_taken_vertices;
        }


        int ind = rand() % RCL.size();
        int vertex = RCL[ind];


        auto item = sigma_mapping[vertex];

        assignments[vertex] = (item.first >= item.second? 1 : 0);
    }

    return assignments;



}




