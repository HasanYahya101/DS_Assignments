#include <iostream>
using namespace std;

/**
 * Note: This is a stack implementation using linked list. For Array based, check the other version.
 */

template <typename dataType>

/**
 * @brief Node class for the linked list.
 * @brief It has a data variable of type dataType and two pointers to the next and previous nodes.
 * @brief It is a Doubly Linked List.
 */
class Node
{
public:
    dataType data; // The data to be stored in the node
    Node *next;    // Pointer to the Next Node in list.
    Node *prev;    // Pointer to the Previous Node in list.
};

template <typename dataType>

/**
 * @brief Stack class implimented using linked list.
 * @brief It has a Default Constructor, push, pop, flipStack and print functions along with a Destructor.
 */
class Stack
{
private:
    Node<dataType> *top;    // The pointer to the top element of the stack
    Node<dataType> *bottom; // The pointer to the bottom element of the stack.
    int size;               // Size of the stack
    bool flipped;           // Bool to check if the stack is flipped or not.

public:
    /**
     * @brief Default Constructor for the linked list based stack class.
     * @brief It initializes the top, bottom, size and flipped variables.
     * @return `void` - Nothing
     * @param void Nothing
     * @note The time complexity of this function is O(1).
     */
    Stack(void)
    {
        top = NULL;
        bottom = NULL;
        size = 0;
        flipped = false;
    }

    /**
     * @brief Inverts the stack.
     * @brief It inverts the stack by swapping the top and bottom pointers.
     * @return `void` - Nothing
     * @param void Nothing
     * @note The time complexity of this function is O(1) as required.
     */
    void __invert__(void)
    {
        Node<dataType> *temp = top;
        top = bottom;
        bottom = temp;
        flipped = !flipped;
    }

    /**
     * @brief Converts the stack to circular list based stack.
     * @brief If the stack is empty, it prints an error message.
     * @brief If the stack is not empty, it converts the stack to circular list based stack.
     * @return `void` - Nothing
     * @param void Nothing
     * @note The time complexity of this function is O(1).
     */
    void __convert_to_circular__(void)
    {
        if (size == 0)
        {
            cout << "Stack is empty" << endl;
        }
        else
        {
            if (flipped)
            {
                top->next = bottom;
                bottom->prev = top;
            }
            else
            {
                top->prev = bottom;
                bottom->next = top;
            }
        }
    }

    /**
     * @brief Pushes an element to the stack.
     * @brief If the stack is empty, it creates a new node and assigns it to top and bottom.
     * @brief If the stack is not empty, it creates a new node and assigns it to top.
     * @return `void` - Nothing
     * @param data The data to be pushed to the stack. It can be of any data type.
     * @note The time complexity of this function is O(1).
     */
    void __push__(dataType data)
    {
        if (size == 0)
        {
            Node<dataType> *temp = new Node<dataType>;
            temp->data = data;
            temp->next = NULL;
            temp->prev = NULL;
            top = temp;
            bottom = temp;
        }
        else
        {
            if (flipped)
            {
                Node<dataType> *temp = new Node<dataType>;
                temp->data = data;
                temp->next = NULL;
                temp->prev = top;
                top->next = temp;
                top = temp;
            }
            else
            {
                Node<dataType> *temp = new Node<dataType>;
                temp->data = data;
                temp->next = top;
                temp->prev = NULL;
                top->prev = temp;
                top = temp;
            }
        }

        size++;
    }

    /**
     * @brief Pops an element from the stack.
     * @brief If the stack is empty, it prints an error message.
     * @brief If the stack is not empty, it pops the top element from the stack.
     * @return `void` - Nothing
     * @param void Nothing
     * @note The time complexity of this function is O(1).
     */
    void __pop__(void)
    {
        if (size == 0)
        {
            cout << "Stack is empty" << endl;
        }
        else
        {
            if (flipped)
            {
                Node<dataType> *temp = top;
                top = top->prev;
                delete temp;
            }
            else
            {
                Node<dataType> *temp = top;
                top = top->next;
                delete temp;
            }
            size--;
        }
    }

    /**
     * @brief Returns the size of the stack.
     * @return `int` - The size of the stack.
     * @param void Nothing
     * @note The time complexity is O(1).
     */
    int __size__(void)
    {
        return size;
    }

    /**
     * @brief Returns the top element of the stack.
     * @return `dataType` - The top element of the stack. It can be of any data type.
     * @param void Nothing
     * @note The time complexity is O(1).
     */
    dataType __top__(void)
    {
        return top->data;
    }

    /**
     * @brief Returns the bottom element of the stack.
     * @return `dataType` - The bottom element of the stack. It can be of any data type.
     * @param void Nothing
     * @note The time complexity is O(1).
     */
    dataType __bottom__(void)
    {
        return bottom->data;
    }

    /**
     * @brief Prints the stack.
     * @brief If the stack is empty, it prints an error message.
     * @brief If the stack is not empty, it prints the stack.
     * @return `void` - Nothing
     * @param void Nothing
     * @note The time complexity is N + N = O(N), where N is the size of the stack.
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
                Node<dataType> *temp = top;
                while (temp != NULL)
                {
                    cout << temp->data << " ";
                    if (temp == bottom)
                    {
                        break;
                    }
                    temp = temp->prev;
                }
            }
            else
            {
                Node<dataType> *temp = top;
                while (temp != NULL)
                {
                    cout << temp->data << " ";
                    if (temp == bottom)
                    {
                        break;
                    }
                    temp = temp->next;
                }
            }
        }
        cout << endl;
    }

    /**
     * @brief Checks if the stack is empty or not.
     * @return `bool` - True if the stack is empty, False otherwise.
     * @param void Nothing
     * @note The time complexity is O(1).
     */
    bool __empty__(void)
    {
        if (size == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief Default Destructor for the linked list based stack class.
     * @brief It deletes the stack.
     * @return `void` - Nothing
     * @param void Nothing
     * @note The time complexity of this function is O(N), where N is the size of the stack.
     */
    ~Stack(void)
    {
        while (size != 0)
        {
            __pop__(); // pop in O(1) for each element, so 1 * N = O(N).
        }
    }
};

int main(void) // The main Function was Hard Coded to test the stack.
{
    Stack<int> stack;
    cout << "Pushing 10 to 1 into stack: " << endl;
    for (int i = 10; i > 0; i--)
    {
        stack.__push__(i);
    }
    cout << "Converting stack to circular!" << endl;
    stack.__convert_to_circular__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Poping an element from stack!" << endl;
    stack.__pop__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Inverting stack!" << endl;
    stack.__invert__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Poping an element from stack!" << endl;
    stack.__pop__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Inverting stack!" << endl;
    stack.__invert__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Poping an element from stack!" << endl;
    stack.__pop__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Inverting stack!" << endl;
    stack.__invert__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Poping an element from stack!" << endl;
    stack.__pop__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Inverting stack!" << endl;
    stack.__invert__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Poping an element from stack!" << endl;
    stack.__pop__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Inverting stack!" << endl;
    stack.__invert__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Poping an element from stack!" << endl;
    stack.__pop__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Inverting stack!" << endl;
    stack.__invert__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Poping an element from stack!" << endl;
    stack.__pop__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Inverting stack!" << endl;
    stack.__invert__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Poping an element from stack!" << endl;
    stack.__pop__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Inverting stack!" << endl;
    stack.__invert__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Poping an element from stack!" << endl;
    stack.__pop__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Inverting stack!" << endl;
    stack.__invert__();
    cout << "Printing stack: " << endl;
    stack.__print__();
    cout << "Poping an element from stack!" << endl;
    stack.__pop__();
    cout << "Printing stack: " << endl;
    stack.__print__();

    system("pause");
    return 0;
}