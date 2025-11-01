#include <iostream> 

//write a funcitonl bool hasTwoSum(int arr[], int n, int sum) that reutrns true is there exista t least one pari of ditince 

bool hasTwoSum(int arr[], int n, int sum){
    // for (int i = 0; i < n; i++){
    //     for (int j = 0; j < n; j++){ 
    //         if(j!= i){ 
    //             if(arr[j] + arr[i] == sum){
    //                 return true; 
    //             }
    //         }
    //     }
    // }

    for (int i = 0; i < n; i++){
            int j = n - i; 
        if (j != i)
        {
            if (arr[j] + arr[i] == sum)
            {
                return true;
            }
        }
        }
    }
    return false; 
}