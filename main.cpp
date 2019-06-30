#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <unistd.h>
#include <math.h>
#include <fstream>
#include <string.h>
#include <iomanip> // for stringstream
#include <time.h>
#include <climits>




using namespace std;
using namespace std::chrono;

void printVector(vector<int> &vec){
    for (auto i : vec){
        cout << i << " ";
    }
    cout << endl;
}

void checkShuffle(vector<int> &vec){
    int shuffled = 0;
    int i = 0;
    while ( i < vec.size()){
        if (vec[i] != ++i){
            shuffled = shuffled + 1;
        }
    }
    cout << "There is " << shuffled << " out of " << vec.size() << " or " << shuffled/float(vec.size()) * 100 << "% shuffled" << endl;
}

void fillVector(vector<int> &vec, size_t vecSize){
    int i = 0;
    while(vec.size() < vecSize){
        vec.push_back(++i);
    }
}

void swapValues(vector<int> &vec, double shufflePercentage){ // shufflePercentage between [0,1]
    int nSwaps = 0;
    int totalSwaps = int(shufflePercentage * vec.size());
    while (nSwaps <= totalSwaps){
        int idx1 = rand() % vec.size();
        int idx2 = rand() % vec.size();
        swap(vec[idx1], vec[idx2]);
        nSwaps = nSwaps + 1;
    }
    cout << endl;
}

/* In case someone wants to pass in the pivValue, I broke partition into 2 pieces.
 */
int pivot(vector<int>& vec, int pivot, int start, int end){

    /* Now we need to go into the array with a starting left and right value. */
    int left = start, right = end-1;
    while(left < right){
        /* Increase the left and the right values until inappropriate value comes */
        while(vec.at(left) < pivot && left <= right) left++;
        while(vec.at(right) > pivot && right >= left) right--;

        /* In case of duplicate values, we must take care of this special case. */
        if(left >= right) break;
        else if(vec.at(left) == vec.at(right)){ left++; continue; }

        /* Do the normal swapping */
        int temp = vec.at(left);
        vec.at(left) = vec.at(right);
        vec.at(right) = temp;
    }
    return right;
}

/* Returns the k-th element of this array. */
int MoM(vector<int> vec, int k, int start, int end){
    /* Start by base case: Sort if less than 10 size
     * E.x.: Size = 9, 9 - 0 = 9.
     */
    if(end-start < 10){
        sort(vec.begin()+start, vec.begin()+end);
        return vec.at(k);
    }

    vector<int> medians;
    /* Now sort every consecutive 5 */
    for(int i = start; i < end; i+=5){
        if(end - i < 10){
            sort(vec.begin()+i, vec.begin()+end);
            medians.push_back(vec.at((i+end)/2));
        }
        else{
            sort(vec.begin()+i, vec.begin()+i+5);
            medians.push_back(vec.at(i+2));
        }
    }

    int median = MoM(medians, medians.size()/2, 0, medians.size());

    /* use the median to pivot around */
    int piv = pivot(vec, median, start, end);
    int length = piv - start+1;

    if(k < length){
        return MoM(vec, k, start, piv);
    }
    else if(k > length){
        return MoM(vec, k-length, piv+1, end);
    }
    else
        return vec[k];
}

int kthSmallestProfit(vector<int> vec, int low, int high, int k){
    // Modifies vector, parameter must be passed by copy, not by reference
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
            //int k = (6+0) /2.;
            //int kth = MoM(v, k, 0, v.size());
            pivot = MoM(vec, (high + low) / 2., low, high);
            //
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
	int i = low;
	int j = high;
	int pivot = setPivotForIteractive(vec, low, high, pivotingMethod);
	if (pivot != -1){  // For Drop Down, if pivot == -1, the array is already sorted
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

void runTests(vector<int> &vec, int seed, int pivotingMethod, int nSize, float shufflePercentage){
    fstream file;
    stringstream ss;
    ss << fixed << setprecision(2) << shufflePercentage;
    string strShufflePercentage = ss.str();
    // cout << strShufflePercentage;
    // arr_nSize_shufflePercentage.txt | Ex: arr_10_0.1.txt
    file.open("data_results/arr_" + to_string(nSize) + "_" + strShufflePercentage + ".txt", fstream::app);

    if (seed == 1 && pivotingMethod == 1){  // set header
        file << "Median\t" << "Random\t" << "Mean\t" << "Drop Down\n";
    }

    // printVector(vec);

    // Calculate the time taken by quickSort
    auto start = high_resolution_clock::now();
    iterativeQuickSort(vec, 0, vec.size()-1, pivotingMethod);
    auto stop = high_resolution_clock::now();
    auto timeTaken = duration_cast<nanoseconds>(stop-start);
    auto elapsedTime = duration_cast<microseconds>(stop-start);
    cout << "Time taken by quickSort: " << timeTaken.count() << " nanoseconds" << endl;
    cout << "Time taken by quickSort: " << elapsedTime.count() << " microseconds" << endl;
    file << timeTaken.count();
    if (pivotingMethod < 4){
        file <<"\t";
    }
    else if(pivotingMethod == 4){
        file << "\n";
    }
    file.close();
    // printVector(vec);
}

void runTerm(vector<int> &vec, int seed, int pivotingMethod, int nSize, float shufflePercentage){
    //printVector(vec);

    // Calculate the time taken by quickSort
    auto start = high_resolution_clock::now();
    iterativeQuickSort(vec, 0, vec.size()-1, pivotingMethod);
    auto stop = high_resolution_clock::now();
    auto timeTaken = duration_cast<nanoseconds>(stop-start);
    auto elapsedTime = duration_cast<microseconds>(stop-start);
    cout << "Time taken by quickSort: " << timeTaken.count() << " nanoseconds" << endl;
    cout << "Time taken by quickSort: " << elapsedTime.count() << " microseconds" << endl;
    //printVector(vec);
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
    int seed = 14;
    int pivotingMethod = 1; // pivoting method
    int nSize = 1000000; // vector size
    float shufflePercentage = 0.35; // percentage of vector that will be shuffled [0,1]
    /*
        shufflePercentage = 0.05 -> approx 8-10% of vector will be shuffled
        shufflePercentage = 0.35 -> approx 49-51% of vector will be shuffled
        shufflePercentage = 1.1 -> approx 88-90% of vector will be shuffled
    */
    while ((c = getopt(argc, argv, "s:m:n:p:")) != -1) {
        // cout << "Reading Parameters" << endl;
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
    checkShuffle(vec);
    // Running tests on terminal
    runTerm(vec, seed, pivotingMethod, nSize, shufflePercentage);
    // Running tests on files
    // runTests(vec, seed, pivotingMethod, nSize, shufflePercentage);
    //vector<int> v = {12, 3, 5, 7, 4, 19, 26}; // 3 4 5 7 12 19 26 | 27 28
    //int k = (6+0) /2.;
    //int kth = MoM(v, k, 0, v.size());
    // int kth1 = kthSmallest(v, 0, 6, 3);
    //cout << kth << endl;
    //printVector(v);
    // cout << "K'th smallest element is " << kthSmallest(arr, 0, n-1, k);

    if(is_sorted(vec.begin(), vec.end())){
        cout << "Sorted" << endl;
    }
    return 0;
}
