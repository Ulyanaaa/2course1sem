/*
[Вариант 6]
1.	Написать программу поиска кратчайшие расстояния от 1-й вершины до
всех остальных для графа согласно своего варианта (см. Рис. 11),
используя алгоритм Дейкстры. Составьте таблицу
сравнения двух алгоритмов по времени или количеству шагов.
*/


#include <iostream>
#include <iomanip>
#include <chrono>   // Для измерения времени выполнения
using namespace std;

const int count_vertices = 8; // Количество вершин в графе
const int INF = 1e9; // "Бесконечность" для инициализации расстояний


void solution(int graph[][count_vertices], int lvl_vertices, int distances[]);

int main() {
                                            //    1 2 3 4 5 6 7 8
    int graph[count_vertices][count_vertices] = {{0,3,0,0,0,0,0,1},
                                                 {3,0,0,3,0,0,2,2},
                                                 {0,0,0,4,0,0,3,0},
                                                 {0,2,4,0,5,7,0,0},
                                                 {0,0,0,5,0,6,0,0},
                                                 {0,0,0,7,6,0,4,5},
                                                 {0,2,3,0,0,4,0,1},
                                                 {1,2,0,0,0,5,1,0}};

    
    int distances[count_vertices];    // Массив для хранения расстояния от 1 до n вершины
    cout << "\n[Task 1 - Dijkstra's algorithm] \n\n";
        
    // Стартовая точка отсчета времени
    auto start = chrono::steady_clock::now();
    for (int lvl_vertices = 0; lvl_vertices < count_vertices; lvl_vertices++)
    {
        solution(graph, lvl_vertices, distances);
        
        // Вывод кратчайших расстояний
        for (int i = 0; i < count_vertices; ++i) {
            cout  << setw(2)<< distances[i] << " ";
        }
        cout << endl;
    }


    // Конечная точка, вывод времени работы
    auto dur = chrono::steady_clock::now() - start;
    cout <<"\ntime: " << chrono::duration_cast<chrono::milliseconds>(dur).count() << " mcs\n" << endl;

}


// Функция для выполнения алгоритма Дейкстры
void solution(int graph[][count_vertices], int lvl_vertices, int distances[]) 
{
    bool visited[count_vertices] = {false};

    for (int i = 0; i < count_vertices; ++i) 
    {
        // Устанавливаем бесконечное значение во всех ячейках изначально
        distances[i] = INF;
    }
    // У той вершины, с которой начинаем, ставим 0
    distances[lvl_vertices] = 0;
    
    for (int i = 0; i < count_vertices; ++i) 
    {
        int min_distance = INF;
        int index;

        // Найдем вершину с минимальным расстоянием
        for (int j = 0; j < count_vertices; ++j) {
            if (!visited[j] && distances[j] < min_distance) 
            {
                min_distance = distances[j];
                index = j;
            }
        }

         
        visited[index] = true;

        // Обновляем расстояния до смежных вершин
        for (int i = 0; i < count_vertices; ++i) {
            if (!visited[i] && graph[index][i] != 0 && distances[index] != INF && distances[index] + graph[index][i] < distances[i]) 
            {
                //cout << i << " " << distances[i] << " more " << distances[index] + graph[index][i] << endl;
                distances[i] = distances[index] + graph[index][i];
            }
        }
    }
}
