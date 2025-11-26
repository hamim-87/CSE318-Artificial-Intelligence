#pragma once

#include <bits/stdc++.h>

using namespace std;


class Node {

    public:
        int feature_index;



        double threshold;


        int class_label;
        int num_samples;


        int left_child_index;
        int right_child_index;

        double impurity;


        Node() {
            feature_index = -1;
            threshold = 0.0;


            class_label = -1;
            num_samples = 0;

            left_child_index = -1;
            right_child_index = -1;

            impurity = 0.0;
        }


        
};