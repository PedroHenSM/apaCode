#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

void printVector(vector<int> &vec){
    for (auto i : vec){
        cout << i << " ";
    }
    cout << endl;
}

void fillVector(vector<int> &vec, size_t vecSize){
    int i = 0;

    while(vec.size() < vecSize){
        vec.push_back( ++i);
    }
}

void swapValues(vector<int> &vec, double shufflePercentage){ // shufflePercentage between [0,1]
    int nSwaps = 0;
    int totalSwaps = shufflePercentage * vec.size();
    // cout << totalSwaps << endl;
    while (nSwaps < totalSwaps){
        int idx1 = rand() % vec.size();
        int idx2 = rand() % vec.size();
        swap(vec[idx1], vec[idx2]);
        // cout << idx1 << " " << idx2 << endl;
        nSwaps++;
    }
    cout << endl;
}


void setPivot(vector<int> &vec, int &pivot, int low, int high, int c){
    switch (c){
        case(1):  // pivot is the last element of partition
            pivot = vec[high];
            break;
        case(2):  // pivot is the first element of partition
            swap(vec[low],vec[high]);
            pivot = vec[high];
            break;
        case(3):  // pivot is the median of three, middle and last elements of partition
            int middle;
            middle = (high + low) / 2;
            if(vec[middle] < vec[low]){
                swap(vec[low], vec[middle]);
            }
            if(vec[high] < vec[low]){
                swap(vec[low], vec[high]);
            }
            if(vec[middle], vec[high]){
                swap(vec[middle], vec[high]);
            }
            pivot = vec[high];
            break;
        case(4):  // pivot is a random number of partition
            swap(vec[low + rand() % (high - low)], vec[high]);
            pivot = vec[high];
            break;
        default:
            cout << "Pivoting method not found, exiting.\n" << endl;
            exit(1);
    }
}

/*
Auxiliar function for quickSort thatplaces the pivot element at
its correct position in sorted array, and places all the smaller
to the left and greaters to the right
*/

int partition(vector<int> &vec, int low, int high){
    int pivot;
    setPivot(vec, pivot, low, high, 3);
    int i = (low - 1);  // index of smaller element of actual partition

    for (int j = low; j <= high - 1; j++){
        // Current element smaller or equal than pivot?
        if(vec[j] <= pivot){
            // increaser index and then swap
            i++;
            swap(vec[i],vec[j]);
        }
    }
    swap(vec[i+1], vec[high]);
    return i + 1;
}


/*
Main function that implements quickSort
*/
void quickSort(vector<int> &vec, int low, int high){
    if (low < high){
        // pi is partitioning index, vec[p] is at right place
        int pi = partition(vec, low, high);
        // Calls quicksort for both halves
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}


int main()
{
    srand(1);
    vector<int> vec;// = {1,2,3,4,5,5,6,7,8,9};
    int vecSize = 10;
    fillVector(vec, vecSize);
    swapValues(vec, 1);
    printVector(vec);
    // Calculate the time taken by quickSort
    auto start = high_resolution_clock::now();
    quickSort(vec, 0, vec.size()-1);
    auto stop = high_resolution_clock::now();
    auto timeTaken = duration_cast<microseconds>(stop-start);
    cout << "Time taken by quickSort: " << timeTaken.count() << "microseconds" << endl;
    printVector(vec);
    return 0;
}
