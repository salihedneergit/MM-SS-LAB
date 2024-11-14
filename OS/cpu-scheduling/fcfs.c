#include <stdio.h>

void displayGanttChart(int n, int at[], int bt[], int ct[]);

int main() {
    int n, i;
    float totalTAT = 0, totalWT = 0;
    
    printf("Enter the total number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n];

    // Input Arrival Time and Burst Time
    for (i = 0; i < n; i++) {
        printf("Enter Arrival time of process[%d]: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst time of process[%d]: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Calculate Completion Time
    int time = at[0];  // Initialize time with arrival time of first process
    for (i = 0; i < n; i++) {
        if (time < at[i]) { // Ensure process starts after arrival
            time = at[i];
        }
        time += bt[i];
        ct[i] = time;
    }

    // Calculate Turnaround Time and Waiting Time
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];         // Turnaround Time
        wt[i] = tat[i] - bt[i];         // Waiting Time
        totalTAT += tat[i];
        totalWT += wt[i];
    }

    // Print table header
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    // Print each process's details
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    // Calculate and print averages
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Waiting Time: %.2f\n", totalWT / n);

    // Display Gantt Chart
    displayGanttChart(n, at, bt, ct);

    return 0;
}

// Function to display the Gantt Chart
void displayGanttChart(int n, int at[], int bt[], int ct[]) {
    printf("\nGantt Chart:\n");

    // Top border
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i]; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    // Process names
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i] - 1; j++) printf(" ");
        printf("P%d", i + 1);
        for (int j = 0; j < bt[i] - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");

    // Bottom border
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i]; j++) printf("--");
        printf(" ");
    }
    printf("\n");

    // Completion times
    int startTime = 0;
    printf("0");
    for (int i = 0; i < n; i++) {
        startTime += bt[i];
        printf("%*d", bt[i] * 2, ct[i]);
    }
    printf("\n");
}
