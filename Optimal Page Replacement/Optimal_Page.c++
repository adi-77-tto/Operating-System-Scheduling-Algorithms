#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int predict(vector<int> pages, vector<int> &memory, int index, int n) {
    int res = -1, farthest = index;
    for (int i = 0; i < memory.size(); i++) {
        int j;
        for (j = index; j < n; j++) 
        {
            if (memory[i] == pages[j]) 
            {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n) return i;
    }
    return res;
}

int main() {
    int n, frames;
    cout << "Enter number of pages: ";
    cin >> n;
    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];
    cout << "Enter number of frames: ";
    cin >> frames;
    vector<int> memory;
    int faults = 0;

    for (int i = 0; i < n; i++) 
    {
        if (find(memory.begin(), memory.end(), pages[i]) == memory.end()) 
        {
            if (memory.size() < frames) 
            {
                memory.push_back(pages[i]);
            } 
            else 
            {
                int pos = predict(pages, memory, i + 1, n);
                memory[pos] = pages[i];
            }
            faults++;
        }
    }
    
    int hits = n - faults;
    cout << "Total Page Faults: " << faults << endl;
    cout << "Hit ration: " << (float)hits/n * 100 <<"%" << endl;
    cout << "Miss ration: " << (float)faults/n * 100 <<"%" << endl;
    return 0;
}
