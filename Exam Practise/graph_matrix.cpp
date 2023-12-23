#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Graph
{
public:
    int **matrix;
    int size;

    Graph(int size)
    {
        this->size = size;
        matrix = new int *[size];
        for (int i = 0; i < size; i++)
        {
            matrix[i] = new int[size];
            for (int j = 0; j < size; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }

    void insert(int vertex1, int vertex2)
    {
        vertex1 = vertex1 - 1;
        vertex2 = vertex2 - 1;
        if (vertex1 >= size || vertex2 >= size)
        {
            cout << "Error, Vertex out of Range" << endl;
            return;
        }
        matrix[vertex1][vertex2] = 1;
        matrix[vertex2][vertex1] = 1;
    }

    void depth_first_search()
    {
        bool *visited = new bool[size];
        for (int i = 0; i < size; i++)
        {
            visited[i] = false;
        }

        stack<int> stk;
        int startVertex = 0;
        stk.push(startVertex);

        while (!stk.empty())
        {
            int curr = stk.top();
            stk.pop();

            if (!visited[curr])
            {
                visited[curr] = true;
                cout << curr + 1 << " ";

                for (int i = size - 1; i >= 0; i--)
                {
                    if (matrix[curr][i] == 1 && !visited[i])
                    {
                        stk.push(i);
                    }
                }
            }
        }
    }

    void breadth_first_search()
    {
        bool *visited = new bool[size];
        for (int i = 0; i < size; i++)
        {
            visited[i] = false;
        }

        queue<int> que;
        int startVertex = 0;
        que.push(startVertex);
        visited[startVertex] = true;

        while (!que.empty())
        {
            int curr = que.front();
            que.pop();
            cout << curr + 1 << " ";

            for (int i = 0; i < size; i++)
            {
                if (matrix[curr][i] == 1 && !visited[i])
                {
                    que.push(i);
                    visited[i] = true;
                }
            }
        }
    }
};

int main()
{
    {
        Graph graph(10);
        graph.insert(1, 2);
        graph.insert(1, 4);
        graph.insert(2, 3);
        graph.insert(4, 3);
        graph.insert(3, 9);
        graph.insert(3, 10);
        graph.insert(2, 5);
        graph.insert(2, 8);
        graph.insert(2, 7);
        graph.insert(5, 8);
        graph.insert(5, 7);
        graph.insert(8, 7);
        graph.insert(5, 6);
        graph.depth_first_search();
    }
    cout << endl;
    {
        Graph graph(10);
        graph.insert(1, 2);
        graph.insert(1, 4);
        graph.insert(2, 3);
        graph.insert(4, 3);
        graph.insert(3, 9);
        graph.insert(3, 10);
        graph.insert(2, 5);
        graph.insert(2, 8);
        graph.insert(2, 7);
        graph.insert(5, 8);
        graph.insert(5, 7);
        graph.insert(8, 7);
        graph.insert(5, 6);
        graph.breadth_first_search();
    }
    return 0;
}
