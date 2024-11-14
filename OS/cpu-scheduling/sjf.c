#include <stdio.h>
#include <string.h>

void printTable(int n, int id[n], int bt[n], int at[n], int tat[n], int wt[n]) {
    int avgT=0, avgW=0;
    printf("Process ID:\tArrival Time:\tBurst Time:\tTurn Around Time:\tWait Time:\n");
    for(int i=0; i<n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", id[i], at[i], bt[i], tat[i], wt[i]);
        avgT += tat[i];
        avgW += wt[i];
    }
    printf("Average Turn Around Time: %f\n", (float)avgT/n);
    printf("Average Waiting Time: %f\n", (float)avgW/n);
}

void printGanttChart(int n, int id[], int start[], int end[]) {
    printf("\nGantt Chart:\n");
    
    // Print process blocks
    printf(" |");
    for(int i = 0; i < n; i++) {
        int length = end[i] - start[i];
        printf(" P%d ", id[i] + 1);
        for (int j = 0; j < length - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n");

    // Print timeline
    printf("%d", start[0]);
    for(int i = 0; i < n; i++) {
        int length = end[i] - start[i];
        for(int j = 0; j < length + 3; j++) printf(" ");
        printf("%d", end[i]);
    }
    printf("\n");
}

void sjf(int n, int bt[n], int at[n], int tat[n], int wt[n], int id[n], int start[n], int end[n]) {
    int completed = 0, time = 0;
    int completedProcesses[n];
    memset(completedProcesses, 0, sizeof(completedProcesses));

    while (completed < n) {
        int minBurstTime = 1e9, index = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && completedProcesses[i] == 0 && bt[i] < minBurstTime) {
                minBurstTime = bt[i];
                index = i;
            }
        }

        if (index != -1) {
            start[index] = time;          // Record start time
            time += bt[index];
            end[index] = time;            // Record end time
            tat[index] = end[index] - at[index];
            wt[index] = tat[index] - bt[index];
            completedProcesses[index] = 1;
            completed++;
        } else {
            time++;
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int id[n], at[n], bt[n], wt[n], tat[n], start[n], end[n];

    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &bt[i]);
        id[i] = i;
    }

    sjf(n, bt, at, tat, wt, id, start, end);
    printTable(n, id, bt, at, tat, wt);
    printGanttChart(n, id, start, end);

    return 0;
}
