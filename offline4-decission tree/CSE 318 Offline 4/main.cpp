
#include "decissiontree.hpp"


int main(int argc, char* argv[]) {

    if(argc != 3) {
        cerr << "Usage: ./decision_tree <criterion> <maxDepth>" << endl;
        return 1;
    }

    string criterion_name = argv[1];
    int max_depth = stoi(argv[2]);

    Criterion criterion(criterion_name);

    DataLoader data_loader("./Datasets/Iris.csv");


    cout<< "Training Decision Tree with criterion: " << criterion_name << " and max depth: " << max_depth << endl;

    double accuracy = 0.0;
    for(int i = 0; i< 20 ; i++) {


        data_loader.split_test_and_train();

        DecisionTree decision_tree(max_depth, data_loader, criterion);

        cout<< "Epoch " << i+1 <<": ";
        decision_tree.fit();

        auto predictions = decision_tree.predict(data_loader.testX);

        int correct_predictions = 0;
        for(size_t i = 0; i < data_loader.testY.size(); ++i) {
            if(predictions[i] == data_loader.testY[i]) {
                ++correct_predictions;
            }
        }

        accuracy += static_cast<double>(correct_predictions) / data_loader.testY.size();
        cout << "Accuracy: " << static_cast<double>(correct_predictions) / data_loader.testY.size() << " ";
        cout << "#Nodes: " << decision_tree.get_number_of_nodes() << " "<<endl;
    }

    cout << "Average Accuracy: " << accuracy / 20 << endl;

    return 0;
}