#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <unistd.h>
#include <math.h>

#include<climits> // just for tests

#define N 10 // just for tests

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
    int totalSwaps = int(shufflePercentage * vec.size());
    // cout << totalSwaps << endl;
    while (nSwaps < totalSwaps){
        int idx1 = rand() % vec.size();
        int idx2 = rand() % vec.size();
        swap(vec[idx1], vec[idx2]);
        // cout << idx1 << " " << idx2 << endl;
        nSwaps = nSwaps + 1;
    }
    cout << endl;
}

int kthSmallestProfit(vector<int> vec, int low, int high, int k){
    /// Modifies vector, so parameter is passed by copy, not by reference
    // nth_element(0, 0 + k - 1, vec.size());
    vector<int>::iterator l = vec.begin() + low;
    vector<int>::iterator h = vec.begin() + high;
    nth_element(l, l + k - 1, h);
    // th_element(vec.begin(), vec.begin() + k - 1, vec.end());
    return vec[k-1];
}

int setPivotForIteractive(vector<int> &vec, int low, int high, int c){
    int pivot = -1;
    switch (c){
        case(1):  // pivot is the median of array
            // cout << "STARTING" << endl;
            // printVector(vec);
            // cout << "low: " << low << " high: " << high << endl;
            // pivot = kthSmallestProfit(vec, low, high, round(high - low + 1) / 2.)));
            // (low + high + 1 / 2.) gives me the middle element
            pivot = kthSmallestProfit(vec, low, high, round((low + high + 1) / 2.));
            // pivot = vec[low];
            // cout << "Pivot: " << pivot << endl;
            // printVector(vec);
            // cout << pivot << endl;
            // exit(9);
            break;
        case(2):  // pivot is a random element
            pivot = vec[low + rand() % (high - low + 1)];
            break;
        case(3):  // pivot is a mean of 3 values
            pivot = (vec[low] + vec[(low + high) / 2] + vec[high]) / 3;
            break;
        case(4):  // Raul's algorithm
            // int pivot;
            // printVector(vec);
            // cout << "low: " << low << " high: " << high << endl;
            for (int i = low; i < high; i ++){
                if (vec[i+1] < vec[i]){
                    pivot = vec[i+1];
                    // exit(33);
                    break;
                }
            }
            // cout << "Pivot after calculating: " << pivot << endl;
            break;
        case(5):  // pivot is the median of three, middle, first and last elements of partition
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
        case(6):  // pivot is the last element
            pivot = vec[high];
            break;
        default:
            cout << "Pivoting method not found, exiting.\n" << endl;
            exit(1);
    }
    return pivot;
}

void iterativeQuickSort(vector<int> &vec, int low, int high, int pivotingMethod){
    /// Pivot could be anywhere in vector
	int i = low;
	int j = high;
	// int pivot = vec[low + (high - low) / 2];
	int pivot = setPivotForIteractive(vec, low, high, pivotingMethod);
	if (pivot != -1){  // For Raul's algorithm, if pivot == -1, the array is already sorted
        while (i <= j){
            while (vec[i] < pivot){
                i++;
            }
            while (vec[j] > pivot){
                j--;
            }
            if (i <= j){
                swap(vec[i],vec[j]);
                i++;
                j--;
            }
        }
        if (low < j){
            iterativeQuickSort(vec, low, j, pivotingMethod);
        }
        if (i < high){
            iterativeQuickSort(vec, i, high, pivotingMethod);
        }
	}
}

int main(int argc, char* argv[])
{
    /**
    PivotingMethod = 1 -> median of list
                     2 -> random value
                     3 -> arithmetic mean of three (first, middle and last elements)
                     4 -> custom algorithm by Raul (drop down?!)
                     5 -> *optional* median of three (first, middle and last elements)
                     6 -> *optional* last element
    **/
    int c;
    int seed = 1;
    int pivotingMethod = 2; // pivoting method
    int nSize = 10; // vector size
    float shufflePercentage = 1; // porcentage of vector that will be shuffled [0,1]
    while ((c = getopt(argc, argv, "s:m:n:p:")) != -1) {
        cout << "Reading Parameters" << endl;
    	switch (c) {
    		case 's': seed = atoi(optarg); break;
    		case 'm': pivotingMethod = atoi(optarg); break;
    		case 'n': nSize = atoi(optarg); break;
    		case 'p': shufflePercentage = atof(optarg); break;
			default: abort();
    	}
    }
    srand(seed);
    vector<int> vec;
    fillVector(vec, nSize);
    swapValues(vec, shufflePercentage);
    printVector(vec);

    // Calculate the time taken by quickSort
    auto start = high_resolution_clock::now();
    iterativeQuickSort(vec, 0, vec.size()-1, pivotingMethod);
    auto stop = high_resolution_clock::now();
    auto timeTaken = duration_cast<microseconds>(stop-start);
    cout << "Time taken by quickSort: " << timeTaken.count() << " microseconds" << endl;
    printVector(vec);
    return 0;
}
