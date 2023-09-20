#include <iostream>
using namespace std;

/**
 * All Time Complexities given below are by my current knowledge.
 * Please, double check them before using them.
 */

template <class dataType>

/**
 * Node Class for Linked List. Each Node has a value and a pointer to next Node.
 * It has 3 constructors, 2 getters, 2 setters, 1 print function and 1 destructor.
 * val is the value of the Node. It can be of any dataType.
 * ptr is the pointer to the next Node. It is of Node<dataType> type.
 */
class Node
{
private:
    dataType val;
    Node<dataType> *ptr;

public:
    /**
     * @brief Constructor that will initialize the Node with NULL values. There is no return type.
     * @brief You will have to use getters and setters to initialize the values.
     * @brief Time Complexity: 1 = O(1). Note: The time complexity is for the Assignment Operator.
     * @brief It is not for the Constructor itself as it is just a declaration.
     * @brief This is the same for all Constructors below as well.
     */
    Node()
    {
        ptr = NULL;
    }

    /**
     * @brief Constructor that will initialize the Node with given values. There is no return type.
     * @brief You will have not have to use getters and setters to initialize the val variable
     * @brief Time Complexity: 1 + 1 = O(1).
     * @param val is the value of the Node. It can be of any dataType.
     */
    Node(dataType val)
    {
        this->val = val;
        ptr = NULL;
    }

    /**
     * @brief Constructor that will initialize the Node with given values. There is no return type.
     * @brief You will have not have to use getters and setters to initialize the val variable.
     * @brief A Node will be created with given value and pointer to next Node.
     * @brief Time Complexity: 1 + 1 = O(1).
     */
    Node(dataType val, Node<dataType> *ptr)
    {
        this->val = val;
        this->ptr = ptr;
    }

    /**
     * @brief Set the Val object as given value.
     * @brief Time Complexity: 1 = O(1).
     * @param val is the value of the Node. It can be of any dataType.
     * @return void - No Value.
     */
    void setVal(dataType val)
    {
        this->val = val;
    }

    /**
     * @brief It is a getter for the val variable.
     * @brief Time Complexity: 1 = O(1).
     * @return dataType - It is the value of the Node. It can be of any dataType.
     */
    dataType getVal()
    {
        return val;
    }

    /**
     * @brief Set the Ptr object as given address. It must point to a Node.
     * @brief Time Complexity: 1 = O(1).
     * @param ptr is the pointer to the next Node. It is of Node<dataType> type.
     * @return void - No Value.
     */
    void setPtr(Node<dataType> *ptr)
    {
        this->ptr = ptr;
    }

    /**
     * @brief It is a getter for the ptr variable.
     * @brief Time Complexity: 1 = O(1).
     * @return Node<dataType>* - It is the pointer to the next Node. It is of Node<dataType> type.
     */
    Node<dataType> *getPtr()
    {
        return ptr;
    }

    /**
     * @brief It will print the value of the Node along with a Space " ".
     * @brief Time Complexity: 1 + 1 = 2 = O(1).
     * @return void - No Value.
     */
    void print()
    {
        cout << val << " ";
    }

    /**
     * @brief Destructor for the Node Class. It will delete the Node created on Heap.
     */
    ~Node() // takes Zero time.
    {
        ptr = NULL;
        // Handled in the Sorted_Set Class.
        // To prevent Double Deletion.
    }
};

template <class dataType>

/**
 * Sorted_Set Class for Linked List. Each Sorted_Set has a head_ptr and a tail_ptr.
 * It has 1 constructor, 2 getters, 2 setters, 1 print function and 1 destructor.
 * head_ptr is the pointer to the first Node of the Linked List. It is of Node<dataType> type.
 * tail_ptr is the pointer to the last Node of the Linked List. It is of Node<dataType> type.
 * It is a Sorted Linked List. It is sorted in ascending order and no Duplicates are allowed.
 * It has 3 functions:
 * 1. __insert_val__(dataType const data) - It will insert the given value in the Sorted_Set.
 * 2. __delete_val__(int const index) - It will delete the value present at the given index.
 * 3. __union__(Sorted_Set<dataType> const &otherSet) - It will take the union of the two Sorted_Sets.
 */
class Sorted_Set
{
private:
    Node<dataType> *head_ptr;
    Node<dataType> *tail_ptr;

    /**
     * @brief Function to append the Node to the Result Linked List.
     * @brief Time Complexity: 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + ... = O(n).
     * @brief It is only supposed to be a helper function of the __union__ function.
     * @param prevResult is the pointer to the last Node of the Result Linked List.
     * @param node is the pointer to the Node to be appended to the Result Linked List.
     * @return void - No Value.
     */
    void appendToResult(Node<dataType> *&prevResult, Node<dataType> *&node)
    {
        if (prevResult == NULL)
        {
            this->head_ptr = node;
            prevResult = node;
        }
        else
        {
            prevResult->setPtr(node);
            prevResult = node;
        }
    }

public:
    /**
     * @brief Constructor that will initialize the Sorted_Set with NULL values. There is no return type.
     * @brief You will have to use getters and setters to initialize the values.
     * @brief Time Complexity: 1 + 1 = O(1). Note: The time complexity is for the Assignment Operators.
     */
    Sorted_Set()
    {
        head_ptr = NULL; // takes 1 time.
        tail_ptr = NULL; // takes 1 time.
    }

    /**
     * @brief It is also a constructor that will initialize the Sorted_Set with given values.
     * @brief It will create a Sorted_Set with given value.
     * @brief Both head_ptr and tail_ptr will point to first Node.
     * @brief Time Complexity: 1 + 1 + O(1) = O(1).
     */
    Sorted_Set(dataType val)
    {
        // assignment operator takes 1 time. But the constructor of Node takes O(1) time itself. But the Node created on Heap depends on the Size of Class.
        // So, as we know above that the Node class takes O(1) time. So, the constructor of Node class will also take 1 + 1 = 2 = O(1) time.
        //  But this is only True for this Class. It is not True for all Classes.
        head_ptr = new Node<dataType>(val);
        tail_ptr = head_ptr; // assignment operator takes 1 time.
    }

    /**
     * @brief Function to insert the given value in the Sorted_Set. The values will be in Ascending Order.
     * @brief No Duplicates are allowed. The time complexity is O(n).
     * @param data is the value to be inserted in the Sorted_Set. It can be of any dataType.
     */
    void __insert_val__(dataType const data)
    {
        if (head_ptr == NULL) // 1 time.
        {
            // 1 + O(1) = O(1) time. As explained above.
            head_ptr = new Node<dataType>(data);
            tail_ptr = head_ptr; // 1 time.
        }
        else
        {
            Node<dataType> *temp = head_ptr; // 1 time.
            Node<dataType> *prev = NULL;     // 1 time.
            while (temp != NULL)             // n times. ie the size of the Linked List. As we have to traverse the whole Linked List.
            {
                if (temp->getVal() == data) // 1 time.
                {
                    return;
                }
                else if (temp->getVal() > data)
                {
                    if (prev == NULL)
                    {
                        head_ptr = new Node<dataType>(data, head_ptr); // 1 + O(1) = O(1) time. As explained above.
                    }
                    else
                    {
                        prev->setPtr(new Node<dataType>(data, temp)); // same as above.
                    }
                    return;
                }
                // 1 time.
                prev = temp;
                temp = temp->getPtr(); // 1 time.
            }
            prev->setPtr(new Node<dataType>(data)); // check the function setPtr() above. It takes O(1) time.
            // check the function getPtr. The assignment operator "=" takes 1 time.
            tail_ptr = prev->getPtr();
        }
    }

    /**
     * @brief Function to delete the value present at the given index.
     * @brief It will remove the Extra Node created on Heap.
     * @brief Time Complexity: 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + ... + n + n + n = 10 + 3n = O(n).
     * @param index is the index of the value to be deleted.
     */
    void __delete_val__(int const index)
    {
        if (head_ptr == NULL) // 1 time.
        {
            return;
        }
        else if (index == 0) // 1 time.
        {
            Node<dataType> *temp = head_ptr; // 1 time.
            head_ptr = head_ptr->getPtr();
            temp->setPtr(NULL);
            delete temp;
            Node<dataType> *temp2 = head_ptr; // 1 time.
            if (head_ptr == NULL)             // 1 time.
            {
                tail_ptr = NULL;
                return;
            }
            // point the tail ptr to end of the Linked List.
            while (temp2 != NULL) // n times. ie the size of the Linked List. As we have to traverse the whole Linked List.
            {
                if (temp2->getPtr() == NULL) // 1 time.
                {
                    tail_ptr = temp2;
                    return;
                }
                temp2 = temp2->getPtr();
            }
        }
        else
        {
            Node<dataType> *temp = head_ptr;
            Node<dataType> *prev = NULL;
            int i = 0;
            while (temp != NULL) // n times. ie the size of the Linked List. As we have to traverse the whole Linked List.
            {
                if (i == index) // 1 time.
                {
                    prev->setPtr(temp->getPtr());
                    temp->setPtr(NULL);
                    delete temp;
                    return;
                }
                prev = temp;
                temp = temp->getPtr();
                i++;
            }
            // point the tail ptr to end of the Linked List.
            Node<dataType> *temp2 = head_ptr; // 1 time.

            while (temp2 != NULL) // n times. ie the size of the Linked List. As we have to traverse the whole Linked List.
            {
                if (temp2->getPtr() == NULL) // 1 time.
                {
                    tail_ptr = temp2;
                    return;
                }
                temp2 = temp2->getPtr();
            }
        }
    }

    /**
     * @brief Function to take the union of the two Sorted_Sets.
     * @brief It will take the union of the two Sorted_Sets and store it in the first Sorted_Set.
     * @brief The values will be in Ascending Order. No Duplicates are allowed.
     * @brief Time Complexity: n = O(n).
     * @brief For example:
     * @brief SortedSet a: (suppose it has 1, 2, 3, 4, 10, 50).
     * @brief Now, SortedSet b: (suppose it has 6, 10, 11).
     * @brief Function: a.__union__(b); (a will now contain 1, 2, 3, 4, 6, 10, 11, 50).
     * @param otherSet is the Sorted_Set to be taken union with.
     * @return void - No Value.
     */
    void __union__(Sorted_Set<dataType> &otherSet)
    {

        Node<dataType> *temp1 = this->head_ptr;
        Node<dataType> *temp2 = otherSet.head_ptr;
        Node<dataType> *prevResult = NULL;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;

        while (temp1 != NULL || temp2 != NULL) // takes n times. ie the size of the Linked List. As we have to traverse the whole Linked List.
        {
            if (temp1 == NULL)
            {
                appendToResult(prevResult, temp2);
                break;
            }
            else if (temp2 == NULL)
            {
                appendToResult(prevResult, temp1);
                break;
            }
            else if (temp1->getVal() < temp2->getVal())
            {
                appendToResult(prevResult, temp1);
                temp1 = temp1->getPtr();
            }
            else if (temp1->getVal() > temp2->getVal())
            {
                appendToResult(prevResult, temp2);
                temp2 = temp2->getPtr();
            }
            else
            {
                // Duplicate values, include only once
                appendToResult(prevResult, temp1);
                temp1 = temp1->getPtr();
                temp2 = temp2->getPtr();
            }
        }

        // point the tail ptr to end of the Linked List.
        Node<dataType> *temp3 = this->head_ptr;
        while (temp3 != NULL)
        {
            if (temp3->getPtr() == NULL)
            {
                this->tail_ptr = temp3;
                return;
            }
            temp3 = temp3->getPtr();
        }
    }

    /**
     * @brief Rotate the List Counter Clockwise by the given value.
     * @brief Time Complexity: n + n = 2n = O(n).
     * @param val is the value to rotate the List Counter Clockwise.
     */
    void __rotate__(int val)
    {
        // 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
        // 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> 1 -> 2, val = 2
        // 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
        // 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> 1 -> 2 -> 3, val = 13
        if (val == 0)
        {
            return;
        }
        if (head_ptr == NULL)
        {
            cout << "The List is Empty." << endl;
            return;
        }
        // calculate the size of the Linked List.
        Node<dataType> *temp_size = head_ptr;
        int size = 0;
        while (temp_size != NULL)
        {
            size++;
            temp_size = temp_size->getPtr();
        }
        if (size == 1)
        {
            return;
        }
        if (val > size)
        {
            val = val % size;
        }
        Node<dataType> *temp = head_ptr;
        Node<dataType> *prev = NULL;
        int i = 0;
        while (temp != NULL)
        {
            if (i == val)
            {
                prev->setPtr(NULL);
                tail_ptr->setPtr(head_ptr);
                head_ptr = temp;
                return;
            }
            prev = temp;
            temp = temp->getPtr();
            i++;
        }
    }

    /**
     * @brief Print the values of the Sorted_Set.
     * @brief Time Complexity: n = O(n).
     */
    void __print__() const
    {
        Node<dataType> *temp = head_ptr;
        while (temp != NULL) // takes n times.
        {
            temp->print();
            temp = temp->getPtr();
        }
        cout << endl;
    }

    ~Sorted_Set() // takes O(1) time.
    {
        delete head_ptr; // takes O(1) time.
        tail_ptr = NULL; // takes O(1) time.
        head_ptr = NULL; // takes O(1) time.
    }
};

int main()
{
    Sorted_Set<int> test_set;

    cout << "Enter a number to add to the Set: ";
    int val;
    cin >> val;
    test_set.__insert_val__(val);
    cout << "Do you want to add another number? (y/n): ";
    char choice;
    cin >> choice;
    while (choice == 'y')
    {
        cout << "Enter a number to add to the Set: ";
        cin >> val;
        test_set.__insert_val__(val);
        cout << "Do you want to add another number? (y/n): ";
        cin >> choice;
    }
    cout << "Your List is: ";
    test_set.__print__();
    cout << "Enter a number (positive or Zero) to rotate the set by: ";
    cin >> val;
    while (val < 0)
    {
        cout << "Please, enter a positive number or Zero: ";
        cin >> val;
    }
    test_set.__rotate__(val);
    cout << "Your List is: ";
    test_set.__print__();

    system("pause");
    return 0;
}
