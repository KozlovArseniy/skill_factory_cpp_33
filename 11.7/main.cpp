#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstdio>

const int buf_size = 100000;

void swap(int* a, int* b) // функция для смены местами двух значений
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition (int* arr, int low, int high)
{
    int pivot = arr[high];    // опорный элемент
    int i = (low - 1);  // индекс наименьшего элемента
    for (int j = low; j <= high - 1; j++)
    {
        // если текущий элемент меньше или равен опорнуму
        if (arr[j] <= pivot)
        {
            i++;    // увеличиваем индекс минимального элемента
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int* arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high); // индекс опорного элемента
        quickSort(arr, low, pi-1);
        quickSort(arr, pi, high);
    }
}

void gen_random_data_file(const std::string& filename, int count_numbers ){
    std::srand(std::time(nullptr)); // use current time as seed for random generator

    std::fstream f;
//    int* arr = new int[count_numbers];
//    int count = 0;
    f.open(filename, std::fstream::out);
    if( f.is_open() ){
        while( count_numbers > 0 ){
            int random_variable = std::rand()%20;
            f<<random_variable;
            if( count_numbers != 1)
                f<<" ";
//            arr[count] = random_variable;
//            count++;
            count_numbers--;
        }
        f.close();
    }
    else
        std::cerr<<"Error open file"<<std::endl;

//    quickSort(arr, 0, count-1);
//    for(int i =0 ;i< count;++i)
//        std::cout<<arr[i]<<" ";
//    std::cout<<std::endl;
//    delete[] arr;
}

void write_arr(const std::string& filename, const int*arr, int size ){
    std::fstream f;
    f.open(filename, std::fstream::out);
    if( f.is_open() ){
        for(int i =0;i< size;i++){
            f<<arr[i];
            if(i != size-1)
                f<<" ";
        }
        f.close();
    }
    else
        std::cerr<<"Error open file"<<std::endl;
}

int get_minimal_and_index_from_array(const int* array, int& minimal_index, int size){
    int minimal_el = INT16_MAX;
    for(int i = 0; i<size; ++i){
        if( array[i]< minimal_el){
            minimal_el = array[i];
            minimal_index = i;
        }
    }
    return minimal_el;
}

void read_file(const std::string filename){
    std::fstream f;
    int batch = 0;
    f.open(filename, std::fstream::in);
    int buf[buf_size];// обрабываем за раз 1000 элементов.
    int buf_real_size;
    while( !f.eof() ){
        buf_real_size = 0;
        for(int i =0; ( i < buf_size ) && ( !f.eof() ); i++){
            f>>buf[i];
            buf_real_size++;
        }
        quickSort(buf, 0, buf_real_size - 1 );
        write_arr(filename + std::to_string(batch), buf, buf_real_size);
        batch++;
    }
    std::fstream result;
    result.open("result", std::fstream::out);

    std::fstream * file_streams = new std::fstream [batch];
    int* min_by_files = new int [batch];
    for(int i = 0;i< batch; ++i){
        file_streams[i].open(filename + std::to_string(i), std::fstream::in );
    }
    int minimal_el;
    int minimal_index;
    for(int i = 0;i < batch; ++i) {
        if( file_streams[i].is_open() )
            file_streams[i] >> min_by_files[i];
        else
            std::cout<<"File not open"<<std::endl;
    }

    while(true){
        minimal_el = get_minimal_and_index_from_array(min_by_files, minimal_index, batch);
        if( minimal_el == INT16_MAX )
            break;
        result<<minimal_el<<" ";
        //std::cout<<minimal_el<<" "<< minimal_index<<std::endl;
        if( !file_streams[minimal_index].eof() )
            file_streams[minimal_index]>>min_by_files[minimal_index];
        else
            min_by_files[minimal_index] = INT16_MAX;
    }

    for(int i = 0;i< batch; ++i){
        std::remove( ( filename+std::to_string(i) ).c_str());
        file_streams[i].close();
    }
    delete[] file_streams;
    delete[] min_by_files;

}

int main() {
    //gen_random_data_file("test", 51200*4*1000);

    gen_random_data_file("test", 60);

    read_file("test");
    return 0;
}
