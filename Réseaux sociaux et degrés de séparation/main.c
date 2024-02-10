//
// Created by: Imad EL Maftouhi on 01/01/2024
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_USERS 20

typedef struct Node {
    int userId;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

typedef struct Graph {
    int numUsers;
    Node* adjList[MAX_USERS];
} Graph;

Graph* createGraph(int numUsers) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numUsers = numUsers;

    for (int i = 0; i < numUsers; ++i) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int user1, int user2) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->userId = user2;
    newNode->next = graph->adjList[user1];
    graph->adjList[user1] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->userId = user1;
    newNode->next = graph->adjList[user2];
    graph->adjList[user2] = newNode;
}

void matrixToGraph(Graph* graph, int matrix[MAX_USERS][MAX_USERS], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] == 1) {
                addEdge(graph, i, j);
            }
        }
    }
}

void printGraphMatrix(Graph* graph) {
    if (graph == NULL) {
        printf("Graph is NULL\n");
        return;
    }

    printf("Graph Matrix Representation:\n");

    printf("   ");
    for (int i = 0; i < MAX_USERS; i++) {
        printf("%2d ", i + 1);
    }
    printf("\n");
    printf("  +");
    for (int i = 0; i < MAX_USERS; i++) {
        printf("---");
    }
    printf("\n");

    for (int i = 0; i < MAX_USERS; i++) {
        printf("%2d|", i + 1);

        Node* ptr = graph->adjList[i];

        for (int j = 0; j < MAX_USERS; j++) {
            int isConnected = 0;
            while (ptr != NULL) {
                if (ptr->userId == j) {
                    isConnected = 1;
                    break;
                }
                ptr = ptr->next;
            }
            if (isConnected){
                printf(" X ");
            } else {
                printf(" . ");
            }

            ptr = graph->adjList[i];
        }

        printf("\n");
    }
}




bool BFS(Graph* graph, int source, int target, int* distance) {
    bool visited[MAX_USERS] = {false};
    Queue queue;
    queue.front = queue.rear = NULL;

    visited[source] = true;
    distance[source] = 0;

    Node* sourceNode = (Node*)malloc(sizeof(Node));
    sourceNode->userId = source;
    sourceNode->next = NULL;
    queue.front = queue.rear = sourceNode;

    while (queue.front != NULL) {
        int currentUser = queue.front->userId;
        Node* temp = queue.front;
        queue.front = queue.front->next;

        for (Node* neighbor = graph->adjList[currentUser]; neighbor != NULL; neighbor = neighbor->next) {
            int adjUser = neighbor->userId;

            if (!visited[adjUser]) {
                visited[adjUser] = true;
                distance[adjUser] = distance[currentUser] + 1;
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->userId = adjUser;
                newNode->next = NULL;

                if (queue.front == NULL) {
                    queue.front = queue.rear = newNode;
                } else {
                    queue.rear->next = newNode;
                    queue.rear = newNode;
                }

                if (adjUser == target) {
                    // Target user found
                    return true;
                }
            }
        }

        free(temp);
    }

    return false;
}

int findDegreeOfSeparation(Graph* graph, int user1, int user2) {
    if (user1 < 0 || user1 >= graph->numUsers || user2 < 0 || user2 >= graph->numUsers) {
        printf("Invalid user IDs\n");
        return -1;
    }

    int distance[MAX_USERS];
    for (int i = 0; i < MAX_USERS; ++i) {
        distance[i] = -1;
    }

    if (BFS(graph, user1, user2, distance)) {
        return distance[user2];
    } else {
        printf("No connection found between users %d and %d\n", user1, user2);
        return -1;
    }
}

void initializeMatrix(int matrix[MAX_USERS][MAX_USERS], int size) {
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j)
        {
            matrix[i][j] = rand() % 2;
        }}
}

// Function to generate a random graph
void generateRandomGraph(Graph* graph, int numUsers) {
    int matrix[MAX_USERS][MAX_USERS];
    initializeMatrix(matrix, numUsers);
    matrixToGraph(graph, matrix, numUsers);
}


int main() {
    int numUsers = 20;
    Graph* graph = createGraph(numUsers);

    int matrix[MAX_USERS][MAX_USERS] = {
            {0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
            {1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };




    matrixToGraph(graph, matrix, numUsers);

    printf("Graph Matrix Representation:\n");
    printGraphMatrix(graph);

    // //activer cette partie seulement si vous voulez generer une matrice avec des valeurs aléatoire
//    Graph* graph2 = createGraph(20);
//    generateRandomGraph(graph2, 20);
//    printf("Random Graph Matrix Representation:\n");
//    printGraphMatrix(graph2);

    int user1 = 0;
    int user2 = 17;
    int degree = findDegreeOfSeparation(graph, user1, user2);

    if (degree != -1) {
        printf("\nLe degré de séparation entre les utilisateurs %d et %d est : %d\n", user1, user2, degree);
    }




    return 0;
}
