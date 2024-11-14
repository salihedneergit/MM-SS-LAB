#include <stdio.h>
#include <string.h>

void printTable(int n, int id[], int at[], int bt[], int pt[], int ct[], int tat[], int wt[]) {
    float avgT = 0, avgW = 0;
    printf("\nProcess ID:\tArrival Time:\tBurst Time:\tPriority:\tCompletion Time:\tTurnaround Time:\tWaiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n", id[i] + 1, at[i], bt[i], pt[i], ct[i], tat[i], wt[i]);
        avgT += tat[i];
        avgW += wt[i];
    }
    printf("\nAverage Turnaround Time: %.2f", avgT / n);
    printf("\nAverage Waiting Time: %.2f\n", avgW / n);
}

void prioritySchedule(int n, int id[], int at[], int bt[], int pt[], int ct[], int tat[], int wt[]) {
    int completed = 0, time = 0;
    int isCompleted[n];
    memset(isCompleted, 0, sizeof(isCompleted));

    while (completed != n) {
        int idx = -1;
        int highestPriority = 100000;

        // Find the process with the highest priority among those that have arrived
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && isCompleted[i] == 0) {
                if (pt[i] < highestPriority) {
                    highestPriority = pt[i];
                    idx = i;
                }
                // If priorities are equal, choose the one with earlier arrival time
                else if (pt[i] == highestPriority) {
                    if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            // Process the selected process
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            isCompleted[idx] = 1;
            completed++;
        } else {
            // If no process has arrived yet, increment time (idle time)
            time++;
        }
    }
}

void displayGanttChart(int n, int id[], int at[], int bt[], int ct[], int pt[]) {
    printf("\nGantt Chart:\n");

    int time = 0;
    int isCompleted[n];
    memset(isCompleted, 0, sizeof(isCompleted));
    int completed = 0;

    // Gantt chart display logic
    printf(" ");
    while (completed < n) {
        int idx = -1;
        int highestPriority = 100000;

        // Find the process with highest priority among those that have arrived
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !isCompleted[i]) {
                if (pt[i] < highestPriority) {
                    highestPriority = pt[i];
                    idx = i;
                }
                // If priorities are equal, choose the one with earlier arrival time
                else if (pt[i] == highestPriority) {
                    if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            // Process the selected process
            for (int i = 0; i < bt[idx]; i++) {
                printf("--");
            }
            printf(" ");
            time += bt[idx];
            isCompleted[idx] = 1;
            completed++;
        } else {
            // Idle time
            printf("--");
            time++;
        }
    }
    printf("\n|");

    // Reset time and completed array for printing process IDs
    time = 0;
    memset(isCompleted, 0, sizeof(isCompleted));
    completed = 0;

    while (completed < n) {
        int idx = -1;
        int highestPriority = 100000;

        // Find the process with highest priority among those that have arrived
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !isCompleted[i]) {
                if (pt[i] < highestPriority) {
                    highestPriority = pt[i];
                    idx = i;
                }
                // If priorities are equal, choose the one with earlier arrival time
                else if (pt[i] == highestPriority) {
                    if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            // Print process ID
            for (int i = 0; i < bt[idx]; i++) {
                printf("P%d", id[idx] + 1);
            }
            printf(" ");
            time += bt[idx];
            isCompleted[idx] = 1;
            completed++;
        } else {
            // Idle time
            printf("  ");
            time++;
        }
    }
    printf("|\n ");

    // Bottom border for Gantt chart
    time = 0;
    memset(isCompleted, 0, sizeof(isCompleted));
    completed = 0;

    while (completed < n) {
        int idx = -1;
        int highestPriority = 100000;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !isCompleted[i]) {
                if (pt[i] < highestPriority) {
                    highestPriority = pt[i];
                    idx = i;
                }
                else if (pt[i] == highestPriority) {
                    if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            for (int i = 0; i < bt[idx]; i++) {
                printf("--");
            }
            printf(" ");
            time += bt[idx];
            isCompleted[idx] = 1;
            completed++;
        } else {
            printf("--");
            time++;
        }
    }
    printf("\n0");

    // Printing time labels at appropriate positions
    time = 0;
    memset(isCompleted, 0, sizeof(isCompleted));
    completed = 0;
    while (completed < n) {
        int idx = -1;
        int highestPriority = 100000;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !isCompleted[i]) {
                if (pt[i] < highestPriority) {
                    highestPriority = pt[i];
                    idx = i;
                }
                else if (pt[i] == highestPriority) {
                    if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            time += bt[idx];
            printf("%*d", bt[idx] * 2, time);
            isCompleted[idx] = 1;
            completed++;
        } else {
            time++;
            printf("  %d", time);
        }
    }
    printf("\n");
}

int main() {
    int n, temp;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int id[n], at[n], bt[n], wt[n], tat[n], pt[n], ct[n];

    printf("Enter Arrival Time, Burst Time, and Priority for each process (lower number = higher priority):\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority: ");
        scanf("%d", &pt[i]);
        id[i] = i;
    }

    // Sort processes by arrival time, then by priority if arrival times are equal
    for (int i = 0; i < n -1; i++) {
        for (int j = 0; j < n - i -1; j++) {
            if (at[j] > at[j+1] || (at[j] == at[j+1] && pt[j] > pt[j+1])) {
                // Swap arrival time
                temp = at[j];
                at[j] = at[j+1];
                at[j+1] = temp;

                // Swap burst time
                temp = bt[j];
                bt[j] = bt[j+1];
                bt[j+1] = temp;

                // Swap priority
                temp = pt[j];
                pt[j] = pt[j+1];
                pt[j+1] = temp;

                // Swap process id
                temp = id[j];
                id[j] = id[j+1];
                id[j+1] = temp;
            }
        }
    }

    prioritySchedule(n, id, at, bt, pt, ct, tat, wt);
    printTable(n, id, at, bt, pt, ct, tat, wt);
    displayGanttChart(n, id, at, bt, ct, pt);

    return 0;
}
