#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid;
    int at;  
    int bt;    
    int prio;   
    int ct;     
    int tat;    
    int wt;     
    int rt;     
    bool done;  
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;
        cout << "Enter arrival time, burst time and priority for P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].prio;
        p[i].done = false;
    }

    int completed = 0, curr_time = 0;
    while (completed < n) {
        int idx = -1;
        int min_prio = 1e9;

        for (int i = 0; i < n; ++i)
        {
            if (!p[i].done && p[i].at <= curr_time) 
            {
                if (p[i].prio < min_prio) 
                {
                    min_prio = p[i].prio;
                    idx = i;
                } 
                else if (p[i].prio == min_prio) 
                {
                    if (p[i].at < p[idx].at) 
                    {
                        idx = i;
                    }
                }
            }
        }
        if (idx == -1) 
        {
            curr_time++; 
        } else {
            p[idx].ct = curr_time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].wt; 
            p[idx].done = true;
            curr_time = p[idx].ct;
            completed++;
        }
    }
    cout << "\nProcess\tAT\tBT\tPrio\tCT\tTAT\tWT\tRT\n";
    for (const auto& proc : p) {
        cout << "P" << proc.pid << "\t"
             << proc.at << "\t"
             << proc.bt << "\t"
             << proc.prio << "\t"
             << proc.ct << "\t"
             << proc.tat << "\t"
             << proc.wt << "\t"
             << proc.rt << "\n";
    }
}
