
#include "2105160_LocalSearch.hpp"
#include "2105160_Graph.hpp"
#include "2105160_ConstructiveAlgorithms.hpp"
#include "2105160_Grasp.hpp"

#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Report {
    private:
        int iteration;
        ofstream output_file;
        string graph_id;
    public:
        Report(string output_file_name) {
            this->iteration = 50;
            this->output_file.open(output_file_name, ios::app);

            ifstream temp_stream(output_file_name);
            if (temp_stream.peek() == ifstream::traits_type::eof())
            {
                this->output_file << " Problem,,, Constructive Algorithm,,, Local Search,, GRASP, " << endl;
                this->output_file << " Name, |V| or n, |E| or m, Randomized-1, Greedy-1, Semi-Greedy-1, local-1,, GRASP-1, " << endl;
                this->output_file << ",,,,,, Number of Iterations, Average Value, Number of Iterations, Best Value " << endl;
            }
        }


        void allFunctionalities(Graph graph) {
             Randomize1 randomize1(graph);
             Greedy1 greedy1(graph);
             SemiGreedy1 semiGreedy1(graph,0.5);

             LocalSearch localSerach(graph);

             Grasp grasp(graph,iteration);

            long long randomized_cut = 0;

            
            for(int i = 0;i< iteration; i++) {
                auto cut = randomize1.get_avg_random_max_cut();
                randomized_cut+= cut;
            }
            randomized_cut = ceil(randomized_cut/(1.0* this->iteration));
            cout<<"runned randomize-1 "<<randomized_cut<<endl;
  
            long long greedy_cut = 0;
            for(int i =0 ;i< iteration;i++) {
                auto _a = greedy1.assign();
                greedy_cut += graph.max_cut(_a);
            }
            greedy_cut = ceil(greedy_cut/(1.0* this->iteration));
            cout<<"runned greedy-1 "<<greedy_cut<<endl;


            long long semi_cut = 0;
            for(int i =0;i < iteration; i++) {
                auto _a = semiGreedy1.assign();
                semi_cut += graph.max_cut(_a);
            }
            semi_cut = ceil( semi_cut /(1.0* this->iteration));
            cout<<"runned semi-greedy1 "<<semi_cut<<endl;


            long long local_cut = 0;
            for(int i =0;i< iteration;i++) {
                auto _asign = randomize1.assign();
                auto _a = localSerach.search(_asign);
                local_cut +=  graph.max_cut(_a);
            }
            local_cut = ceil( local_cut/(1.0* this->iteration));

            cout<<"runned local-1 "<<local_cut<<endl;

            long long grasp_cut = grasp.search();
            cout<<"runned grasp-1 "<<grasp_cut<<endl;

            this->output_file << graph_id << "," << graph.get_vertice_count()<< "," << graph.num_edges << ","<<randomized_cut<<","<<greedy_cut<<","<<semi_cut<<","<<iteration<<","<<local_cut<<","<<iteration<<","<<grasp_cut<<endl; 
            


        }

        void generate(string input_file_name) {
            ifstream _input_file(input_file_name);

            graph_id = input_file_name.substr(input_file_name.find_last_of("/\\") + 1).substr(0, input_file_name.substr(input_file_name.find_last_of("/\\") + 1).find_last_of("."));


            int n,m;

            _input_file >> n >> m;

            Graph graph(n,m);
            
            for (int i = 0; i < m; i++)
            {
                int u,v,w;
                _input_file >> u >> v >> w;

                u--;
                v--;

                
                graph.add_edges(u,v,w);
            }
            allFunctionalities(graph);
        }
};