#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id;
    int at;  
    int bt;  
    int ct;  
    int wt;  
    int tat; 
    bool done = false; 
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter Arrival Time for Process " << p[i].id << ": ";
        cin >> p[i].at;
        cout << "Enter Burst Time for Process " << p[i].id << ": ";
        cin >> p[i].bt;
    }
    int completed = 0, currentTime = 0;
    while (completed < n) {
        int idx = -1;
        int minBT = 1e9;

        for (int i = 0; i < n; i++) 
        {
            if (!p[i].done && p[i].at <= currentTime && p[i].bt < minBT)
             {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if (idx != -1) 
        {
            p[idx].wt = currentTime - p[idx].at;
            p[idx].ct = currentTime + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].done = true;
            currentTime = p[idx].ct;
            completed++;
        } 
        else currentTime++;
    }

    cout << "\nProcess\tAT\tBT\tCT\tWT\tTAT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].wt << "\t"
             << p[i].tat << endl;
    }
}
