#include <iostream>
#include <windows.h>
#include <process.h>
#include <ctime>
using namespace std;

const int MAX = 100;

int *buffer;
int buf_pos = -1, buf_size;
int producer_count, consumer_count;

HANDLE mutex;
HANDLE empty_slots;
HANDLE full_slots;
HANDLE cout_mutex; // Mutex for printing to console

unsigned __stdcall producer(void* param) {
    int id = *(int*)param;
    delete (int*)param; // Free memory

    while (true) {
        int item = 1 + rand() % 40;

        WaitForSingleObject(cout_mutex, INFINITE);
        cout << "Producer " << id << " produced " << item << endl;
        ReleaseMutex(cout_mutex);

        WaitForSingleObject(empty_slots, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        buffer[++buf_pos] = item;

        ReleaseMutex(mutex);
        ReleaseSemaphore(full_slots, 1, NULL);

        Sleep(1000 + rand() % 2000);
    }
    return 0;
}

unsigned __stdcall consumer(void* param) {
    int id = *(int*)param;
    delete (int*)param; // Free memory

    while (true) {
        WaitForSingleObject(full_slots, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        int item = buffer[buf_pos--];

        ReleaseMutex(mutex);

        WaitForSingleObject(cout_mutex, INFINITE);
        cout << "Consumer " << id << " consumed " << item << endl;
        ReleaseMutex(cout_mutex);

        ReleaseSemaphore(empty_slots, 1, NULL);

        Sleep(1000 + rand() % 3000);
    }
    return 0;
}

int main() {
    srand((unsigned)time(NULL));

    cout << "Enter number of producers: ";
    cin >> producer_count;

    cout << "Enter number of consumers: ";
    cin >> consumer_count;

    cout << "Enter buffer size: ";
    cin >> buf_size;
    buffer = new int[buf_size];

    mutex = CreateMutex(NULL, FALSE, NULL);
    empty_slots = CreateSemaphore(NULL, buf_size, buf_size, NULL);
    full_slots = CreateSemaphore(NULL, 0, buf_size, NULL);
    cout_mutex = CreateMutex(NULL, FALSE, NULL); // Initialize cout mutex

    for (int i = 0; i < producer_count; ++i) {
        int* id = new int(i + 1);
        _beginthreadex(NULL, 0, producer, id, 0, NULL);
    }

    for (int i = 0; i < consumer_count; ++i) {
        int* id = new int(i + 1);
        _beginthreadex(NULL, 0, consumer, id, 0, NULL);
    }

    // Let the main thread run for 10 seconds before terminating
    Sleep(20000);

    delete[] buffer;
    CloseHandle(mutex);
    CloseHandle(empty_slots);
    CloseHandle(full_slots);
    CloseHandle(cout_mutex); // Close cout mutex

    return 0;
}
