#include "RoutePlanner.h"
#include <iostream>
#include <fstream>

// Array to help you out with name of the cities in order
const std::string cities[81] = { 
    "Adana", "Adiyaman", "Afyon", "Agri", "Amasya", "Ankara", "Antalya", "Artvin", "Aydin", "Balikesir", "Bilecik", 
    "Bingol", "Bitlis", "Bolu", "Burdur", "Bursa", "Canakkale", "Cankiri", "Corum", "Denizli", "Diyarbakir", "Edirne", 
    "Elazig", "Erzincan", "Erzurum", "Eskisehir", "Gaziantep", "Giresun", "Gumushane", "Hakkari", "Hatay", "Isparta", 
    "Mersin", "Istanbul", "Izmir", "Kars", "Kastamonu", "Kayseri", "Kirklareli", "Kirsehir", "Kocaeli", "Konya", "Kutahya", 
    "Malatya", "Manisa", "Kaharamanmaras", "Mardin", "Mugla", "Mus", "Nevsehir", "Nigde", "Ordu", "Rize", "Sakarya", 
    "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdag", "Tokat", "Trabzon", "Tunceli", "Urfa", "Usak", "Van", "Yozgat", 
    "Zonguldak", "Aksaray", "Bayburt", "Karaman", "Kirikkale", "Batman", "Sirnak", "Bartin", "Ardahan", "Igdir", 
    "Yalova", "Karabuk", "Kilis", "Osmaniye", "Duzce" 
};

// Constructor to initialize and load constraints
RoutePlanner::RoutePlanner(const std::string& distance_data, const std::string& priority_data, const std::string& restricted_data, int maxDistance)
    : maxDistance(maxDistance), totalDistanceCovered(0), numPriorityProvinces(0), numWeatherRestrictedProvinces(0) {

    // TO DO:
    // Load map data from file
    map.loadDistanceData(distance_data);
    // Mark all provinces as unvisited initially
    map.resetVisited();
    // Load priority provinces
    loadPriorityProvinces(priority_data);
    // Load restricted provinces
    loadWeatherRestrictedProvinces(restricted_data);
}

// Load priority provinces from txt file to an array of indices
void RoutePlanner::loadPriorityProvinces(const std::string& filename) {
    // TODO: Your code here
    std::ifstream file(filename);
    std::string line;

    int index = 0;
    while(std::getline(file, line)) {
        if (index == 10) {
            break;
        }

        int provinceNo = std::stoi(line);

        priorityProvinces[index] = provinceNo;
        index += 1;
    }
    numPriorityProvinces = index;

}

// Load weather-restricted provinces from txt file to an array of indices
void RoutePlanner::loadWeatherRestrictedProvinces(const std::string& filename) {
    // TODO: Your code here

    std::ifstream file(filename);
    std::string line;

    int index = 0;
    while(std::getline(file, line)) {
        if (index == 10) {
            break;
        }

        int provinceNo = std::stoi(line);

        weatherRestrictedProvinces[index] = provinceNo;
        index += 1;
    }
    numWeatherRestrictedProvinces = index;

}

// Checks if a province is a priority province
bool RoutePlanner::isPriorityProvince(int province) const {
    // TODO: Your code here

    for(int i = 0; i < numPriorityProvinces; i++) {
        if(province == priorityProvinces[i]) {
            return true;
        }
    }

    return false;
}

// Checks if a province is weather-restricted
bool RoutePlanner::isWeatherRestricted(int province) const {
    // TODO: Your code here

    for(int i = 0; i < numWeatherRestrictedProvinces; i++) {
        if(province == weatherRestrictedProvinces[i]) {
            return true;
        }
    }

    return false;
}

// Begins the route exploration from the starting point
void RoutePlanner::exploreRoute(int startingCity) {
    // TODO: Your code here
    stack.push(startingCity);
    map.visited[startingCity] = true;
    route.push_back(startingCity);
    while(!isExplorationComplete()) {
        std::cout << cities[stack.data[stack.top]] << std::endl;
        exploreFromProvince(stack.data[stack.top]);

        // QUEUE DAKI SIRADA SEYAHAT EDILECEK ELEMENAI STACKE ATIYOR
        std::cout << "queue: " ;
        for(int i = queue.front ; i <= queue.rear; i++) {
            std::cout << queue.data[i] << " ";
        }
        std::cout << std::endl;
        backtrack();

    }
    route = tempRoute;
    for(int i = 0 ; i < route.size() - 1  ; i++) {
        totalDistanceCovered += map.distanceMatrix[route[i]][route[i+1]];
    }
    displayResults();
}

// Helper function to explore from a specific province
void RoutePlanner::exploreFromProvince(int province) {
    // TODO: Your code here

    for(int i = 0; i < 81; i++) {
        if (province == i) {
            continue;
        }
        if(map.distanceMatrix[province][i] <= 250) {
            if(!map.isVisited(i)) {
                enqueueNeighbors(i);
            }
        }

    }

}

void RoutePlanner::enqueueNeighbors(int province) {
    // TO DO: Enqueue priority & non-priority neighbors to the queue according to given constraints

    for(int i = 0; i < numWeatherRestrictedProvinces; i++) {
        if(province == weatherRestrictedProvinces[i]) {
            std::cout << "Province "<< cities[province] <<" is weather-restricted. Skipping." << std::endl;
            return;
        }
    }


    for(int i = 0; i < numPriorityProvinces; i++) {
        if (province == priorityProvinces[i]) {
            queue.enqueuePriority(province);
            return;
        }
    }

    queue.enqueue(province);

}

void RoutePlanner::backtrack() {
    // If you reach a dead-end province 
    // TODO: Your code here

    int x{0};
    while(true) {
        if(queue.isEmpty()) {
            break;
        }

        x = queue.dequeue();
        std::cout << "x: " << x  << " " << cities[x]<< std::endl;
        if(map.distanceMatrix[x][stack.data[stack.top]] <= maxDistance && !map.isVisited(x)) {
            break;
        }
    }

    if(queue.isEmpty()) {
        if( map.distanceMatrix[x][stack.data[stack.top]] > maxDistance || map.isVisited(x)) {
            int p = stack.pop();
            std::cout << "Pop : " << p << std::endl;
            std::cout << "backward" << std::endl;
            if(route.size() > tempRoute.size()) {
                tempRoute = route;
            }
            route.pop_back();

        }else {
            stack.push(x);
            std::cout << "forward" << std::endl;
            map.visited[x] = true;
            route.push_back(x);

        }

    }else {
        stack.push(x);
        std::cout << "forward" << std::endl;
        map.visited[x] = true;
        route.push_back(x);
    }

}

bool RoutePlanner::isExplorationComplete() const {
    // TODO: Your code here

    if (queue.isEmpty() && stack.isEmpty()) {
        return true;
    }

    return false;
}

void RoutePlanner::displayResults() const {
    // TODO: Your code here
    // Display "Journey Completed!" message
    std::cout << "Journey Completed!" << std::endl;
    // Display the total number of provinces visited
    std::cout << "Total Number of Provinces Visited: " << map.countVisitedProvinces() << std::endl;
    // Display the total distance covered
    std::cout << "Total Distance Covered: " << totalDistanceCovered << " km" << std::endl;
    // Display the route in the order visited
    for(int i = 0 ; i < route.size() ; i++) {
        std::cout << cities[route[i]] << " -> " ;
    }
    std::cout << "end" << std::endl;
    // Priority Province Summary
    int count {0};
    for(int k = 0; k < numPriorityProvinces; k++) {
        std::cout << "- " << cities[priorityProvinces[k]] << " (";
        if (map.isVisited(priorityProvinces[k])) {
            count += 1;
            std::cout << "Visited";
        }else {
            std::cout << "Not Visited";
        }
        std::cout << ")" << std::endl;
    }
    std::cout << "Total Priority Provinces Visited: " << count <<" out of "<< numPriorityProvinces << std::endl;
    if(count == numPriorityProvinces) {
        std::cout << "Success: All priority provinces were visited." << std::endl;
    }else {
        std::cout << "Warning: Not all priority provinces were visited." << std::endl;
    }


}


