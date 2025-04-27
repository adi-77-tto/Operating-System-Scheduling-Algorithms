#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define TIME_QUANTUM 2

struct Process {
    int pid, at, bt, remaining_time, ct, tat, wt;
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt;
        processes[i].remaining_time = processes[i].bt;
    }

    int time = 0, completed = 0;
    vector<int> gantt;
    queue<int> readyQueue;
    vector<bool> isInQueue(n, false);

    // Sort by arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    readyQueue.push(0);
    isInQueue[0] = true;

    while (completed < n) {
        if (!readyQueue.empty()) 
        {
            int i = readyQueue.front();
            readyQueue.pop();
            // Execution
            gantt.push_back(processes[i].pid);

            int execTime = min(TIME_QUANTUM, processes[i].remaining_time);
            time = max(time, processes[i].at); // In case CPU was idle
            time += execTime;
            processes[i].remaining_time -= execTime;

            // Check for newly arrived processes
            for (int j = 0; j < n; j++) {
                if (!isInQueue[j] && processes[j].at <= time && processes[j].remaining_time > 0) {
                    readyQueue.push(j);
                    isInQueue[j] = true;
                }
            }

            // If process not finished, re-queue it
            if (processes[i].remaining_time > 0) 
            {
                readyQueue.push(i);
            } 
            else 
            {
                processes[i].ct = time;
                processes[i].tat = processes[i].ct - processes[i].at;
                processes[i].wt = processes[i].tat - processes[i].bt;
                completed++;
            }
        } 
        else 
        {
            // CPU idle: find the next arriving process
            for (int j = 0; j < n; j++) 
            {
                if (!isInQueue[j]) {
                    time = processes[j].at;
                    readyQueue.push(j);
                    isInQueue[j] = true;
                    break;
                }
            }
        }
    }

    // Output Process Details
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto& p : processes) {
        cout << "P" << p.pid << "\t" << p.at << "\t" << p.bt << "\t" 
             << p.ct << "\t" << p.tat << "\t" << p.wt << "\n";
    }

    // Output Gantt Chart
    cout << "\nGantt Chart:\n| ";
    for (int i = 0; i < gantt.size(); i++) {
        if (i == 0 || gantt[i] != gantt[i - 1]) {
            cout << "P" << gantt[i] << " | ";
        }
    }
    cout << "\n";

    return 0;
}
