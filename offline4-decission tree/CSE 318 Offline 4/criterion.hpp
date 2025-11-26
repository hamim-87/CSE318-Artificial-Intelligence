#pragma once

#include <bits/stdc++.h>

using namespace std;

class Criterion {
    private:

        string selected_criterion;




        double intrinsic_value(vector<double> &feature_column, vector<double> &target_column) {
            map<double, int> value_counts;
            for(int i = 0; i < feature_column.size(); i++) {
                value_counts[feature_column[i]]++;
            }

            double iv = 0.0;
            for(auto it: value_counts) {
                double prob = (double)it.second / feature_column.size();
                if(prob == 0) continue;
                iv -= prob * log2(prob);
            }
            return iv;
        }

    public:
        Criterion(const string& criterion) : selected_criterion(criterion) {}
        Criterion(){
            selected_criterion = "IG"; 
        }

        double entropy(vector<double>& target) {
            map<double, int> partition;
            for(auto it: target) {
                partition[it]++;
            }

            double entropy = 0.0;

            for(auto it: partition) {
                double prob = (double)it.second / target.size();

                if(prob == 0) continue;
                entropy -= prob * log2(prob);
            }
            return entropy;
        }


        // double information_gain(
        //     vector<string> & feature_column,
        //     vector<string> &target_column,
        //     const string &value
        // ) {
        //     double parent_entropy = entropy(target_column);

        //     vector<string> match_target;
        //     vector<string> non_match_target;

        //     for(int i = 0; i < feature_column.size(); i++) {
        //         if(feature_column[i] == value) {
        //             match_target.push_back(target_column[i]);
        //         } else {
        //             non_match_target.push_back(target_column[i]);
        //         }
        //     }

        //     double wce = 0.0;
        //     if(!match_target.empty()) {
        //         wce += (double)match_target.size() / feature_column.size() * entropy(match_target);
        //     }
        //     if(!non_match_target.empty()) {
        //         wce += (double)non_match_target.size() / feature_column.size() * entropy(non_match_target);
        //     }

        //     return parent_entropy - wce;
        // }

        double information_gain(
            vector<double> & feature_column,
            vector<double> &target_column,
            double threshold
        ) {
            double parent_entropy = entropy(target_column);

            vector<double> left_target;
            vector<double> right_target;

            for(int i = 0; i < feature_column.size(); i++) {
                if(feature_column[i] <= threshold) {
                    left_target.push_back(target_column[i]);
                } else {
                    right_target.push_back(target_column[i]);
                }
            }

            double wce = 0.0;
            if(!left_target.empty()) {
                wce += (double)left_target.size() / feature_column.size() * entropy(left_target);
            }
            if(!right_target.empty()) {
                wce += (double)right_target.size() / feature_column.size() * entropy(right_target);
            }

            return parent_entropy - wce;
        }


        // double information_gain_ratio(
        //     vector<string> & feature_column,
        //     vector<string> &target_column,
        //     const string &value
        // ) {
        //     double ig = information_gain(feature_column, target_column, value);
        //     double iv = intrinsic_value(feature_column, target_column);

        //     if(iv == 0) return 0.0; 
        //     return ig / iv;
        // }

        double information_gain_ratio(
            vector<double> & feature_column,
            vector<double> &target_column,
            double threshold
        ) {
            double ig = information_gain(feature_column, target_column, threshold);
            double iv = intrinsic_value(feature_column, target_column);

            if(iv == 0) return 0.0; 
            return ig / iv;
        }

        // double normalized_weighted_information_gain(
        //     vector<string> & feature_column,
        //     vector<double> &target_column,
        //     const string &value
        // ) {
        //     double ig = information_gain(feature_column, target_column, value);

        //     set<string> unique_values(feature_column.begin(), feature_column.end());
        //     int k = unique_values.size();

        //     if(k == 0) return 0.0; 
        //     return (ig / log2(k + 1)) * (1.0 - (double)(k - 1) / feature_column.size());
        // }

        double normalized_weighted_information_gain(
            vector<double> & feature_column,
            vector<double> &target_column,
            double threshold
        ) {
            double ig = information_gain(feature_column, target_column, threshold);

            set<double> unique_values(feature_column.begin(), feature_column.end());
            int k = unique_values.size();

            if(k == 0) return 0.0; 
            return (ig / log2(k + 1)) * (1.0 - (double)(k - 1) / feature_column.size());
        }


        double get_criterion_value(
             vector<double> &idx,
             vector<double> &target,
             double &split_value
        ) {
            if (selected_criterion == "IG") {
                return information_gain(idx, target, split_value);
            } else if (selected_criterion == "IGR") {
                return information_gain_ratio(idx, target, split_value);
            } else if (selected_criterion == "NWIG") {
                return normalized_weighted_information_gain(idx, target, split_value);
            } else {
                throw invalid_argument("Unknown criterion: " + selected_criterion);
            }
        }

    

 

};