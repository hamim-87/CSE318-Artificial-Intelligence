#include <bits/stdc++.h>

using namespace std;

class DataLoader {
private:
    vector<vector<string>> data;
    vector<vector<double>> p_data;
    map<int, vector<string>> categorial_features;
    vector<bool> is_feature_numerical;



    bool is_number(const string& s) {
        try {
            size_t pos;
            stod(s, &pos);
            return pos == s.size();
        } catch (...) {
            return false;
        }
    }

public:
    vector<vector<double>> trainX;
    vector<double> trainY;

    vector<vector<double>> testX;
    vector<double> testY;
    DataLoader() {}

    DataLoader(string _file) {
        this->data = this->process_data(_file);

        if (data.empty() || data[0].empty()) {
            return;
        }


        p_data.resize(data.size(), vector<double>(data[0].size(), 0.0));

        this->check_neumerical_features();
        this->encode_categorial_features();
        this->pre_process();
        this->split_test_and_train();


        
    }

    void split_test_and_train() {
        trainX.clear();
        trainY.clear();
        testX.clear();
        testY.clear();

        unsigned seed = static_cast<unsigned>(time(0));
        shuffle(p_data.begin()+1,p_data.end(), default_random_engine(seed));

        int n = p_data.size() * 0.8;
        for(int i =1;i<n;i++) {
            vector<double> v;
            for(int j =0;j<p_data[i].size()-1;j++){
                v.push_back(p_data[i][j]);
            }
            trainX.push_back(v);
            trainY.push_back(p_data[i].back());
        }

        for(int i = n;i<p_data.size();i++){
            vector<double> v;
            for(int j = 0;j<p_data[i].size()-1;j++) {
                v.push_back(p_data[i][j]);
            }
            testX.push_back(v);
            testY.push_back(p_data[i].back());
        }
    }




    void print() {
        if (p_data.empty()) {
            return;
        }
        for (const auto& row : p_data) {
            for (double val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }

    void encode_categorial_features() {
        if (data.empty() || data[0].empty()) return;

        for (int i = 0; i < data[0].size(); i++) {
            if (is_feature_numerical[i]) continue;

            set<string> unique_values;
            for (int j = 1; j < data.size(); j++) {
                if (j >= data.size() || i >= data[j].size()) {

                    continue;
                }
                if (data[j][i] == "?" || data[j][i].empty()) continue;
                unique_values.insert(data[j][i]);
            }
            categorial_features[i].assign(unique_values.begin(), unique_values.end());
        }
    }

    double get_encode_value(int feature_index, const string& value) {
        auto it = categorial_features.find(feature_index);
        if (it == categorial_features.end()) return -1.0;

        for (int i = 0; i < it->second.size(); i++) {
            if (it->second[i] == value) return static_cast<double>(i);
        }
        return -1.0;
    }

    string get_decode_value(int feature_index, double value) {
        auto it = categorial_features.find(feature_index);
        if (it == categorial_features.end() || value < 0 || value >= it->second.size()) {
            return "";
        }
        return it->second[static_cast<int>(value)];
    }

    void check_neumerical_features() {
        if (data.empty() || data[0].empty()) return;

        is_feature_numerical.resize(data[0].size(), true);
        for (int i = 0; i < data[0].size(); i++) {
            bool is_numerical = true;
            for (int j = 1; j < data.size(); j++) {
                if (data[j][i] == "?" || data[j][i].empty()) continue;
                if (!is_number(data[j][i])) {
                    is_numerical = false;
                    break;
                }
            }
            is_feature_numerical[i] = is_numerical;
        }
    }

    void pre_process() {
        if (data.empty() || data[0].empty()) return;

        for (int i = 0; i < data[0].size(); i++) {
            for (int j = 1; j < data.size(); j++) {
                if (j >= data.size() || i >= data[j].size()) {
                    cout << "Error: Invalid access at data[" << j << "][" << i << "]" << endl;
                    continue;
                }
                if (is_feature_numerical[i]) {
                    if (data[j][i] == "?" || data[j][i].empty()) {
                        p_data[j][i] = 0.0;
                    } else {
                        try {
                            p_data[j][i] = stod(data[j][i]);
                        } catch (...) {
                            p_data[j][i] = 0.0;
                        }
                    }
                } else {
                    if (data[j][i] == "?" || data[j][i].empty()) {
                        p_data[j][i] = -1.0;
                    } else {
                        p_data[j][i] = get_encode_value(i, data[j][i]);
                    }
                }
            }
        }



    }

    vector<vector<string>> process_data(string _file) {
        ifstream file(_file);
        vector<vector<string>> _data;

        if (!file.is_open()) {
            cout << "Error: Could not open file " << _file << endl;
            return _data;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string value;
            vector<string> row;

            while (getline(ss, value, ',')) {
                row.push_back(value);
            }

            if (!row.empty()) {
                _data.push_back(row);
            }
        }

   
        if (!_data.empty()) {
            size_t num_cols = _data[0].size();
            for (size_t i = 1; i < _data.size(); i++) {
                if (_data[i].size() != num_cols) {
                    return {};
                }
            }
        }

        file.close();
        return _data;
    }


};