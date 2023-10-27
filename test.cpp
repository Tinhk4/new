
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Define a struct to represent a data point
struct DataPoint {
    vector<double> features;
    int label;
};

// Define a function to calculate the Euclidean distance between two data points
double euclideanDistance(const DataPoint& a, const DataPoint& b) {
    double distance = 0.0;
    for (int i = 0; i < a.features.size(); i++) {
        distance += pow(a.features[i] - b.features[i], 2);
    }
    return sqrt(distance);
}

// Define the KNN algorithm function
int knn(const vector<DataPoint>& trainingData, const DataPoint& query, int k) {
    // Create a vector to store the distances between the query point and each training point
    vector<pair<double, int>> distances;
    for (int i = 0; i < trainingData.size(); i++) {
        double distance = euclideanDistance(trainingData[i], query);
        distances.push_back(make_pair(distance, i));
    }

    // Sort the distances in ascending order
    sort(distances.begin(), distances.end());

    // Count the number of occurrences of each label among the k nearest neighbors
    vector<int> labelCounts(10, 0);
    for (int i = 0; i < k; i++) {
        int index = distances[i].second;
        int label = trainingData[index].label;
        labelCounts[label]++;
    }

    // Find the label with the highest count
    int maxCount = 0;
    int maxLabel = -1;
    for (int i = 0; i < labelCounts.size(); i++) {
        if (labelCounts[i] > maxCount) {
            maxCount = labelCounts[i];
            maxLabel = i;
        }
    }

    return maxLabel;
}

int main() {
    // Create some sample data
    vector<DataPoint> trainingData = {
        {{1, 2, 3}, 0},
        {{4, 5, 6}, 1},
        {{7, 8, 9}, 2},
        {{10, 11, 12}, 0},
        {{13, 14, 15}, 1},
        {{16, 17, 18}, 2}
    };
    DataPoint query = {{4, 5, 6}, -1};

    // Run the KNN algorithm with k = 3
    int k = 3;
    int label = knn(trainingData, query, k);

    // Print the predicted label
    cout << "Predicted label: " << label << endl;

    return 0;
}
