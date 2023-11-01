#include <iostream>
using namespace std;

/**
 * Note: This is a stack implementation using array. For List based, check the other version.
 */

template <typename dataType>

/**
 * @brief Stack class implimented using array.
 * @brief It has a Default Constructor, push, pop, flipStack and print functions along with a Destructor.
 */
class Stack
{
private:
    dataType *arr; // array to store the elements of the stack
    int capacity;  // Total capacity of Memory Allocated
    int size;      // Total number of elements in the stack
    bool flipped;  // If true then count from start and increment, else count from end and decrement
    int top;       // Index of the top element of the stack

public:
    /**
     * @brief Default Constructor for the array based stack class.
     * @brief It initializes the capacity, size, flipped and top variables.
     * @brief It also initializes the array to NULL.
     * @return `void` - Nothing
     * @param void Nothing
     * @note The time complexity of this function is O(1).
     */
    Stack(void)
    {
        capacity = 0;
        size = 0;
        flipped = false;
        top = -1;
        arr = NULL;
    }

    /**
     * @brief Pushes an element to the stack.
     * @brief It takes an argument of type dataType and pushes it to the stack. The data can be any datatype.
     * @brief It also increases the size of the stack by 1.
     * @brief If the stack is full, it doubles the capacity of the stack.
     * @brief If the stack is flipped, it adds the element at the end of the already filled array.
     * @brief If the stack is not flipped, it adds the element at the start of the array after pushing all elements forward by 1.
     * @return `void` - Nothing
     * @param data - The data to be pushed to the stack. The data can be of any datatype.
     * @note The time complexity of this function is O(N), where N is the size of the Array.
     */
    void __push__(dataType data)
    {
        if (capacity == 0)
        {
            capacity = 1;
            arr = new dataType[capacity];
            arr[0] = data;
            top = 0;
            size = 1;
        }
        else
        {
            if (size == capacity)
            {
                capacity *= 2;
                dataType *temp = new dataType[capacity];
                for (int i = 0; i < size; i++)
                {
                    temp[i] = arr[i];
                }
                delete[] arr;
                arr = temp;
            }
            if (flipped)
            {
                // add after at the end of the already filled array
                arr[size] = data;
                top = size;
            }
            else
            {
                // add at the start of array after pushing all elements forward by 1
                for (int i = size; i > 0; i--)
                {
                    arr[i] = arr[i - 1];
                }
                arr[0] = data;
                top = 0;
            }
            size++;
        }
    }

    /**
     * @brief Pops an element from the stack.
     * @brief It removes the top element from the stack and decreases the size of the stack by 1.
     * @brief If the stack is empty, it prints an error message.
     * @brief If the stack is flipped, it removes the last element from the end of the already filled array.
     * @brief If the stack is not flipped, it removes the first element and pushes all elements back by 1.
     * @return `void` - Nothing
     * @param void Nothing
     * @note The time complexity of this function is N + N = O(N), where N is the size of the Array.
     */
    void __pop__(void)
    {
        if (size == 0)
        {
            cout << "Stack is empty" << endl;
            return;
        }
        else
        {
            if (flipped)
            {
                // remove last element at the end of the already filled array
                top = size - 2;
            }
            else
            {
                // remove first element and push all elements back by 1
                for (int i = 0; i < size - 1; i++)
                {
                    arr[i] = arr[i + 1];
                }
                top = 0;
            }
            size--;
            if (size <= capacity / 2)
            {
                capacity /= 2;
                dataType *temp = new dataType[capacity];
                for (int i = 0; i < size; i++)
                {
                    temp[i] = arr[i];
                }
                delete[] arr;
                arr = temp;
            }
        }
    }

    /**
     * @brief This Function flips the array based stack.
     * @brief It changes the value of the flipped variable.
     * @brief If the stack is empty, it prints an error message.
     * @return `void` - Nothing
     * @param void Nothing
     * @note Time Complexity of this function is O(1), as required.
     */
    void __flipStack__(void)
    {
        if (size == 0)
        {
            cout << "Stack is empty" << endl;
        }
        else
        {
            if (flipped)
            {
                flipped = false;
                top = 0;
            }
            else
            {
                flipped = true;
                top = size - 1;
            }
        }
    }

    /**
     * @brief This Function prints the stack.
     * @brief It prints the stack in the order it is stored in the array, if the array is not flipped.
     * @brief It prints the stack in the reverse order, if the array is flipped.
     * @brief If the stack is empty, it prints an error message.
     * @return `void` - Nothing
     * @param void Nothing
     * @note Time Complexity of this function is O(N), where N is the size of the Array.
     */
    void __print__(void)
    {
        if (size == 0)
        {
            cout << "Stack is empty" << endl;
        }
        else
        {
            if (flipped)
            {
                for (int i = size - 1; i >= 0; i--)
                {
                    cout << arr[i] << " ";
                }
                cout << endl;
            }
            else
            {
                for (int i = 0; i < size; i++)
                {
                    cout << arr[i] << " ";
                }
                cout << endl;
            }
        }
    }

    /**
     * @brief Default Destructor for the array based stack class.
     * @brief It deletes the array.
     * @return `void` - Nothing
     * @param void Nothing
     * @note The time complexity of this function is O(1).
     */
    ~Stack(void)
    {
        delete[] arr;
    }
};

int main(void) // The main Function was Hard Coded for testing purposes
{
    Stack<int> stack;
    cout << "Adding 10 elements to the stack" << endl;
    for (int i = 10; i >= 1; i--)
    {
        stack.__push__(i);
    }
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Poping an element from the stack" << endl;
    stack.__pop__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Flipping the stack" << endl;
    stack.__flipStack__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Poping an element from the stack" << endl;
    stack.__pop__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Flipping the stack" << endl;
    stack.__flipStack__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Poping an element from the stack" << endl;
    stack.__pop__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Flipping the stack" << endl;
    stack.__flipStack__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Poping an element from the stack" << endl;
    stack.__pop__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Flipping the stack" << endl;
    stack.__flipStack__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Poping an element from the stack" << endl;
    stack.__pop__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Flipping the stack" << endl;
    stack.__flipStack__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Poping an element from the stack" << endl;
    stack.__pop__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Flipping the stack" << endl;
    stack.__flipStack__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Poping an element from the stack" << endl;
    stack.__pop__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Flipping the stack" << endl;
    stack.__flipStack__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Poping an element from the stack" << endl;
    stack.__pop__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Flipping the stack" << endl;
    stack.__flipStack__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Poping an element from the stack" << endl;
    stack.__pop__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Flipping the stack" << endl;
    stack.__flipStack__();
    cout << "Printing the stack: " << endl;
    stack.__print__();
    cout << "Poping an element from the stack" << endl;
    stack.__pop__();
    cout << "Printing the stack: " << endl;
    stack.__print__();

    cout << endl;
    system("pause");
    return 0;
}