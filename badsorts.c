/* badsorts.c
    - Steven Shi
    - Description: Contains awful sorting
      methods.
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/* swap()
  - takes in two ints and swaps them.
  - Returns 0 if successful, 1 if error
*/
int swap(int *x1, int *x2) {
  if (x1 == NULL || x2 == NULL) {
    perror("Error: swap() passed null pointer");
    return 1 ;
  }
  int temp = *x1 ;
  *x1 = *x2 ;
  *x2 = temp ;
  return 0 ;
}

/* validate()
  - n is size of array
  - returns 0 if array is sorted by ascending L -> R
  - returns 1 if array is not sorted
 */
int validate(int arr[], int n) {
  int i ;
  for (i = 0; i < n - 1 ; i++) {
    if (arr[i] > arr[i + 1]) {
      return 1 ;
    }
  }
  return 0 ;
}

/* randSwapSort()
  - n is size of array
  - Assumes seed is set for rand()
  - Swaps elements 69 times, validated(?), then tries again
  - returns number of shuffles done
*/
unsigned int randSwapSort(int arr[], int n) {
  int r1, r2, i ;
  unsigned int count = 0 ;
  while (validate(arr, n) != 0) {
    for (i = 0; i < 69; i++) {
      r1 = rand() % n ;
      do {
        r2 = rand() % n ;
      } while (r2 == r1) ;
      swap(&arr[r1], &arr[r2]) ;
    }
    count++ ;
  }
  return count ;
}

int printArray(int arr[], int size) {
    int i ;
    printf("[") ;
    for (i = 0; i < size - 1; i++)
        printf("%d, ", arr[i]);
    printf("%d]\n", arr[size - 1]) ;
    return 0 ;
}

/* test: main() */
int main() {
  int arr[] = {2, 1, 6, 7, 9, 4, 5, 1000, 20, 30, 50} ;
  clock_t start_t, end_t ;
  double total_t ;
  int i;

  srand(time(NULL));
  start_t = clock();
  printf("Starting of the program, start_t = %ld\n", start_t) ;
  printf("Sorting array using randSwapSort(), start_t = %ld\n", start_t) ;
  printf("Array to sort: ") ;
  printArray(arr, sizeof(arr) / 4);
  printf("Shuffles performed: %u \n", randSwapSort(arr, sizeof(arr) / 4)) ;
  end_t = clock();
  printf("randSwapSort() success, end_t = %ld\n", end_t);
  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC ;
  printf("CPU runtime: %f seconds\n", total_t) ;
  printf("Exiting of the program...\n") ;
  return 0 ;
}
