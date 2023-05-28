#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

using namespace std;
void min_reduction(int arr[], int length)
{
    int min_value = INT_MAX;

    //By using the reduction clause, each thread can perform the computation on a portion //of the array independently, updating its local minimum value. At the end, the 
//global minimum   value is obtained by combining the local minimum values from each //thread.
    #pragma omp parallel for reduction(min : min_value)
    for (int i = 0; i < length; i++)
    {
        if (arr[i] < min_value)
        {
            min_value = arr[i];
        }
    }
    cout << "Minimum value: " << min_value << endl;
}
void max_reduction(int arr[], int length)
{
    int max_value = INT_MIN;
    #pragma omp parallel for reduction(max : max_value)
    for (int i = 0; i < length; i++)
    {
        if (arr[i] > max_value)
        {
            max_value = arr[i];
        }
    }
    cout << "Maximum value: " << max_value << endl;
}
void sum_reduction(int arr[], int length)
{
    int sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < length; i++)
    {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;
}
void average_reduction(int arr[], int length)
{
    int sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < length; i++)
    {
        sum += arr[i];
    }
    cout << "Average: " << (double)sum / length << endl;
}

int main()
{
    int sizeArr = 100000;
    int arr[sizeArr];

    for(int i = 0; i < sizeArr; i++){
        arr[i] = rand() % sizeArr;
    } 

    double startTime = omp_get_wtime();
    min_reduction(arr, sizeArr);
    max_reduction(arr, sizeArr);
    sum_reduction(arr, sizeArr);
    average_reduction(arr, sizeArr);
    double endTime = omp_get_wtime();

    cout<<endl<<"Time Required For Execution : "<<endTime-startTime<<endl;

    // for(int i = 0; i < sizeArr; i++){
    //     cout<<arr[i]<<" ";
    // } 
}