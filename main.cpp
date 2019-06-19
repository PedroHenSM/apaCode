#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <unistd.h>

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


int setPivotForRecursive(vector<int> &vec, int low, int high, int c){
    /// Finds pivot and put it on the last position of vector
    int pivot;
    switch (c){
        case(1):  // pivot is the median of array
            cout << "precisa implementar" << endl;
            exit(9);
            break;
        case(2):  // pivot is a random element
            swap(vec[low + rand() % (high - low)], vec[high]);
            pivot = vec[high];
            break;
        case(3):  // pivot is a man of 3 values
            cout << "precisa implementar" << endl;
            exit(9);
            break;
        case(4):  // pivot is a random number of partition
            cout << "Algoritmo do Raul, precisa implementar" << endl;
            exit(9);
            break;
        case(5):  // pivot is the median of three, middle , first and last elements of partition
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

int setPivotForIteractive(vector<int> &vec, int low, int high, int c){
    int pivot;
    switch (c){
        case(1):  // pivot is the median of array
            cout << "precisa implementar" << endl;
            exit(9);
            break;
        case(2):  // pivot is a random element
            pivot = vec[low + rand() % (high - low)];
            break;
        case(3):  // pivot is a man of 3 values
            cout << "precisa implementar" << endl;
            exit(9);
            break;
        case(4):  // pivot is a random number of partition
            pivot = vec[low + rand() % (high - low)];
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

void achaPivo(vector<int> &vec, int n1, int n2, int &pto){
    int pos = n1+1;
    pto = 0;
    while(1){
        if (pos > n2){
            break;
        }
        else if (vec[pos] >= vec[pos-1]){
            pos = pos + 1;
        }
        else{
            pto = pos;
            break;
        }
    }
}

void particionaRaulzito(vector<int> &vec, int low, int high, int pivot){
	int i = low;
	int j = high;
	// int pivot = vec[low + (high - low) / 2];
	while (i > j){
        swap(vec[i], vec[j]);
		while (vec[i] < vec[pivot]){
			i++;
		}
		while (vec[j] > vec[pivot]){
			j--;
		}
	}
    // return pivot;
}

void quickRaulzito(vector<int> &vec, int n1, int n2){
    int p;
    // setPivot(vec, n1, n2, 1);
    int pto = n2;
    achaPivo(vec, n1, n2, pto);
    if (pto != 0){
        particionaRaulzito(vec, n1,n2, pto);
        quickRaulzito(vec,n1, pto);
        quickRaulzito(vec,pto+1, n2);
    }
}

int partition(vector<int> &vec, int low, int high, int pivotingMethod){
    /// Pivot must be in the last position of vector
    int pivot = setPivotForRecursive(vec, low, high, pivotingMethod);
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
// 4,8,1,6,3,7,2,5
/// Main function that implements quickSort
void quickSort(vector<int> &vec, int low, int high, int pivotingMethod){
    /// Pivot must be in the last position of vector
    if (low < high){
        // pi is partitioning index, vec[p]] is at right place
        int pi = partition(vec, low, high, pivotingMethod);
        // Calls quicksort for both halves
        quickSort(vec, low, pi - 1, pivotingMethod);
        quickSort(vec, pi + 1, high, pivotingMethod);
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
    int pivotingMethod = 1; // pivoting method
    int nSize = 10; // vector size
    float shufflePercentage = 0.1; // porcentage of vector that will be shuffled [0,1]
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
    vector<int> vec;// = {1,2,3,4,5,5,6,7,8,9};
    fillVector(vec, nSize);
    swapValues(vec, shufflePercentage);
    printVector(vec);
    // Calculate the time taken by quickSort
    auto start = high_resolution_clock::now();
    // quickSort(vec, 0, vec.size() -1, pivotingMethod);
    iterativeQuickSort(vec, 0, vec.size()-1, pivotingMethod);
    // quickRaulzito(vec, 0, vec.size()-1);
    auto stop = high_resolution_clock::now();
    auto timeTaken = duration_cast<microseconds>(stop-start);
    cout << "Time taken by quickSort: " << timeTaken.count() << "microseconds" << endl;
    printVector(vec);
    return 0;
}
