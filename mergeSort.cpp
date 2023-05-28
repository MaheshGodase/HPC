#include <iostream>
#include <omp.h>

using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int L[n1], R[n2];
    
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
        
    i = 0;
    j = 0;
    k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) { 
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void parallelMergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, left, mid);
            }
            
            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, right);
            }
        }
        
        merge(arr, left, mid, right);
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
               
        mergeSort(arr, left, mid);
           
        mergeSort(arr, mid + 1, right);
            
        merge(arr, left, mid, right);
    }
}

int main() {

    int sizeArr = 100000;
    int arr[sizeArr];
    int arr2[sizeArr];

    for(int i = 0; i < sizeArr; i++){
        arr[i] = rand() % sizeArr;
        arr2[i] = rand() % sizeArr;
    } 

    double startTime = omp_get_wtime();
    mergeSort(arr, 0, sizeArr - 1);
    double endTime = omp_get_wtime();

    double parallelStartTime = omp_get_wtime();
    parallelMergeSort(arr2, 0, sizeArr - 1);
    double parallelEndTime = omp_get_wtime();

    
    cout << "\nSorted array is: ";
    for (int i = 0; i < sizeArr; i++)
        cout << arr[i] << " ";
    cout << endl;
    
    cout<<"The sequential time is : " << endTime - startTime<<endl;

    cout<<"The Parallel time is : " << parallelEndTime - parallelStartTime<<endl;

    return 0;
}
