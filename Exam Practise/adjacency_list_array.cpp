#include <iostream>
using namespace std;

class Adjacency_List // for graphs
{
private:
    char **adjacency_list;
    int size;

public:
    Adjacency_List(int size)
    {
        this->size = size;
        adjacency_list = new char *[size];
        for (int i = 0; i < size; i++)
        {
            adjacency_list[i] = new char[size];
        }
    }

    void add_edge(char from, char to)
    {
        int from_index = from - 'a';
        int to_index = to - 'a';
        adjacency_list[from_index][to_index] = 1;
        adjacency_list[to_index][from_index] = 1;
    }

    void delete_edge(char from, char to)
    {
        int from_index = from - 'a';
        int to_index = to - 'a';
        adjacency_list[from_index][to_index] = 0;
        adjacency_list[to_index][from_index] = 0;
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << char(i + 'a') << " -> ";
            for (int j = 0; j < size; j++)
            {
                if (adjacency_list[i][j] == 1)
                {
                    cout << char(j + 'a') << " ";
                }
            }
            cout << endl;
        }
    }

    ~Adjacency_List()
    {
        for (int i = 0; i < size; i++)
        {
            delete[] adjacency_list[i];
        }
        delete[] adjacency_list;
    }
};

int main()
{
    Adjacency_List graph(5);
    graph.add_edge('a', 'b');
    graph.add_edge('a', 'c');
    graph.add_edge('a', 'd');
    graph.add_edge('a', 'e');
    graph.add_edge('b', 'c');

    graph.print();

    system("pause");
    return 0;
}