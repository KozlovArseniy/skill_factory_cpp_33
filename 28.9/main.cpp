#include <iostream>
#include <future>
#include <chrono>

bool make_thread = true;

void merge(int* arr, int l, int m, int r)
{
    int nl = m - l + 1;
    int nr = r - m;

    // создаем временные массивы
    int left[nl], right[nr];

    // копируем данные во временные массивы
    for (int i = 0; i < nl; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < nr; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0;
    int k = l;  // начало левой части

    while (i < nl && j < nr) {
        // записываем минимальные элементы обратно во входной массив
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    // записываем оставшиеся элементы левой части
    while (i < nl) {
        arr[k] = left[i];
        i++;
        k++;
    }
    // записываем оставшиеся элементы правой части
    while (j < nr) {
        arr[k] = right[j];
        j++;
        k++;
    }
}


void merge_sort(int *arr, int l, int r){
    if( l >=r)
        return;
    int m = (l + r -1) / 2;
    merge_sort(arr, l, m);
    if( make_thread && ((r - l) > 100 )) {
        auto f = async(std::launch::async, [&]() {
            merge_sort(arr, l, m);
        });

        merge_sort(arr, m+1, r);
        f.get();
    }
    else {
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
    }
    merge(arr, l, m , r);
}

int N = 10000;
int arr[10000];

int main() {

    for(long i=0;i<N; i++) {
        arr[i] = rand() % 10;
    }

    merge_sort(arr, 0, N);

    for( int i=0; i < N; ++i)
        std::cout<<arr[i]<<" ";

    std::cout<<std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
