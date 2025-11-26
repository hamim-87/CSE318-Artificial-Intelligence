
#include "2105160_Graph.hpp"
#include "2105160_LocalSearch.hpp"
#include "2105160_ConstructiveAlgorithms.hpp"

class Grasp {
    private:
        Graph graph;
        int iteration;
        
    public:
        Grasp(Graph _graph, int iteration = 5, double alpha = 0.5) {
            this->graph = _graph;
            this->iteration = iteration;

        }


        long long search() {
            LocalSearch localsearch(this->graph);
            SemiGreedy1 semigreedy(this->graph,0.5);
            long long res = 0;

            vector<int> bestAssignment;

            for(int i = 0;i<iteration;i++) {
                
                auto assignments = semigreedy.assign();

                auto newassignments = localsearch.search(assignments);

                long long localcut = graph.max_cut(newassignments);

                if(localcut> res) {
                    res = localcut;
                    bestAssignment = newassignments;
                }

            }
            
            return res;

        }
};