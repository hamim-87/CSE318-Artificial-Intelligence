#ifndef LOCAL_SEARCH
#define LOCAL_SEARCH

using namespace std;

#include "2105160_Graph.hpp"

class LocalSearch{
    private:
        Graph  graph;
    

    public:
        LocalSearch(Graph _graph){
            this->graph = _graph;
        }

        vector<int> search(vector<int> flip_color_assingments){
            

            long long best_cut = this->graph.max_cut(flip_color_assingments);

            int m = graph.get_vertice_count();

            while(1){
                int index = 0;

                for(;index<m;index++){

                    long long new_cut = this->graph.max_cut(index,flip_color_assingments,best_cut);

                    if(new_cut>best_cut){
                        flip_color_assingments[index] = 1 ^ flip_color_assingments[index];
                        
                        break;
                    }
                }

                if(index >= m) break;

            }

            return flip_color_assingments;
        }
    


};


#endif