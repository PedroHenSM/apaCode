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
        case(4):  // Raul's algorithm
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
            cout << "precisa implementar" << endl;
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

int selection (int *a, int ini, int fim, int k){
    int pivotIndex, pivotValue,auxIndex;
    int i;
    pivotIndex = (ini+fim)/2;  //não-randômico
    pivotValue = a[pivotIndex];
    swap(a[pivotIndex], a[fim]);
    auxIndex = ini;
    for(i = ini; i< fim; i++){
        if(a[i] < pivotValue){
            swap(a[auxIndex], a[i]);
            auxIndex = auxIndex+1;
        }
    }
    swap(a[auxIndex], a[fim]);
    if(k == auxIndex)
        return a[k];
    else if (k < auxIndex )
        return selection(a, ini, auxIndex-1,k);
    else
        return selection(a,auxIndex+1, fim, k);
}

int partitionMed(int arr[], int l, int r, int k);

int findMedian(int arr[], int n)
{
    sort(arr, arr+n);  // Sort the array
    return arr[n/2];   // Return middle element
}

// Returns k'th smallest element in arr[l..r] in worst case
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT
int kthSmallest(int arr[], int l, int r, int k)
{
    // If k is smaller than number of elements in array
    if (k > 0 && k <= r - l + 1)
    {
        int n = r-l+1; // Number of elements in arr[l..r]

        // Divide arr[] in groups of size 5, calculate median
        // of every group and store it in median[] array.
        int i, median[(n+4)/5]; // There will be floor((n+4)/5) groups;
        for (i=0; i<n/5; i++)
            median[i] = findMedian(arr+l+i*5, 5);
        if (i*5 < n) //For last group with less than 5 elements
        {
            median[i] = findMedian(arr+l+i*5, n%5);
            i++;
        }

        // Find median of all medians using recursive call.
        // If median[] has only one element, then no need
        // of recursive call
        int medOfMed = (i == 1)? median[i-1]:
                                 kthSmallest(median, 0, i-1, i/2);

        // Partition the array around a random element and
        // get position of pivot element in sorted array
        int pos = partitionMed(arr, l, r, medOfMed);

        // If position is same as k
        if (pos-l == k-1)
            return arr[pos];
        if (pos-l > k-1)  // If position is more, recur for left
            return kthSmallest(arr, l, pos-1, k);

        // Else recur for right subarray
        return kthSmallest(arr, pos+1, r, k-pos+l-1);
    }

    // If k is more than number of elements in array
    return INT_MAX;
}

void swapMed(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// It searches for x in arr[l..r], and partitions the array
// around x.
int partitionMed(int arr[], int l, int r, int x)
{
    // Search for x in arr[l..r] and move it to end
    int i;
    for (i=l; i<r; i++)
        if (arr[i] == x)
           break;
    swapMed(&arr[i], &arr[r]);

    // Standard partition algorithm
    i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            swapMed(&arr[i], &arr[j]);
            i++;
        }
    }
    swapMed(&arr[i], &arr[r]);
    return i;
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
    int pivotingMethod = 4; // pivoting method
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
    vector<int> vec;/// = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

    int arr[] = {22, 99, 32, 88, 34, 33, 11, 97, 55};// {4,8,1,6,3,7,2,5};
    fillVector(vec, nSize);
    swapValues(vec, shufflePercentage);
    printVector(vec);
    //vec = {22, 99, 32, 88, 34, 33, 11, 97, 55, 66}; /// 11, 22, 32, 33, 34, 55, 88, 97, 99

    /*
    sort(vec.begin(), vec.end());
    printVector(vec);
    int l = 0;
    int h = vec.size() - 1;
    /// v.begin() + v.size() / 2
    int k = round((l + h + 1) / 2.);
    cout << "k " << k << endl;
    int kth = kthSmallestProfit(vec, l, h, k); /// O(n) at worst case
    cout << "kth: " << kth << endl;
    exit(8);
    */

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
