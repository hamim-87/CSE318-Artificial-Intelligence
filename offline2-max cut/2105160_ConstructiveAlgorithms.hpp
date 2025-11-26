#ifndef CONSTRUCTIVE_ALGORITHMS
#define CONSTRUCTIVE_ALGORITHMS

#include <bits/stdc++.h>

using namespace std;

#include "2105160_Graph.hpp"


class ConstructiveAlgorithms{
    protected:
        Graph graph;
    public:
        ConstructiveAlgorithms(Graph _graph);
        virtual vector<int> assign() = 0;
};


class Greedy1 : public ConstructiveAlgorithms {
    public:
        Greedy1(Graph _graph);
        vector<int> assign();
    
};

class Randomize1 : public ConstructiveAlgorithms {
    public:
        Randomize1(Graph _graph);
        vector<int> assign();
        long long get_avg_random_max_cut();
};

class SemiGreedy1 : public ConstructiveAlgorithms {
    private:
        double alpha ;
    public:
        SemiGreedy1(Graph _graph,double _alpha = 0.5);
        vector<int> assign();

};




#endif