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
};

bool compareByArrival(const Process &a, const Process &b) {
    return a.at < b.at;
}

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
    sort(p.begin(), p.end(), compareByArrival);
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at)  currentTime = p[i].at;
        p[i].wt = currentTime - p[i].at;
        p[i].ct = currentTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        currentTime = p[i].ct;
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
