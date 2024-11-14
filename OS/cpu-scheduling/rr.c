#include <stdio.h>

typedef struct{
    int pid;
    int at;
    int bt;
    int rm;
    int tat;
    int cmp;
    int wt;
    int inQ;
} Process;

int front = -1, rear = -1;

void printTable(int n, Process proc[n]) {
    float avgT = 0, avgW = 0;
    printf("Process ID:\tArrival Time:\tBurst Time:\tCompletion Time:\tTurn Around Time:\tWaiting Time:\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].cmp, proc[i].tat, proc[i].wt);
        avgT += proc[i].tat;
        avgW += proc[i].wt;
    }
    printf("Average Turn Around Time: %.2f\n", avgT / n);
    printf("Average Waiting Time: %.2f\n", avgW / n);
}

void sortProcess(int n, Process proc[n]) {
    Process temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(proc[j].at > proc[j + 1].at) {
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

void enqueue(Process q[1000], Process pr) {
    if(front == -1) front = 0;
    q[++rear] = pr;
}

Process dequeue(Process q[1000]) {
    if(front == rear) {
        int k = front;
        front = -1;
        rear = -1;
        return q[k];
    } else {
        return q[front++];
    }
}

void displayGanttChart(int gantt[], int timeSlots) {
    printf("\nGantt Chart:\n");

    // Print top border
    printf(" ");
    for (int i = 0; i < timeSlots; i++) {
        printf("--");
    }
    printf("\n|");

    // Print process IDs in the chart
    for (int i = 0; i < timeSlots; i++) {
        if (gantt[i] == -1) {
            printf("  ");  // Idle time
        } else {
            printf("P%d", gantt[i]);
        }
    }
    printf("|\n ");

    // Print bottom border
    for (int i = 0; i < timeSlots; i++) {
        printf("--");
    }
    printf("\n");

    // Print time labels
    printf("0");
    for (int i = 1; i <= timeSlots; i++) {
        if (i == timeSlots || gantt[i] != gantt[i - 1]) {
            printf("%2d", i);  // Proper spacing for time labels
        } else {
            printf("  ");
        }
    }
    printf("\n");
}

void roundRobin(int n, Process proc[n], int quanta) {
    int completed = 0, time = proc[0].at;
    Process queue[1000];
    int gantt[1000];  // Array to store Gantt chart process IDs
    int timeSlots = 0;

    for(int i = 0; i < n; i++) proc[i].inQ = 0;

    enqueue(queue, proc[0]);
    proc[0].inQ = 1;

    while(completed < n) {
        // Allocate CPU
        if(rear == -1 && front == -1) {
            gantt[timeSlots++] = -1;  // Record idle time
            time++;
        } else {
            Process pr = dequeue(queue);
            int exeTime = pr.rm < quanta ? pr.rm : quanta;
            pr.rm -= exeTime;
            for (int i = 0; i < exeTime; i++) {
                gantt[timeSlots++] = pr.pid;  // Record each time slot in the Gantt chart
            }
            time += exeTime;

            // Add to queue any process that arrives during execution
            for(int i = 0; i < n; i++) {
                if(proc[i].at <= time && !proc[i].inQ && proc[i].rm > 0) {
                    proc[i].inQ = 1;
                    enqueue(queue, proc[i]);
                }
            }

            if(pr.rm <= 0) {
                completed++;
                for(int i = 0; i < n; i++) {
                    if(proc[i].pid == pr.pid) {
                        proc[i].cmp = time;
                        proc[i].tat = time - proc[i].at;
                        proc[i].wt = proc[i].tat - proc[i].bt;
                        break;
                    }
                }
            } else {
                pr.inQ = 1;
                enqueue(queue, pr);
            }
        }
    }

    // Display Gantt chart after completion
    displayGanttChart(gantt, timeSlots);
}

int main() {
    int n, quanta;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process proc[n];
    printf("Enter time quanta: ");
    scanf("%d", &quanta);

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for(int i = 0; i < n; i++) {
        printf("Process P%d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &proc[i].at);
        printf("Burst Time: ");
        scanf("%d", &proc[i].bt);
        proc[i].rm = proc[i].bt;
        proc[i].pid = i + 1;
    }

    sortProcess(n, proc);
    roundRobin(n, proc, quanta);
    printTable(n, proc);

    return 0;
}
