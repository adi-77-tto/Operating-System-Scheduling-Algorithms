
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, frames;
    cout << "Enter number of pages: ";
    cin >> n;
    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int &p : pages) cin >> p;

    cout << "Enter number of frames: ";
    cin >> frames;
    vector<int> mem; 
    int faults = 0;
    for (int i = 0; i < n; i++) {
        int current = pages[i];
        if (find(mem.begin(), mem.end(), current) == mem.end()) 
        {
            if (mem.size() == frames) 
            {
                mem.erase(mem.begin());
            }
            mem.push_back(current);
            faults++;
        }
    }
    int hits = n - faults;
    cout << "Total Page Faults: " << faults << endl;
    cout << "Hit ratio: " << (float)hits/n * 100  << endl;
    cout << "Miss ratio: " << (float)faults/n * 100  << endl;
    return 0;
}
