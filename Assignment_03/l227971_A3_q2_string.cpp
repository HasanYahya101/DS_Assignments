#include <iostream>
using namespace std;

template <typename dataType>
class Node
{
public:
    dataType data;
    Node *next;
    Node *prev;

    Node(dataType data)
    {
        this->data = data;
        next = NULL;
        prev = NULL;
    }

    Node()
    {
        next = NULL;
        prev = NULL;
    }
};

template <typename dataType>

class Radix_Queue
{
private:
    Node<dataType> *head;
    Node<dataType> *tail;
    int size;

public:
    /**
     * @brief Construct a new Radix_Queue object
     * @note Time complexity: O(1)
     */
    Radix_Queue()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    /**
     * @brief Adds an element to the end of the queue
     * @note Time complexity: O(1)
     * @param data The data to be added
     * @return void
     */
    void enqueue(dataType data)
    {
        Node<dataType> *newNode = new Node<dataType>(data);
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    /**
     * @brief Get the Data object
     * @note Time complexity: O(n)
     * @param index The index of the element to be returned
     * @return dataType The data of the element
     */
    dataType getData(int index)
    {
        if (index < 0 || index >= size)
        {
            cout << "Index out of bounds" << endl;
            return -1;
        }
        else
        {
            Node<dataType> *temp = head;
            for (int i = 0; i < index; i++)
            {
                temp = temp->next;
            }
            return temp->data;
        }
    }

    /**
     * @brief Removes the first element in the queue
     * @note Time complexity: O(1)
     * @return dataType The data of the removed element
     * @return -1 If the queue is empty
     */
    dataType dequeue()
    {
        if (head == NULL)
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        else
        {
            dataType data = head->data;
            Node<dataType> *temp = head;
            head = head->next;
            delete temp;
            size--;
            return data;
        }
    }

    /**
     * @brief Get the Size of the queue
     * @note Time complexity: O(1)
     * @return int The size of the queue
     */
    int getSize()
    {
        return size;
    }

    /**
     * @brief Prints the queue
     * @note Time complexity: O(n)
     * @return void
     */
    void print()
    {
        Node<dataType> *temp = tail;
        while (temp != NULL)
        {
            int val = temp->data;
            char character = static_cast<char>(val);
            cout << character; // Print the character
            temp = temp->prev;
        }
    }

    /**
     * @brief Destroy the Radix_Queue object
     * @note Time complexity: O(1)
     */
    ~Radix_Queue()
    {
        // Nothing to do here
    }
};

template <typename dataType>

/**
 * @brief Sorts the array of queues using radix comparisons
 * @param radixQueue_arr The array of queues to be sorted
 * @param size_of_arr The size of the array of queues
 * @return The sorted array of queues
 * @note Time complexity: O(n^3), i think
 */
Radix_Queue<dataType> *Radix_Sort(Radix_Queue<dataType> *radixQueue_arr, int size_of_arr)
{
    // find max digits
    int max_digits = 0;
    for (int i = 0; i < size_of_arr; i++)
    {
        if (radixQueue_arr[i].getSize() > max_digits)
        {
            max_digits = radixQueue_arr[i].getSize();
        }
    }
    // add zeros to the left of queues with less digits, ie the number 11 can be 0011 but not 1100
    for (int i = 0; i < size_of_arr; i++)
    {
        while (radixQueue_arr[i].getSize() < max_digits)
        {
            radixQueue_arr[i].enqueue(32); // ASCII of space
        }
    }
    // print the array of queues
    cout << "Your String is: " << endl;
    for (int i = 0; i < size_of_arr; i++)
    {
        radixQueue_arr[i].print();
        cout << endl;
    }
    system("pause");
    system("cls");
    cout << "--->> Sorting..." << endl;
    // Sort the array of queues using radix comparisons
    for (int i = 0; i < max_digits; i++)
    {
        for (int j = 0; j < size_of_arr - 1; j++)
        {
            for (int k = 0; k < size_of_arr - j - 1; k++)
            {
                if (radixQueue_arr[k].getData(i) > radixQueue_arr[k + 1].getData(i))
                {
                    // Swap the queues
                    Radix_Queue<dataType> temp = radixQueue_arr[k];
                    radixQueue_arr[k] = radixQueue_arr[k + 1];
                    radixQueue_arr[k + 1] = temp;
                }
            }
        }
        cout << "Column " << i + 1 << " from End, Sorted: " << endl;
        for (int i = 0; i < size_of_arr; i++)
        {
            radixQueue_arr[i].print();
            cout << endl;
        }
        system("pause");
        system("cls");
    }
    return radixQueue_arr;
}

int main()
{
    cout << "How many numbers you want to enter: ";
    int num;
    cin >> num;
    while (num < 2)
    {
        cout << "Please enter a number greater than 1: ";
        cin >> num;
    }
    Radix_Queue<int> *radixQueue_arr = new Radix_Queue<int>[num];
    for (int i = 0; i < num; i++)
    {
        cout << "Enter String " << i + 1 << ": ";
        string temp;
        cin >> temp;
        // enter each digit separately in the queue
        for (int k = temp.length() - 1; k >= 0; k--)
        {
            char character = temp[k];
            int ascii = static_cast<int>(character);
            radixQueue_arr[i].enqueue(ascii);
        }
    }
    // sort the array of queues
    Radix_Queue<int> *radixQueue_arr_2 = Radix_Sort(radixQueue_arr, num);
    // print the sorted array of queues
    cout << "Your Completly Sorted String is: " << endl;
    for (int i = 0; i < num; i++)
    {
        radixQueue_arr_2[i].print();
        cout << endl;
    }
    cout << endl;

    system("pause");
    return 0;
}