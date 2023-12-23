#include <iostream>
#include <list>
#include <stack>
#include <queue>
using namespace std;

class Graph
{
public:
    list<int> **arr;
    int size;

    Graph(int size)
    {
        this->size = size;
        arr = new list<int> *[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = new list<int>;
        }
    }

    void insert(int vertex1, int vertex2)
    {
        vertex1 = vertex1 - 1;
        vertex2 = vertex2 - 1;
        if (vertex1 > this->size || vertex2 > this->size)
        {
            cout << "Error, Size of List Exceeded" << endl;
            return;
        }
        arr[vertex1]->push_back(vertex2);
        arr[vertex2]->push_back(vertex1);
    }

    void depth_first_search()
    {
        bool *visited = new bool[size];
        for (int i = 0; i < size; i++)
        {
            visited[i] = false;
        }

        stack<int> stk;
        int i = 0;
        stk.push(i);
        while (stk.empty() == false)
        {
            int curr = stk.top();
            stk.pop();
            if (visited[curr] == false)
            {
                visited[curr] = true;
                while (arr[curr]->empty() == false)
                {
                    int temp = arr[curr]->front();
                    arr[curr]->pop_front();
                    if (visited[temp] == false)
                    {
                        stk.push(temp);
                    }
                }
                cout << curr + 1 << " ";
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
        int i = 0;
        que.push(i);
        while (que.empty() == false)
        {
            int curr = que.front();
            que.pop();
            if (visited[curr] == false)
            {
                visited[curr] = true;
                while (arr[curr]->empty() == false)
                {
                    int temp = arr[curr]->front();
                    arr[curr]->pop_front();
                    if (visited[temp] == false)
                    {
                        que.push(temp);
                    }
                }
                cout << curr + 1 << " ";
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