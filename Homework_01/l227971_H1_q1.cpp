#include <iostream>
using namespace std;

template <typename dataType>
class Node
{
public:
    dataType data;
    Node *next;
    Node *prev;

    Node(dataType data, Node *next = NULL, Node *prev = NULL)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

class Cart // Each cart in C(num)((items), (age)) format
{
public:
    int age;
    int cart_size; // Number of items
    int num;

    Cart(int age = 0, int cart_size = 0, int num = 0)
    {
        this->age = age;
        this->cart_size = cart_size;
        this->num = num;
    }
};

class Priority_Queue // Priority Based on highest age and then highest number of items
{
private:
    Node<Cart> *head;
    Node<Cart> *tail;
    int size;

public:
    Priority_Queue()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    Priority_Queue(const Priority_Queue &obj)
    {
        head = NULL;
        tail = NULL;
        size = 0;

        Node<Cart> *temp = obj.head;
        while (temp != NULL)
        {
            enqueue(temp->data);
            temp = temp->next;
        }
    }

    void enqueue(Cart data)
    {
        // the one with the highest age and then highest number of items should be at the front and can be taken out at first
        Node<Cart> *newNode = new Node<Cart>(data);

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            Node<Cart> *temp = head;
            while (temp != NULL && temp->data.age > data.age)
            {
                temp = temp->next;
            }

            // nevermind it is by age only
            // now by Number of items
            /*
            while (temp != NULL && temp->data.age == data.age && temp->data.cart_size > data.cart_size)
            {
                temp = temp->next;
            }
            */

            if (temp == NULL)
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            else if (temp == head)
            {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            else
            {
                newNode->next = temp;
                newNode->prev = temp->prev;
                temp->prev->next = newNode;
                temp->prev = newNode;
            }
        }

        size++;
    }

    void dequeue()
    {
        if (head != NULL)
        {
            Node<Cart> *temp = head;
            head = head->next;
            delete temp;
            size--;
        }
        else if (head == NULL)
        {
            tail = NULL;
        }
    }

    Cart top()
    {
        return head->data;
    }

    int getSize()
    {
        return size;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    Cart at_index(int index) // index starts from zero
    {
        if (index >= 0 && index < size)
        {
            Node<Cart> *temp = head;
            for (int i = 0; i < index; i++)
            {
                temp = temp->next;
            }
            return temp->data;
        }
        else
        {
            return Cart();
        }

        return Cart();
    }

    void print()
    {
        Node<Cart> *temp = head;
        while (temp != NULL)
        {
            cout << temp->data.age << " " << temp->data.cart_size;
            temp = temp->next;
            cout << endl;
        }
        cout << endl;
    }

    int lowest_age()
    {
        int s_age = 0;
        Node<Cart> *temp = head;
        while (temp != NULL)
        {
            if (temp->data.age < s_age)
            {
                s_age = temp->data.age;
            }
            temp = temp->next;
        }
        return s_age;
    }

    int highest_age()
    {
        int h_age = 0;
        Node<Cart> *temp = head;
        while (temp != NULL)
        {
            if (temp->data.age > h_age)
            {
                h_age = temp->data.age;
            }
            temp = temp->next;
        }
        return h_age;
    }

    int lowest_cart_size()
    {
        int s_cart_size = 0;
        Node<Cart> *temp = head;
        while (temp != NULL)
        {
            if (temp->data.cart_size < s_cart_size)
            {
                s_cart_size = temp->data.cart_size;
            }
            temp = temp->next;
        }
        return s_cart_size;
    }

    int highest_cart_size()
    {
        int h_cart_size = 0;
        Node<Cart> *temp = head;
        while (temp != NULL)
        {
            if (temp->data.cart_size > h_cart_size)
            {
                h_cart_size = temp->data.cart_size;
            }
            temp = temp->next;
        }
        return h_cart_size;
    }

    int Total_items()
    {
        int total_items = 0;
        Node<Cart> *temp = head;
        while (temp != NULL)
        {
            total_items += temp->data.cart_size;
            temp = temp->next;
        }
        return total_items;
    }

    ~Priority_Queue()
    {
        while (head != NULL)
        {
            Node<Cart> *temp = head;
            head = head->next;
            delete temp;
        }

        tail = NULL;

        size = 0;
    }
};

int main() // Each cart in in Cnum(items, age) format
{
    Priority_Queue queues[4]; // An array of four priority queues

    cout << "There are a total of 4 Queues at this Store" << endl;

    int num_of_customers = 0;

    char choice;

    do
    {
        cout << "Do you want to pay your bills (Y/N): ";
        cin >> choice;

        if (choice == 'Y' || choice == 'y')
        {
            Cart customer;
            cout << "Please enter how many items do you want to purchase: ";
            cin >> customer.cart_size;
            cout << "Please enter your age: ";
            cin >> customer.age;
            customer.num = ++num_of_customers;

            int size_of_arr_1 = queues[0].getSize();
            int size_of_arr_2 = queues[1].getSize();
            int size_of_arr_3 = queues[2].getSize();
            int size_of_arr_4 = queues[3].getSize();

            int items_in_arr_1 = queues[0].Total_items();
            int items_in_arr_2 = queues[1].Total_items();
            int items_in_arr_3 = queues[2].Total_items();
            int items_in_arr_4 = queues[3].Total_items();

            // put in in the shortest queue (ie least number of items)
            // If 2 or more have the same number of items, then put in the queue of smallest size.
            // If 2 or more have the same number of items and size, then put in the first queue from them

            int lowest_num_of_items = items_in_arr_1;

            if (items_in_arr_2 < lowest_num_of_items)
            {
                lowest_num_of_items = items_in_arr_2;
            }

            if (items_in_arr_3 < lowest_num_of_items)
            {
                lowest_num_of_items = items_in_arr_3;
            }

            if (items_in_arr_4 < lowest_num_of_items)
            {
                lowest_num_of_items = items_in_arr_4;
            }
            int same_count = 0;
            // Do two or more have have the same number of items?
            int arr[4] = {-1, -1, -1, -1};

            for (int i = 0; i < 4; i++)
            {
                if (queues[i].Total_items() == lowest_num_of_items)
                {
                    same_count++;
                    arr[i] = i;
                }
            }

            if (same_count == 1)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (arr[i] != -1)
                    {
                        queues[i].enqueue(customer);
                        break;
                    }
                }
            }
            else if (same_count > 1)
            {
                int lowest_size = size_of_arr_1;
                for (int i = 0; i < 4; i++)
                {
                    if (arr[i] != -1)
                    {
                        if (queues[i].getSize() < lowest_size)
                        {
                            lowest_size = queues[i].getSize();
                        }
                    }
                }

                int same_count_2 = 0;
                int arr_2[4] = {-1, -1, -1, -1};

                for (int i = 0; i < 4; i++)
                {
                    if (queues[i].getSize() == lowest_size)
                    {
                        same_count_2++;
                        arr_2[i] = i;
                    }
                }

                if (same_count_2 == 1)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        if (arr_2[i] != -1)
                        {
                            queues[i].enqueue(customer);
                            break;
                        }
                    }
                }
                else if (same_count_2 > 1)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        if (arr_2[i] != -1)
                        {
                            queues[i].enqueue(customer);
                            break;
                        }
                    }
                }
            }

            // Display the current status of all queues
            for (int i = 0; i < 4; i++)
            {
                cout << "Queue " << (i + 1) << "\t\t";
            }
            cout << endl;

            int largest_size = 0;
            for (int i = 0; i < 4; i++)
            {
                if (queues[i].getSize() > largest_size)
                {
                    largest_size = queues[i].getSize();
                }
            }

            for (int i = 0; i < largest_size; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (queues[j].getSize() > i)
                    {
                        cout << "C" << queues[j].at_index(i).num << "(" << queues[j].at_index(i).cart_size << ", " << queues[j].at_index(i).age << ")\t";
                    }
                    else
                    {
                        cout << "\t\t";
                    }
                }
                cout << endl;
            }

            cout << endl;
        }
    } while (choice == 'Y' || choice == 'y');

    cout << "Exiting Program..." << endl;

    system("pause");
    return 0;
}