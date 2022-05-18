#include <stdio.h>
#include <time.h>

int binsearch(int x, int v[], int n);
int mybinsearch(int x, int v[], int n);
void testf(char test_name[], int (*f)(int, int[], int), int number_to_search, int array[]);

int main(){

    int test[] = {1, 23, 34, 45, 56, 67, 78, 89};

    testf("myBin f", mybinsearch, 34, test);
    testf("myBin n", binsearch, 5, test);
    testf("krBin f", mybinsearch, 34, test);
    testf("krBin n", binsearch, 5, test);

    return 0;
}

void testf(char test_name[], int (*f)(int, int[], int), int number_to_search, int array[]){
    int result;
    clock_t start, end;

    start = clock();
    result = (*f)(number_to_search, array, 8); //sizeof(array)/4
    end = clock();
    printf("%s = position of %d: %d\texecution time: %f\n", test_name, number_to_search, result, ((double) (end-start))/CLOCKS_PER_SEC);
}

/* mybinsearch: same as binsearch, but with just one test inside the loop */
int mybinsearch(int x, int v[], int n){
    int low, high, mid;

    low = 0;
    high = n - 1;

    mid = (low+high) / 2;
    while (low <= high && v[mid] != x){
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;

        mid = (low+high) / 2;
    }

    if (v[mid] == x)
        return mid;
    else
        return -1; /* no match */
}

/* binsearch: find x in v[O] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n){
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high){
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else    /* found match */
            return mid;
    }
    return -1; /* no match */
}