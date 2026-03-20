#include <stdio.h>
#include <stdbool.h>

// Function to check if the current system state is safe
bool isSafe(int n, int m, int avail[], int alloc[][m], int need[][m], int safeSeq[]) {
    int work[m];
    bool finish[n];

    for (int i = 0; i < m; i++) work[i] = avail[i];
    for (int i = 0; i < n; i++) finish[i] = false;

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                // If all needs of p[i] can be satisfied
                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        // If we couldn't find a process that can finish, it's unsafe
        if (!found) {
            return false; 
        }
    }
    return true;
}

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    // Using Variable Length Arrays (VLA)
    int alloc[n][m], max[n][m], avail[m], need[n][m];

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Max Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(int j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    // Calculate Need Matrix
    printf("\nNeed Matrix Calculated:\n");
    for(int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Initial Safety Check
    int safeSeq[n];
    if (isSafe(n, m, avail, alloc, need, safeSeq)) {
        printf("\nSystem is currently in a SAFE state.\nSafe Sequence is: ");
        for(int i = 0; i < n; i++) {
            printf("P%d ", safeSeq[i]);
            if(i != n - 1) printf("-> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is NOT in a safe state (Deadlock potential).\n");
        return 0; // Exit if initially unsafe
    }

    int reqProcess;
    printf("\n--- Make a New Resource Request ---\n");
    printf("Enter the Process ID making the request (0 to %d): ", n - 1);
    scanf("%d", &reqProcess);

    int request[m];
    printf("Enter the request for resources for P%d: ", reqProcess);
    for(int j = 0; j < m; j++) {
        scanf("%d", &request[j]);
    }

    // 1. Check if Request <= Need
    for(int j = 0; j < m; j++) {
        if(request[j] > need[reqProcess][j]) {
            printf("\nError: Process has exceeded its maximum claim.\n");
            return 0;
        }
    }

    // 2. Check if Request <= Available
    for(int j = 0; j < m; j++) {
        if(request[j] > avail[j]) {
            printf("\nProcess P%d must wait, resources are not available.\n", reqProcess);
            return 0;
        }
    }

    // 3. Pretend to allocate resources
    for(int j = 0; j < m; j++) {
        avail[j] -= request[j];
        alloc[reqProcess][j] += request[j];
        need[reqProcess][j] -= request[j];
    }

    // 4. Check safety again
    if (isSafe(n, m, avail, alloc, need, safeSeq)) {
        printf("\nRequest can be granted instantly! System is still in a SAFE state.\nNew Safe Sequence is: ");
        for(int i = 0; i < n; i++) {
            printf("P%d ", safeSeq[i]);
            if(i != n - 1) printf("-> ");
        }
        printf("\n");
    } else {
        printf("\nRequest CANNOT be granted. It would lead to an UNSAFE state.\n");
        // Rollback (optional, but good practice)
        for(int j = 0; j < m; j++) {
            avail[j] += request[j];
            alloc[reqProcess][j] -= request[j];
            need[reqProcess][j] += request[j];
        }
    }

    return 0;
}