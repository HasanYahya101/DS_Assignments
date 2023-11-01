#include <iostream>
using namespace std;

template <typename dataType>

/**
 * @brief Node class for the Undo_Stack
 * @brief It contains the data, next and prev pointers
 * @tparam dataType - It can be any data type.
 */
class Node
{
public:
    dataType data; // data for stored value. It can be any data type
    Node *next;    // Node pointer pointing to next Node.
    Node *prev;    // Node pointer pointing to prev Node.
};

template <typename dataType>

/**
 * @brief Undo_Stack class.
 * @brief It contains the top, bottom and size variables. Top and bottom are Node pointers. Size is an integer.
 * @brief It contains the functions to push, pop, display and get the size of the stack.
 * @tparam dataType - It can be any data type.
 */
class Undo_Stack
{
private:
    Node<dataType> *top;    // Node pointer to store the top of the stack.
    Node<dataType> *bottom; // Node pointer to store the bottom of the stack.
    int size;               // Integer to store the size of the stack.

public:
    /**
     * @brief Constructer for the Undo_Stack class.
     * @brief It initializes the top and bottom pointers to NULL and size to 0.
     * @return `void` - No parameters
     * @param void No parameters
     * @note Time complexity: O(1)
     */
    Undo_Stack(void)
    {
        top = NULL;
        bottom = NULL;
        size = 0;
    }

    /**
     * @brief Push function for the Undo_Stack class.
     * @brief It pushes the data into the stack.
     * @brief If the size of the stack exceeds 100, it automatically removes the bottom most entry.
     * @return `void` - No parameters
     * @param data It is the data to be pushed into the stack. It can be any data type.
     * @tparam dataType It can be any data type.
     * @note Time complexity: O(1)
     */
    void __push__(dataType data)
    {
        Node<dataType> *temp = new Node<dataType>;
        temp->data = data;
        temp->next = NULL;
        temp->prev = NULL;

        if (size == 0)
        {
            top = temp;
            bottom = temp;
        }
        else
        {
            top->next = temp;
            temp->prev = top;
            top = temp;
        }
        size++;

        if (size > 100)
        {
            Node<dataType> *temp = bottom;
            bottom = bottom->next;
            bottom->prev = NULL;
            delete temp;
            size--;
        }
    }

    /**
     * @brief Size function for the Undo_Stack class.
     * @brief It returns the size of the stack.
     * @return `int` - It returns the size of the stack.
     * @param void No parameters
     * @note Time complexity: O(1)
     */
    int __size__(void)
    {
        return size;
    }

    /**
     * @brief Pop function for the Undo_Stack class.
     * @brief It pops the top most entry from the stack.
     * @return `void` - No parameters
     * @param void No parameters
     * @note Time complexity: O(1)
     */
    void __pop__(void)
    {
        if (size == 0)
        {
            cout << "Stack is empty" << endl;
        }
        else
        {
            Node<dataType> *temp = top;
            top = top->prev;
            delete temp;
            size--;
        }
    }

    /**
     * @brief Pop function for the Undo_Stack class.
     * @brief It pops the 2nd from top entry from the stack.
     * @return `void` - No parameters
     * @param void No parameters
     * @note Time complexity: O(1)
     */
    void __pop_2nd_from_top__(void)
    {
        // if you have 4 3 2 1 with 4 on top, delete 3
        if (size == 0)
        {
            cout << "Stack is empty" << endl;
        }
        else
        {
            Node<dataType> *temp = top->prev;
            top->prev = top->prev->prev;
            top->prev->next = top;
            delete temp;
            size--;
        }
    }

    /**
     * @brief Pop function for the Undo_Stack class.
     * @brief It pops the bottom most entry from the stack.
     * @return `void` - No parameters
     * @param void No parameters
     * @note Time complexity: O(1)
     */
    void __pop_bottom__(void)
    {
        // if you have 4 3 2 1 with 4 on top, delete 1
        if (size == 0)
        {
            cout << "Stack is empty" << endl;
        }
        else
        {
            Node<dataType> *temp = bottom;
            bottom = bottom->next;
            bottom->prev = NULL;
            delete temp;
            size--;
        }
    }

    /**
     * @brief Pop function for the Undo_Stack class.
     * @brief It pops the 2nd from bottom entry from the stack.
     * @return `void` - No parameters
     * @param void No parameters
     * @note Time complexity: O(1)
     */
    void __pop_2nd_from_bottom__(void)
    {
        // if you have 4 3 2 1 with 4 on top, delete 2
        if (size == 0)
        {
            cout << "Stack is empty" << endl;
        }
        else
        {
            Node<dataType> *temp = bottom->next;
            bottom->next = bottom->next->next;
            bottom->next->prev = bottom;
            delete temp;
            size--;
        }
    }

    /**
     * @brief Display function for the Undo_Stack class.
     * @brief It displays the stack.
     * @return `void` - No parameters
     * @param void No parameters
     * @note Time complexity: O(n)
     * @tparam dataType It can be any data type.
     */
    void __display__(void)
    {
        Node<dataType> *temp = top;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }

    /**
     * @brief Destructer for the Undo_Stack class.
     * @brief It deletes all the nodes from the stack.
     * @return `void` - No parameters
     * @param void No parameters
     * @note Time complexity: O(n)
     */
    ~Undo_Stack(void)
    {
        while (size != 0)
        {
            __pop__(); // Called in O(1) for each node, so O(n).
        }
    }
};

int main(void) // Main has been hard coded to test the Undo_Stack class.
{
    Undo_Stack<int> stack;
    cout << "Adding 1 to 100 into the stack" << endl;
    for (int i = 1; i <= 100; i++)
    {
        stack.__push__(i);
    }
    cout << "Displaying the stack" << endl;
    stack.__display__();
    cout << "Now pushing 101 into the stack" << endl;
    stack.__push__(101);
    cout << "Displaying the stack" << endl;
    stack.__display__();
    cout << "As you can see 1, ie the bottom most entry was automatically removed, because the size exceded 100" << endl;
    cout << "Now poping the stack" << endl;
    stack.__pop__();
    cout << "Displaying the stack" << endl;
    stack.__display__();
    cout << "101, the top most entry was deleted successfully" << endl;
    cout << "The size of the Stack is: " << stack.__size__() << endl;
    cout << "Note, that the pop functionality in Manual was confusing as it said to pop 2nd element" << endl;
    cout << "So, i did all pop functions" << endl;
    cout << "The above tested pop function deletes the top most element" << endl;
    cout << "Now, testing the pop_2nd_from_top function" << endl;
    stack.__pop_2nd_from_top__();
    cout << "Displaying the stack" << endl;
    stack.__display__();
    cout << "As you can see 99, ie the 2nd from top entry was deleted successfully" << endl;
    cout << "Now, testing the pop_bottom function" << endl;
    stack.__pop_bottom__();
    cout << "Displaying the stack" << endl;
    stack.__display__();
    cout << "As you can see, 2 was deleted successfully" << endl;
    cout << "Now, testing the pop_2nd_from_bottom function" << endl;
    stack.__pop_2nd_from_bottom__();
    cout << "Displaying the stack" << endl;
    stack.__display__();
    cout << "As you can see, 4 was deleted successfully" << endl;

    cout << endl;
    system("pause");
    return 0;
}