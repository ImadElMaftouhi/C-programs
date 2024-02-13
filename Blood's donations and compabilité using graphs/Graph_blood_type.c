#include <stdio.h>
#include <stdlib.h>

#define BLOOD_TYPES 8
#define BLOOD_TYPE_LENGTH 3

void printMatrix(int *matrix, int size) {
    char bloodTypes[BLOOD_TYPES][BLOOD_TYPE_LENGTH] = {"AB+", "AB-", "A+", "A-", "B+", "B-", "O+", "O-"};

    // Print header with blood types
    printf("\t");
    for (int i = 0; i < size; i++) {
        printf("%s\t", bloodTypes[i]);
    }

    for (int i = 0; i < size; i++) {
        printf("\n%s\t", bloodTypes[i]);
        for (int j = 0; j < size; j++) {
            printf("%d\t", *(matrix + i * size + j));
        }
    }
    printf("\n");
}

int* createAdjacencyMatrix(int size) {
    char bloodTypes[BLOOD_TYPES][BLOOD_TYPE_LENGTH] = {"AB+", "AB-", "A+", "A-", "B+", "B-", "O+", "O-"};
    int *matrix = (int *)malloc(size * size * sizeof(int));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("Enter the value for the relation between %s and %s (1 or 0): ", bloodTypes[i], bloodTypes[j]);
            scanf("%d", (matrix + i * size + j));

            while (*(matrix + i * size + j) != 1 && *(matrix + i * size + j) != 0) {
                printf("Choices must be either 1 or 0, please retry: ");
                scanf("%d", (matrix + i * size + j));
            }
        }
    }

    return matrix;
}

int countPredecessors(int *matrix, int node, int size) {
    node--;

    int counter = 0;
    for (int i = 0; i < size; i++) {
        if (*(matrix + i * size + node) == 1) {
            counter++;
        }
    }

    return counter;
}

int countSuccessors(int *matrix, int node, int size) {
    node--;

    int counter = 0;
    for (int i = 0; i < size; i++) {
        if (*(matrix + i + node * size) == 1) {
            counter++;
        }
    }

    return counter;
}

void showPredecessors(int *matrix, int node, int size) {
    node--;

    char bloodTypes[BLOOD_TYPES][BLOOD_TYPE_LENGTH] = {"AB+", "AB-", "A+", "A-", "B+", "B-", "O+", "O-"};

    printf("List of predecessors: ");
    for (int i = 0; i < size; i++) {
        if (*(matrix + i * size + node) == 1) {
            printf("%s ; ", bloodTypes[i]);
        }
    }
    printf("\n");
}

void showSuccessors(int *matrix, int node, int size) {
    node--;

    char bloodTypes[BLOOD_TYPES][BLOOD_TYPE_LENGTH] = {"AB+", "AB-", "A+", "A-", "B+", "B-", "O+", "O-"};

    printf("List of successors: ");
    for (int i = 0; i < size; i++) {
        if (*(matrix + i + node * size) == 1) {
            printf("%s ; ", bloodTypes[i]);
        }
    }
    printf("\n");
}

int main() {
    printf("Enter the number of blood types: ");
    int size;
    scanf("%d", &size);

    if (size <= 0 || size > BLOOD_TYPES) {
        printf("Invalid input. Blood types must be between 1 and %d.\n", BLOOD_TYPES);
        return 1;
    }

    int *adjacencyMatrix = createAdjacencyMatrix(size);

    printf("\nAdjacency Matrix:\n");
    printMatrix(adjacencyMatrix, size);

    printf("\nEnter a blood type (1 to %d) to get information: ", size);
    int chosenBloodType;
    scanf("%d", &chosenBloodType);

    if (chosenBloodType <= 0 || chosenBloodType > size) {
        printf("Invalid input. Choose a blood type between 1 and %d.\n", size);
        free(adjacencyMatrix);
        return 1;
    }

    int predecessors = countPredecessors(adjacencyMatrix, chosenBloodType, size);
    printf("\nTotal number of predecessors: %d\n", predecessors);
    showPredecessors(adjacencyMatrix, chosenBloodType, size);

    int successors = countSuccessors(adjacencyMatrix, chosenBloodType, size);
    printf("\nTotal number of successors: %d\n", successors);
    showSuccessors(adjacencyMatrix, chosenBloodType, size);

    free(adjacencyMatrix);

    return 0;
}
