#include "Map.h"
#include <fstream>
#include <iostream>
#include <sstream>

Map::Map() {
    // TODO: UNUTTUM
    // TODO: Your code here
    // Initialize all distances to a value representing no direct connection
    // Initialize all provinces as unvisited
}

// Loads distance data from a file and fills the distanceMatrix
void Map::loadDistanceData(const std::string& filename) {
    // TODO: Your code here
    // Read each line in the CSV file
    std::ifstream file(filename);
    std::string line;
    int row {0};

    // Read each cell separated by a comma
    while(std::getline(file, line)) {
        int column {0};

        std::istringstream ss(line);
        std::string number_str;

        while (std::getline(ss, number_str, ',')) {

            // Convert cell to an integer and store in distanceMatrix
            distanceMatrix[row][column] = std::stoi(number_str);
            column += 1;

        }
        row += 1;
    }


    // for(int i = 0; i < 81; i++) {
    //     for(int k = 0; k < 81; k++) {
    //         std::cout << distanceMatrix[i][k] << " ";
    //     }
    //     std::cout << std::endl;
    //
    // }
}

// Checks if the distance between two provinces is within the allowed maxDistance
bool Map::isWithinRange(int provinceA, int provinceB, int maxDistance) const {
    // TODO: Your code here

    if(distanceMatrix[provinceA][provinceB] <= maxDistance) {
        return true;
    }

    return false; 
}

// Marks a province as visited
void Map::markAsVisited(int province) {
    // TODO: Your code here

    visited[province] = true;
}

// Checks if a province has already been visited
bool Map::isVisited(int province) const {
    // TODO: Your code here

    if(visited[province]) {
        return true;
    }

    return false;
}

// Resets all provinces to unvisited
void Map::resetVisited() {
    // TODO: Your code here

    // TODO: KISALT
    for(int i = 0; i < 81; i++) {
        visited[i] = false;
    }

}

// Function to count the number of visited provinces
int Map::countVisitedProvinces() const {
    // TODO: Your code here

    int count{0};

    for(int i = 0; i < 81; i++) {
        if(visited[i]) {
            count += 1;
        }
    }

    return count;
}

// Function to get the distance between two provinces
int Map::getDistance(int provinceA, int provinceB) const {
    // TODO: Your code here

    return distanceMatrix[provinceA][provinceB];
}