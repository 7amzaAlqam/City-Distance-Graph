#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 100
#define MAX_DISTANCE 9999

// Structure to represent a city
typedef struct City {
    char name[100];
} City;

// Structure to represent an edge between two cities
typedef struct Edge {
    int source;
    int destination;
    int distance;
} Edge;

City cities[MAX_CITIES];
Edge graph[MAX_CITIES][MAX_CITIES];
int numCities = 0;

// Function to load cities from file and construct the graph
void loadCities() {
    // Open the file
    FILE *file = fopen("cities.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char source[100], destination[100];
    int distance;

    // Read city data from file
    while (fscanf(file, "%s %s %dkm", source, destination, &distance) != EOF) {
        int sourceIndex = -1, destinationIndex = -1;

        // Find or add source city
        for (int i = 0; i < numCities; i++) {
            if (strcmp(cities[i].name, source) == 0) {
                sourceIndex = i;
                break;
            }
        }

        if (sourceIndex == -1) {
            strcpy(cities[numCities].name, source);
            sourceIndex = numCities;
            numCities++;
        }

        // Find or add destination city
        for (int i = 0; i < numCities; i++) {
            if (strcmp(cities[i].name, destination) == 0) {
                destinationIndex = i;
                break;
            }
        }

        if (destinationIndex == -1) {
            strcpy(cities[numCities].name, destination);
            destinationIndex = numCities;
            numCities++;
        }

        // Add edge to the graph
        graph[sourceIndex][destinationIndex].source = sourceIndex;
        graph[sourceIndex][destinationIndex].destination = destinationIndex;
        graph[sourceIndex][destinationIndex].distance = distance;
    }

    // Close the file
    fclose(file);
}

// Function to get the index of a city by its name
int getCityIndex(char *cityName) {
    for (int i = 0; i < numCities; i++) {
        if (strcmp(cities[i].name, cityName) == 0) {
            return i;
        }
    }
    return -1;
}

// Dijkstra's algorithm to find the shortest path
void dijkstra(int sourceIndex, int destinationIndex) {
    // Initialize distance, visited, and previous arrays
    int distance[MAX_CITIES];
    int visited[MAX_CITIES];
    int previous[MAX_CITIES];

    for (int i = 0; i < numCities; i++) {
        distance[i] = MAX_DISTANCE;
        visited[i] = 0;
        previous[i] = -1;
    }

    distance[sourceIndex] = 0;

    // Run Dijkstra's algorithm
    for (int i = 0; i < numCities - 1; i++) {
        int minDistance = MAX_DISTANCE;
        int minIndex = -1;

        // Find the unvisited city with minimum distance
        for (int j = 0; j < numCities; j++) {
            if (visited[j] == 0 && distance[j] < minDistance) {
                minDistance = distance[j];
                minIndex = j;
            }
        }

        visited[minIndex] = 1;

        // Update distance and previous arrays
        for (int j = 0; j < numCities; j++) {
            if (visited[j] == 0 && graph[minIndex][j].distance != 0 && distance[minIndex] != MAX_DISTANCE &&
                distance[minIndex] + graph[minIndex][j].distance < distance[j]) {
                distance[j] = distance[minIndex] + graph[minIndex][j].distance;
                previous[j] = minIndex;
            }
        }
    }

    // Print the shortest path
    printf("Shortest path from %s to %s using Dijkstra's algorithm:\n", cities[sourceIndex].name, cities[destinationIndex].name);
    printf("%s", cities[destinationIndex].name);
    int currentIndex = destinationIndex;
    while (previous[currentIndex] != -1) {
        printf(" <- %s", cities[previous[currentIndex]].name);
        currentIndex = previous[currentIndex];
    }
    printf("\n");
    printf("Total distance: %d km\n", distance[destinationIndex]);
}

// Breadth First Search (BFS) algorithm to find the shortest path
void bfs(int sourceIndex, int destinationIndex) {
    // Initialize visited, previous, and distance arrays
    int visited[MAX_CITIES];
    int previous[MAX_CITIES];
    int distance[MAX_CITIES];

    for (int i = 0; i < numCities; i++) {
        visited[i] = 0;
        previous[i] = -1;
        distance[i] = MAX_DISTANCE;
    }

    visited[sourceIndex] = 1;
    distance[sourceIndex] = 0;

    // Create a queue for BFS
    int queue[MAX_CITIES];
    int front = 0;
    int rear = 0;
    queue[rear++] = sourceIndex;

    // Run BFS algorithm
    while (front < rear) {
        int currentIndex = queue[front++];
        for (int i = 0; i < numCities; i++) {
            if (visited[i] == 0 && graph[currentIndex][i].distance != 0) {
                visited[i] = 1;
                previous[i] = currentIndex;
                distance[i] = distance[currentIndex] + graph[currentIndex][i].distance;
                queue[rear++] = i;
            }
        }
    }

    // Print the shortest path
    printf("Shortest path from %s to %s using BFS algorithm:\n", cities[sourceIndex].name, cities[destinationIndex].name);
    printf("%s", cities[destinationIndex].name);
    int currentIndex = destinationIndex;
    while (previous[currentIndex] != -1) {
        printf(" <- %s", cities[previous[currentIndex]].name);
        currentIndex = previous[currentIndex];
    }
    printf("\n");
    printf("Total distance: %d km\n", distance[destinationIndex]);
}


int main() {
    int choice;
    int sourceIndex = -1, destinationIndex = -1;

    // Menu loop
    while (1) {
        printf("Menu:\n");
        printf("1. Load cities\n");
        printf("2. Enter source\n");
        printf("3. Enter destination\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                loadCities();
                printf("Cities loaded.\n");
                break;
            case 2:
                printf("Enter source city: ");
                char sourceCity[100];
                scanf("%s", sourceCity);
                sourceIndex = getCityIndex(sourceCity);
                if (sourceIndex == -1) {
                    printf("City not found.\n");
                }
                break;
            case 3:
                printf("Enter destination city: ");
                char destinationCity[100];
                scanf("%s", destinationCity);
                destinationIndex = getCityIndex(destinationCity);
                if (destinationIndex == -1) {
                    printf("City not found.\n");
                } else if (sourceIndex == -1) {
                    printf("Please enter source city first.\n");
                } else {
                    dijkstra(sourceIndex, destinationIndex);
                    bfs(sourceIndex, destinationIndex);

                    // Print information to file
                    FILE *file = fopen("shortest_distance.txt", "w");
                    if (file == NULL) {
                        printf("Error opening file.\n");
                        return 1;
                    }

                    fprintf(file, "Shortest path from %s to %s:\n", cities[sourceIndex].name, cities[destinationIndex].name);
                    fprintf(file, "Dijkstra's algorithm:\n");
                    fprintf(file, "%s", cities[destinationIndex].name);
                    int currentIndex = destinationIndex;
                    int previous[MAX_CITIES];
                    while (previous[currentIndex] != -1) {
                        fprintf(file, " <- %s", cities[previous[currentIndex]].name);
                        currentIndex = previous[currentIndex];
                    }
                    fprintf(file, "\n");
                    int distance[destinationIndex];
                    fprintf(file, "Total distance: %d km\n", distance[destinationIndex]);

                    fprintf(file, "BFS algorithm:\n");
                    fprintf(file, "%s", cities[destinationIndex].name);
                    currentIndex = destinationIndex;

                    while (previous[currentIndex] != -1) {
                        fprintf(file, " <- %s", cities[previous[currentIndex]].name);
                        currentIndex = previous[currentIndex];
                    }
                    fprintf(file, "\n");
                    fprintf(file, "Total distance: %d km\n", distance[destinationIndex]);

                    fclose(file);

                    printf("**Shortest path information saved to shortest_distance.txt.\n");

                }
                break;
            case 4:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
