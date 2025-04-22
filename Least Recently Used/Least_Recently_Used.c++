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
    vector<int> memory;
    int faults = 0;

    for (int page : pages) 
    {
        auto it = find(memory.begin(), memory.end(), page);
        if (it == memory.end()) 
        {
            faults++;
            if (memory.size() == frames) memory.pop_back(); 
        } 
        else 
        {
            memory.erase(it); 
        }
        memory.insert(memory.begin(), page);
    }
    
    int hits = n - faults;
    cout << "Total Page Faults: " << faults << endl;
    cout << "Hit ration : " << (float)hits/n * 100 <<"%" << endl;
    cout << "Miss ration : " << (float)faults/n * 100 <<"%" << endl;
    return 0;
}
