/* badsorts.c
    - Steven Shi
    - Description: Contains awful sorting
      methods.
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

void arrToString(char *str, int *arr, int size, int limit) {
  int i ;
  int n ;
  int index = 0 ;
  memset(str, 0, sizeof str);
  if (limit && size > 30) {
    n = 30 ;
  } else {
    n = size ;
  }
  for (i = 0 ; i < n; i++) {
    index = index + sprintf(&str[index], "%d ", arr[i]) ;
  }
  if (limit && size > 30) {
    sprintf(&str[index + 1], " ... ") ;
  }
}

int printArray(int *arr, int size, int limit) {
    int i ;
    int n ;
    printf("[") ;
    if (limit && size > 30) {
      n = 30 ;
    } else {
      n = size ;
    }
    for (i = 0 ; i < n - 1 ; i++)
        printf("%d, ", arr[i]);
    if (limit && size > 30) {
      printf("%d... ]\n", arr[size - 1]) ;

    } else {
      printf("%d]\n", arr[size - 1]) ;
    }
    return 0 ;
}

void pushArray(int *arr, int size) {
  int i ;
  int buffer[size] ;
  int j = 0 ;
  memcpy(buffer, arr, size * sizeof(int)) ;

  for (i = 1 ; i < size ; i++) {
    arr[j] = buffer[i] ;
    j++ ;
  }
  arr[size - 1] = buffer[0] ;
  //printArray(arr, size, 1) ;
}

/* =============================================================

    Sorting Functions:

=============================================================
*/

/* bogoSort()
  - n is size of array
  - Assumes seed is set for rand()
  - Swaps elements 69 times, validated(?), then tries again
  - if output 1, output shuffling
  - returns number of shuffles done
*/
unsigned int bogoSort(int *arr, int n, int output) {
  int r1, r2, i ;
  char str[100] ;
  unsigned int count = 0 ;
  int pn ;

  // set pseudonumber for output
  pn = 1 ;

  if (output) {
    printf("bogoSort() : Shuffling... \n") ;
  }
  if (validate(arr, n) != 0) {
    do {
      if (output && count % pn == 0) {
        arrToString(str, arr, n, 1) ;
        printf("\rNumber of Shuffles: %d | [ %s] ", count, str) ;
        pn = rand() % 420 + 1;
      }
      for (i = 0; i < n / 2; i++) {
        r1 = rand() % n ;
        do {
          r2 = rand() % n ;
        } while (r2 == r1) ;
        swap(&arr[r1], &arr[r2]) ;
      }
      count++ ;
    } while (validate(arr, n) != 0) ;
  }
  arrToString(str, arr, n, 1) ;
  printf("\rNumber of Shuffles: %d | [ %s] ", count, str) ;
  fflush(stdout) ;
  return count ;
}

/* borpSort()
  - n is size of array
  - Assumes seed is set for rand()
  - Swaps elements 69 times, validated(?), then tries again
  - if output 1, output shuffling
  - returns number of shuffles done
*/

unsigned int borpSort(int *arr, int n, int output) {
  int r1, r2, i ;
  double m;
  char str[100] ;
  unsigned int count = 0 ;
  int pn ;
  int buffer[n] ;
  int ref[n] ;
  int arrIndex ;
  double p = 80 ;

  // calculating mean
  m = 0.0 ;
  for (i = 0 ; i < n ; i++) {
    m += arr[i] ;
  }
  m = m / n ;

  // set pseudonumber for output
  pn = 1 ;

  if (output) {
    printf("borpSort() : Shuffling... \n") ;
  }
  memcpy(ref, arr, n * sizeof(int)) ;
  if (validate(arr, n) != 0) {
    do {
      p = 80.0 ;
      if (output && count % pn == 0) {
        arrToString(str, arr, n, 1) ;
        printf("\rNumber of Shuffles: %d | [ %s] ", count, str) ;
        pn = rand() % 1000 + 1;
      }
      memcpy(buffer, ref, n * sizeof(int)) ;
      arrIndex = 0 ;
      do {
        if (buffer[0] < m && rand() % 100 > p) {
          arr[arrIndex] = buffer[0] ;
          pushArray(buffer, n - arrIndex) ;
          arrIndex++ ;
          p = p - 20.0 / (double) n ;
          //printf("p value: %lf\n", p) ;
        } else if (rand() % 100 < p) {
          arr[arrIndex] = buffer[0] ;
          pushArray(buffer, n - arrIndex) ;
          arrIndex++ ;
          p = p - 20.0 / (double) n ;
          //printf("p value: %lf\n", p) ;
        } else {
          pushArray(buffer, n - arrIndex) ;
        }
      } while (arrIndex < n) ;
      count++ ;
    } while (validate(arr, n) != 0) ;


    arrToString(str, arr, n, 1) ;
    //printf("Shuffled Array: %s\n", str) ;
  }
  arrToString(str, arr, n, 1) ;
  printf("\rNumber of Shuffles: %d | [ %s] ", count, str) ;
  fflush(stdout) ;
  return count ;
}


/* =============================================================

    main() ;

=============================================================
*/
int main() {
  int choice ;
  int size ;
  int *arr ;
  char str[100] ;
  clock_t start_t, end_t ;
  double total_t ;
  int i;

  printf("\nWhich fresh hell would you like to indulge in?\n") ;
  printf("\n%s\n     %s\n     %s\n     %s\n     %s\n     %s\n%s\n",
    "----------------------------------",
    "1: (BogoSort)",
    "2: (BropSort)",
    "3: (Quantum BogoSort)",
    "4: (BogoBogoSort)",
    "5: (BogoBorpBogoSort)",
    "----------------------------------") ;
  printf("\nINPUT [1..5] : ") ;
  scanf("%d", &choice) ;
  printf("\n") ;

  printf("Size of Array? : ") ;
  scanf("%d", &size) ;
  printf("\n") ;
  arr = (int *) malloc(size * sizeof(int)) ;
  //printf("Size: %d", size) ;
  for (i = 0 ; i < size ; i++) {
    arr[i] = rand() % 89 + 10 ;
  }

  srand(time(NULL));

  switch (choice) {
    case 1 : // BogoSort
      start_t = clock();
      printf("Starting of the program,\n") ;
      printf("Sorting array using bogoSort(), start_t = %ld\n", start_t) ;
      printf("Size of Array : %d \n", size) ;
      printf("Array to sort: ") ;
      printArray(arr, size, 1) ;
      printf("\n") ;
      bogoSort(arr, size, 1) ;
      end_t = clock();
      printf("\nbogoSort() success, end_t = %ld\n", end_t);
      break ;

    case 2 : // BorpSort
      start_t = clock();
      printf("Starting of the program,\n") ;
      printf("Sorting array using borpSort(), start_t = %ld\n", start_t) ;
      printf("Size of Array : %d\n", size) ;
      printf("Array to sort : ") ;
      printArray(arr, size, 1);
      borpSort(arr, size, 1) ;
      end_t = clock();
      printf("\nborpSort() success, end_t = %ld\n", end_t);
      break ;

    case 3 : // Quantum BogoSort
      printf("Error: Unimplemented\n") ;
      break ;

    case 4 : // BogoBorpBogoSort
      printf("Error: Unimplmented\n") ;
      break ;

    case 5 : // BogoBorpBogoSort
      printf("Error: Unimplemented\n") ;
      break ;

    default : // fail case
      printf("Error : Can you fucking read??? \n") ;
      return 0 ;
  }

  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC ;
  printf("CPU runtime: %f seconds\n", total_t) ;
  printf("Exiting of the program...\n") ;
  return 0 ;
}
