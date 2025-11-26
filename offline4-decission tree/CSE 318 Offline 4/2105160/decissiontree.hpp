#pragma once

#include "node.hpp"
#include  "dataloader.hpp"
#include "criterion.hpp"


class DecisionTree {
    private:
        int _max_depth; 
        int _min_samples_split;
        int _min_samples_leaf;

        vector<Node> _nodes;

        Criterion _criterion;

        DataLoader _data_loader;


        bool find_split(
            double &best_theashold,
            int &best_feature,
            vector<int> &left_indices,
            vector<int> &right_indices,
            vector<int> &indices
        ) {
            double best_score = -1.0;
            best_feature = -1;
            best_theashold = 0.0;
            left_indices.clear();
            right_indices.clear();

            int n_samples = indices.size();
            if(n_samples < _min_samples_split) return false;

            vector<double> targets(n_samples);
            for(int i = 0;i<n_samples;i++) {
                targets[i] = _data_loader.trainY[indices[i]];
            }

            int n_features = _data_loader.trainX[0].size();

            for(int i = 0;i<n_features;i++) {
                vector<double> unique_feature_values;
                vector<double> feature_column;
                set<double> unique_values_set;
                for(int j = 0;j<n_samples;j++) {
                    double value = _data_loader.trainX[indices[j]][i];
                    unique_values_set.insert(value);
                    feature_column.push_back(value);
                }

                unique_feature_values.assign(unique_values_set.begin(), unique_values_set.end());

                for(int j = 1;j < unique_feature_values.size();j++) {
                    
                    double avg_threshold = (unique_feature_values[j] + unique_feature_values[j-1]) / 2.0;

                    vector<int> left, right;
                    vector<double> left_targets, right_targets;

                
                    for (int idx : indices) {
                        if (_data_loader.trainX[idx][i] <= avg_threshold) {
                            left.push_back(idx);
                            left_targets.push_back(_data_loader.trainY[idx]);
                        } else {
                            right.push_back(idx);
                            right_targets.push_back(_data_loader.trainY[idx]);
                        }
                    }

  
                    if (left.size() < _min_samples_leaf || right.size() < _min_samples_leaf) {
                        continue;
                    }

                    double gain = _criterion.information_gain(
                        feature_column,
                        targets,
                        avg_threshold
                    );

                    if (gain > best_score) {
                        best_score = gain;
                        best_feature = i;
                        best_theashold = avg_threshold;
                        left_indices = left;
                        right_indices = right;
                    }
                }

                
            }

            return best_feature != -1 && !left_indices.empty() && !right_indices.empty();
        }


        int build_tree(vector<int> &row_indices, int depth) {

            Node node;
            node.num_samples = row_indices.size();
            

            auto idx = _data_loader.trainX;
            auto y = _data_loader.trainY;

            vector<double> targets;
            for(int i =0;i < row_indices.size(); i++) {
                targets.push_back(y[row_indices[i]]);
            }

            node.impurity = _criterion.entropy(targets);

            if( (depth >= _max_depth && _max_depth != 0) || row_indices.size() < _min_samples_split) {
                map<double, int> counts;
                for(const auto& label : targets) {
                    counts[label]++;
                }
                auto max_it = max_element(counts.begin(), counts.end(),
                    [](const auto& a, const auto& b) { return a.second < b.second; });
                node.class_label = max_it->first;
                _nodes.push_back(node);
                return _nodes.size() - 1;
            }

            double best_threshold;
            int best_feature;
            vector<int> left_indices, right_indices;

            bool can_split = find_split(
                 best_threshold,
                 best_feature,
                 left_indices,
                 right_indices,
                 row_indices
            );


            if(!can_split) {
                map<double, int> counts;
                for(const auto& label : targets) {
                    counts[label]++;
                }
                auto max_it = max_element(counts.begin(), counts.end(),
                    [](const auto& a, const auto& b) { return a.second < b.second; });
                node.class_label = max_it->first;
                _nodes.push_back(node);
                return _nodes.size() - 1;
            }

            node.feature_index = best_feature;
            node.threshold = best_threshold;
            _nodes.push_back(node);

            int index = _nodes.size()-1;

            node.left_child_index = build_tree(left_indices,depth+1);
            node.right_child_index = build_tree(right_indices,depth+1);
            _nodes[index] = node;

            return index;

        }





        



    public:
        DecisionTree(int max_depth,DataLoader data_loader,Criterion criterion, int min_samples_split = 2, int min_samples_leaf = 1 ) {
            this->_max_depth = max_depth;
            this->_min_samples_split = min_samples_split;
            this->_min_samples_leaf = min_samples_leaf;
            this->_data_loader = data_loader;
            this->_criterion = criterion;

        }

        void fit() {


            vector<int> row_indices(_data_loader.trainX.size());
            iota(row_indices.begin(), row_indices.end(), 0); 
            
            this->build_tree(row_indices, 0);
            
        }

        vector<int> predict(vector<vector<double>> & X) {
            vector<int> y(X.size());

            
            for(int i = 0; i< y.size();i++) {
                int node_index = 0;

                while(_nodes[node_index].feature_index != -1) {
                    int feature_index = _nodes[node_index].feature_index;
                    if(X[i][feature_index] <= _nodes[node_index].threshold) {
                        node_index = _nodes[node_index].left_child_index;
                    }else{
                        node_index = _nodes[node_index].right_child_index;
                    }
                }
                y[i] = _nodes[node_index].class_label;
            }

            return y;
        } 




        
        int get_number_of_nodes() {
            return _nodes.size();
        }




};
