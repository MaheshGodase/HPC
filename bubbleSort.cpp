#include<iostream>
#include<omp.h>

using namespace std;

void bubbleSort(int arr[], int length){

    for(int i = 0; i < length; i++){

        for(int j = 0; j < length-1; j++){
            
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void parallelBubbleSort(int arr[], int length){

    int first;
    for(int i = 0; i < length-1; i++){

        first = i % 2;

        #pragma omp parallel for shared(arr,first,length)
        for(int j = first; j < length-1; j++){
            
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(){

    int arrSize = 100000;
    int arr[arrSize];

    for(int i=0; i<arrSize; i++){

        arr[i] = rand() % arrSize;
    }

    double startTime = omp_get_wtime();
    bubbleSort(arr, arrSize);   
    double endTime = omp_get_wtime();

    double startTimeParallel = omp_get_wtime();
    parallelBubbleSort(arr, arrSize);   
    double endTimeParallel = omp_get_wtime();

    std :: cout<<"After Sorting : ";
    for(int i = 0; i < arrSize; i++){
        std :: cout<<arr[i]<<" ";
    }

    std :: cout<<std :: endl;
    std :: cout<<"Time taken For Sequentially : "<<endTime - startTime<<std :: endl;
    std :: cout<<"Time taken For Parallely : "<<endTimeParallel - startTimeParallel<<std :: endl;
    return 0;
}