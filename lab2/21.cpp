/*
Вариант 6

[Task 1] Разработать подпрограммы сортировки массива определенного типа данных (см. табл. 1) c помощью алгоритмов сортировки (см. табл. 2). 
Таблица 1: Одномерный массив беззнаковых коротких целых чисел типа short int

Таблица 2:
1. Быстрая сортировка 
2. Блочная сортировка
*/


#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
 

void create_rnd_arr(short int arr[], int min_ch, int max_ch, int n);
void output_arr(short int arr[], int n);

void fill_arr(short int arr[], short int basket_arr[], int n);

void quick_sort(short int arr[], int start, int n);
int dop_quick_sort(short int arr[], int start, int end);


void basket_sort(short int arr[], int n);
void sorting_one_basket( short int basket[], int n);

int main()
{
    time_t t;
    srand(time(&t));

    // Диапозон значений массива
    int min_ch = -1000;
    int max_ch = 1000;

    cout << "\n[Task 1]" << endl;
    // Количество элементов в массиве
    int n;    
    cout << "\nEnter number of series in the array: "; cin >> n;
    
    // Массив для быстрой сортировки
    short int arr[n];
    // Массив дляблочной сортировки
    short int basket_arr[n];

    // Создание рандомного массива
    create_rnd_arr(arr, min_ch, max_ch, n);

    // Заполняем такими же элементами массив для блочной сортировки
    fill_arr(arr, basket_arr, n);
    
    // Быстрая сортировка
    cout << "\nArray for quick sort: \n";
    output_arr(arr,n); 
    quick_sort(arr, 0, n-1);
    cout << "\nSorted array by quick sort:\n";
    output_arr(arr, n);

    // Блочная сортировка
    cout << "\nArray for block sort: \n";
    output_arr(basket_arr, n); 
    basket_sort(basket_arr, n);
    cout << "\nSorted array by block sort:\n";
    output_arr(basket_arr, n);
    
}

// Заполнение массива блочной сортировки такими же эл-тами, как и для быстрой
void fill_arr(short int arr[], short int basket_arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        basket_arr[i] = arr[i];
    }
}

// Создание массива с рандомными элементами
void create_rnd_arr(short int arr[], int min_ch, int max_ch, int n)
{    
    for (int i = 0; i <= n; i++)    
        // num = m + rand() % (n - m + 1);
        arr[i] = min_ch + rand() % (max_ch - min_ch + 1);
}
 
 // Функция вывода массива
void output_arr(short int arr[], int n)
{
    for (int i = 0; i < n; i++)             
        cout << arr[i] << "  ";        
    cout << "\n";    
} 

// Функция, организующая быструю сортировк
void quick_sort(short int arr[], int start, int end)
{ 
    // Начало не должно быть больше окончания
    if (start >= end) {
        return;
    }

    // Вызываем функцию, которая отсортирует массив: *меньше* *опорное число* *больше* и вернет индекс, 
    // который разделит последовательность для дальнейшей сортировки
    int index_opora = dop_quick_sort(arr, start, end);

    quick_sort(arr, start, index_opora-1);
    quick_sort(arr, index_opora+1, end);
}

 
int dop_quick_sort(short int arr[], int start, int end)
{
    // Выбираем опорным числом крайнее левое значение
    int opora = arr[end];
    // Вспомогательный индекс (возвращаемый индекс опоры)
    int index_sort = start;
    // Переменная для того,чтобы поменять элементы массива местами
    short int temp;

    // Цикл сортировки
    for (int i = start; i < end; i++)
    {
        // Если я нахожу число меньше опоры, то я его ставлю вперед (по индексу index_sort), а число которое 
        // было впереди, ставлю на место найденного меньшего числа (по идексу i)
        if (arr[i] <= opora)
        {
            // Меняю местами
            temp = arr[i];
            arr[i] = arr[index_sort];
            arr[index_sort] = temp;
            // Двигаю index_sort 
            index_sort ++;
        }
    } 
    // После всех найденных чисел меньше опоры, ставлюю опору
    temp = arr[end];
    arr[end] = arr[index_sort];
    arr[index_sort] = temp;

    // Возвращаю индекс опоры
    return index_sort;
}





// Функция для корзинной сортировки
void basket_sort(short int arr[], int n) {
    // Находим минимальное и максимальное значения в массиве
    short int min_val = arr[0];
    short int max_val = arr[0];
    for (int i = 1; i < n; i++) 
    {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    // Кол-во корзин = кол-во элементов исходного
    int num_baskets = n;
    // Запоминем кол-во элементов в каждой корзине
    int basket_sizes[num_baskets] = {0};
    // Сами корзины
    short int* baskets[num_baskets];

    for (int i = 0; i < num_baskets; i++) 
    {
        baskets[i] = new short int[n];
    }

    // Распределение элементов по корзинам
    for (int i = 0; i < n; i++) 
    {
        // Определяем индекс : определяем насколько число больше минимального, определяем какой
        // диапозон эл-тов, умножем на максимальный индекс -> используем int, получаем индекс корзины
        int basket_index = int((arr[i] - min_val) / (max_val - min_val) * (num_baskets - 1));

        // Заносим число в корзину под нужным индексом на последнее место
        baskets[basket_index][basket_sizes[basket_index]] = arr[i];

        // Указываем что в этой корзине теперь на 1 эл=т больше
        basket_sizes[basket_index]++;
    }

    // Сортировка элементов внутри каждой корзины
    for (int i = 0; i < num_baskets; i++) 
    {
        sorting_one_basket(baskets[i], basket_sizes[i]);
    }

    // Объединение корзин в отсортированный массив
    int index = 0;
    for (int i = 0; i < num_baskets; i++) {
        for (int j = 0; j < basket_sizes[i]; j++) {
            arr[index++] = baskets[i][j];
        }
        delete[] baskets[i];
    }
}



// Функция для сортировки вставками
void sorting_one_basket( short int basket[], int n) {
    // Начинаем с 1, нас не интересуют пустые или с одним эл-том корзины
    for (int i = 1; i < n; i++) 
    {
        // Запоминаем элемент
        short int key = basket[i];
        // Берем индекс эл-та слева
        int j = i - 1;
        // Пока слева есть эл-т и он больше, чем key
        while (j >= 0 && basket[j] > key) 
        {
            // Двигаем key вправо
            basket[j + 1] = basket[j];
            // Берем следующий левый эл-т
            j--;
        }
        // Ставим key на правильное место
        basket[j + 1] = key;
    }
}
