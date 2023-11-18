#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#define STR_ERROR "Not Found"

template <typename Type>
class queue_node
{
public:
    Type data;
    queue_node *next;

    queue_node(Type data)
    {
        this->data = data;
        next = nullptr;
    }
};

template <typename Type>

class queue
{
private:
    queue_node<Type> *front;
    queue_node<Type> *rear;
    int size;

public:
    queue()
    {
        front = nullptr;
        rear = nullptr;
        size = 0;
    }

    void enqueue(Type data)
    {
        queue_node<Type> *new_node = new queue_node<Type>(data);
        if (front == nullptr)
        {
            front = new_node;
            rear = new_node;
        }
        else
        {
            rear->next = new_node;
            rear = new_node;
        }
        size++;
    }

    int Size()
    {
        return size;
    }

    bool empty()
    {
        return size == 0;
    }

    void convert_to_ascending()
    {
        // convert the queue to ascending order with the minimum value at the front
        // using bubble sort
        queue_node<Type> *current = front;
        while (current != nullptr)
        {
            queue_node<Type> *current2 = front;
            while (current2->next != nullptr)
            {
                if (current2->data > current2->next->data)
                {
                    Type temp = current2->data;
                    current2->data = current2->next->data;
                    current2->next->data = temp;
                }
                current2 = current2->next;
            }
            current = current->next;
        }
    }

    void push(Type data)
    {
        queue_node<Type> *new_node = new queue_node<Type>(data);
        if (front == nullptr)
        {
            front = new_node;
            rear = new_node;
        }
        else
        {
            rear->next = new_node;
            rear = new_node;
        }
        size++;
    }

    void push_no_duplicates(Type data)
    {
        // if data already exists, don't push
        if (front == nullptr)
        {
            queue_node<Type> *new_node = new queue_node<Type>(data);
            front = new_node;
            rear = new_node;
            size++;
        }
        else
        {
            queue_node<Type> *current = front;
            while (current != nullptr)
            {
                if (current->data == data)
                {
                    return;
                }
                current = current->next;
            }
            queue_node<Type> *new_node = new queue_node<Type>(data);
            rear->next = new_node;
            rear = new_node;
            size++;
        }
    }

    Type dequeue()
    {
        if (front == nullptr)
        {
            return NULL;
        }
        else
        {
            queue_node<Type> *temp = front;
            Type data = temp->data;
            front = front->next;
            delete temp;
            size--;
            return data;
        }
    }

    Type pop()
    {
        if (front == nullptr)
        {
            return NULL;
        }
        else
        {
            queue_node<Type> *temp = front;
            Type data = temp->data;
            front = front->next;
            delete temp;
            size--;
            return data;
        }
    }

    Type peek()
    {
        if (front == nullptr)
        {
            return NULL;
        }
        else
        {
            return front->data;
        }
    }

    bool is_empty()
    {
        return size == 0;
    }

    int get_size()
    {
        return size;
    }
};

template <typename Type>

class Node
{
public:
    Type data;
    Node *left;
    Node *right;
    int height;

    // constructors
    Node()
    {
        left = nullptr;
        right = nullptr;
    }
    Node(Type data)
    {
        this->data = data;
        this->height = 1;
        left = nullptr;
        right = nullptr;
    }
    Node(Type data, Node *left, Node *right)
    {
        this->data = data;
        this->left = left;
        this->right = right;
        this->height = 1;
    }
};

template <typename Type>

class BST // Binary Search Tree, based on AVL Tree
{
protected:
    Node<Type> *root;

public:
    int size;
};

struct Link
{
public:
    int id;
    string url_text;

    Link()
    {
        id = -1;
        url_text = "";
    }
};

class Links : public BST<Link>
{
public:
    Links()
    {
        root = NULL;
        size = 0;
    }

    bool already_exist(int key)
    {
        // If an ID already exists in the tree, return true
        Node<Link> *current = root;
        if (current == NULL)
        {
            return false;
        }

        while (current->data.id != key)
        {
            if (key < current->data.id)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
            if (current == NULL)
            {
                return false;
            }
        }
        return true;
    }

    bool already_exists(string val)
    {
        // If a URL already exists in the tree, return true
        Node<Link> *current = root;

        if (current == NULL)
        {
            return false;
        }

        while (current->data.url_text != val)
        {
            if (val < current->data.url_text)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
            if (current == NULL)
            {
                return false;
            }
        }
        return true;
    }

    Node<Link> *insert(Node<Link> *node, Link link)
    {
        if (node == nullptr)
        {
            size++;
            return new Node<Link>(link);
        }
        if (link.id < node->data.id)
        {
            node->left = insert(node->left, link);
        }
        else if (link.id > node->data.id)
        {
            node->right = insert(node->right, link);
        }
        else
        {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        return node;
    }

    void insert(Link link) // helper function for recursion
    {
        // if id, return false
        if (already_exist(link.id))
        {
            return;
        }

        // recursive function
        root = insert(root, link);
    }

    string search(int key)
    {
        // return url_text of a given id(key)
        Node<Link> *current = root;
        while (current->data.id != key)
        {
            if (key < current->data.id)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }

            if (current == NULL)
            {
                return STR_ERROR; // returns string "Not Found"
            }
        }
        return current->data.url_text;
    }

    int getHeight(Node<Link> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node<Link> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void print_level_by_level()
    {
        print_level_by_level(root);
    }

    void print_level_by_level(Node<Link> *node)
    {
        queue<Node<Link> *> q;
        q.push(node);

        // print one level/height in the same line
        while (q.empty() == false)
        {
            int count = q.Size();
            while (count > 0)
            {
                Node<Link> *current = q.peek();
                cout << current->data.id << " ";
                q.pop();
                if (current->left != NULL)
                {
                    q.push(current->left);
                }
                if (current->right != NULL)
                {
                    q.push(current->right);
                }
                count--;
            }
            cout << endl;
        }
    }

    void print_3_traversals()
    {
        cout << "Inorder: ";
        Inorder_Print();
        cout << endl;
        cout << "Preorder: ";
        Preorder_Print();
        cout << endl;
        cout << "Postorder: ";
        Postorder_Print();
        cout << endl;
    }

    void Inorder_Print(Node<Link> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        Inorder_Print(node->left);
        cout << node->data.id << " ";
        Inorder_Print(node->right);
    }

    void Inorder_Print()
    {
        Inorder_Print(root);
    }

    void Preorder_Print(Node<Link> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        cout << node->data.id << " ";
        Preorder_Print(node->left);
        Preorder_Print(node->right);
    }

    void Preorder_Print()
    {
        Preorder_Print(root);
    }

    void Postorder_Print(Node<Link> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        Postorder_Print(node->left);
        Postorder_Print(node->right);
        cout << node->data.id << " ";
    }

    void Postorder_Print()
    {
        Postorder_Print(root);
    }

    bool IS_Balanced(Node<Link> *node)
    {
        if (node == NULL)
        {
            return true;
        }

        int balance = getBalance(node);

        if (balance > 1 || balance < -1)
        {
            return false;
        }

        return IS_Balanced(node->left) && IS_Balanced(node->right);
    }

    bool IS_Balanced()
    {
        // is balanced as an AVL tree
        return IS_Balanced(root);
    }

    string to_str(bool val)
    {
        if (val)
        {
            return "True";
        }
        else
        {
            return "False";
        }
    }

    void test_balance_and_print()
    {
        cout << endl;
        // print level by level
        print_level_by_level();

        // check if balanced
        cout << "\nIs Balanced: " << to_str(IS_Balanced()) << endl;
    }
};

struct Word
{
public:
    string word;
    queue<int> link_id;

    Word()
    {
        word = "";
    }

    Word(string word, int link_id)
    {
        this->word = word;
        this->link_id.push_no_duplicates(link_id);
    }
};

class Words : public BST<Word>
{
public:
    Words()
    {
        root = NULL;
        size = 0;
    }

    bool delete_word(string word)
    {
        // delete a word from the tree
        Node<Word> *current = root;
        Node<Word> *parent = root;
        bool is_left = true;

        if (current == NULL)
        {
            return false;
        }

        while (current->data.word != word)
        {
            parent = current;
            if (word < current->data.word)
            {
                is_left = true;
                current = current->left;
            }
            else
            {
                is_left = false;
                current = current->right;
            }

            if (current == NULL)
            {
                return false;
            }
        }

        // if node is a leaf
        if (current->left == NULL && current->right == NULL)
        {
            if (current == root)
            {
                root = NULL;
            }
            else if (is_left)
            {
                parent->left = NULL;
            }
            else
            {
                parent->right = NULL;
            }
        }
        // if node has one child that is on the left
        else if (current->right == NULL)
        {
            if (current == root)
            {
                root = current->left;
            }
            else if (is_left)
            {
                parent->left = current->left;
            }
            else
            {
                parent->right = current->left;
            }
        }
        // if node has one child that is on the right
        else if (current->left == NULL)
        {
            if (current == root)
            {
                root = current->right;
            }
            else if (is_left)
            {
                parent->left = current->right;
            }
            else
            {
                parent->right = current->right;
            }
        }
        // if node has two children
        else
        {
            Node<Word> *successor = get_successor(current);
            if (current == root)
            {
                root = successor;
            }
            else if (is_left)
            {
                parent->left = successor;
            }
            else
            {
                parent->right = successor;
            }
            successor->left = current->left;
        }
        size--;
        return true;
    }

    Node<Word> *get_successor(Node<Word> *node)
    {
        Node<Word> *current = node->right;
        Node<Word> *parent = node;
        Node<Word> *successor = node;

        while (current != NULL)
        {
            parent = successor;
            successor = current;
            current = current->left;
        }

        if (successor != node->right)
        {
            parent->left = successor->right;
            successor->right = node->right;
        }

        return successor;
    }

    bool already_exist(string key, int link_id)
    {
        // If an ID already exists in the tree, return true after inserting the link_id into that word
        Node<Word> *current = root;
        if (current == NULL)
        {
            return false;
        }

        while (current->data.word != key)
        {
            if (key < current->data.word)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
            if (current == NULL)
            {
                return false;
            }
        }
        current->data.link_id.push_no_duplicates(link_id);
        return true;
    }

    Node<Word> *insert(Node<Word> *node, Word word_new)
    {
        if (node == nullptr)
        {
            size++;
            return new Node<Word>(word_new);
        }
        if (word_new.word < node->data.word)
        {
            node->left = insert(node->left, word_new);
        }
        else if (word_new.word > node->data.word)
        {
            node->right = insert(node->right, word_new);
        }
        else
        {
            return node;
        }

        return node;
    }

    void insert(Word word_new) // helper function for recursion
    {
        // if id, return false
        if (already_exist(word_new.word, word_new.link_id.peek()))
        {
            return;
        }

        // recursive function
        root = insert(root, word_new);
    }

    queue<int> search(string key)
    {
        // return url_text of a given id(key)
        Node<Word> *current = root;
        while (current->data.word != key)
        {
            if (key < current->data.word)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }

            if (current == NULL)
            {
                return queue<int>(); // returns empty queue
            }
        }
        // return the whole of queue
        return current->data.link_id;
    }

    int getHeight(Node<Word> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node<Word> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void print_level_by_level()
    {
        print_level_by_level(root);
    }

    void print_level_by_level(Node<Word> *node)
    {
        queue<Node<Word> *> q;
        q.push(node);

        // print one level/height in the same line
        while (q.empty() == false)
        {
            int count = q.Size();
            while (count > 0)
            {
                Node<Word> *current = q.peek();
                cout << current->data.word << " ";
                q.pop();
                if (current->left != NULL)
                {
                    q.push(current->left);
                }
                if (current->right != NULL)
                {
                    q.push(current->right);
                }
                count--;
            }
            cout << endl;
        }
    }

    void print_3_traversals()
    {
        cout << "Inorder: ";
        Inorder_Print();
        cout << endl;
        cout << "Preorder: ";
        Preorder_Print();
        cout << endl;
        cout << "Postorder: ";
        Postorder_Print();
        cout << endl;
    }

    void Inorder_Print(Node<Word> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        Inorder_Print(node->left);
        cout << node->data.word << " ";
        Inorder_Print(node->right);
    }

    void Inorder_Print()
    {
        Inorder_Print(root);
    }

    void Preorder_Print(Node<Word> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        cout << node->data.word << " ";
        Preorder_Print(node->left);
        Preorder_Print(node->right);
    }

    void Preorder_Print()
    {
        Preorder_Print(root);
    }

    void Postorder_Print(Node<Word> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        Postorder_Print(node->left);
        Postorder_Print(node->right);
        cout << node->data.word << " ";
    }

    void Postorder_Print()
    {
        Postorder_Print(root);
    }

    bool IS_Balanced(Node<Word> *node)
    {
        if (node == NULL)
        {
            return true;
        }

        int balance = getBalance(node);

        if (balance > 1 || balance < -1)
        {
            return false;
        }

        return IS_Balanced(node->left) && IS_Balanced(node->right);
    }

    bool IS_Balanced()
    {
        // is balanced as an AVL tree
        return IS_Balanced(root);
    }

    string to_str(bool val)
    {
        if (val)
        {
            return "True";
        }
        else
        {
            return "False";
        }
    }

    void test_balance_and_print()
    {
        cout << endl;
        // print level by level
        print_level_by_level();

        // check if balanced
        cout << "\nIs Balanced: " << to_str(IS_Balanced()) << endl;
    }
};

enum Tag
{
    LINK_LINE,
    WORD_LINE
};

Tag is_tag_type(string line)
{
    if (line.find("http://www.") != string::npos && line.find(".html") != string::npos) // line must contain both "http://www." and ".html"
    {
        return LINK_LINE;
    }
    else if (line.find("http://www.") == string::npos && line.find(".html") == string::npos)
    {
        return WORD_LINE;
    }
    else
    {
        return LINK_LINE;
    }
}

string to_str(bool val)
{
    if (val)
    {
        return "true";
    }
    else
    {
        return "false";
    }
}

int main()
{
    system("cls");
    Links links;
    Words words;
    string file_name_input;
    std::cout << "Please Enter File Name (with extension): ";
    getline(cin, file_name_input);

    while (file_name_input == "" || file_name_input.find(".txt") == string::npos || file_name_input.find(" ") != string::npos)
    {
        std::cout << "File name not Allowed, Please Enter the actual File Name: ";
        getline(cin, file_name_input);
    }

    ifstream file(file_name_input);
    if (!file.is_open())
    {
        std::cout << "File not found, Exiting Program..." << endl;
        system("pause");
        return 0;
    }
    string line;
    int empty_count = 0;
    bool file_end = false; // File ends when 2 empty lines are read
    int current_link_id = -1;
    int previous_link_id = -1;
    while (getline(file, line))
    {
        if (line == "")
        {
            empty_count++;
        }

        if (empty_count == 2)
        {
            file_end = true;
            break;
        }

        if (line != "" && empty_count > 0)
        {
            empty_count = 0;
        }

        if (line != "")
        {
            if (is_tag_type(line) == LINK_LINE)
            {
                // taking the text before the first space
                string code_text = line.substr(0, line.find(" "));
                // remove any spaces from the code_text
                string new_code_text = "";
                for (int i = 0; i < code_text.length(); i++)
                {
                    if (code_text[i] != ' ')
                    {
                        new_code_text += code_text[i];
                    }
                }
                // convert the code_text to int
                int code_for_link = stoi(new_code_text);
                string link_value = line.substr(line.find("http://www."), line.find(".html") + 5 - line.find("http://www."));
                Link link;
                previous_link_id = code_for_link;
                link.id = code_for_link;
                link.url_text = link_value;
                links.insert(link);
                current_link_id = code_for_link;
            }
            else if (is_tag_type(line) == WORD_LINE)
            {
                string word = line.substr(0, line.find(" "));
                int temp_num = previous_link_id;
                Word word_new;
                word_new.word = word;
                word_new.link_id.push_no_duplicates(temp_num);
                words.insert(word_new);
                while (line.find(" ") != string::npos)
                {
                    line = line.substr(line.find(" ") + 1, line.length() - line.find(" ") - 1);
                    word = line.substr(0, line.find(" "));
                    Word word_new_new;
                    word_new_new.word = word;
                    word_new_new.link_id.push_no_duplicates(temp_num);
                    words.insert(word_new_new);
                }
            }
        }
    }
    file.close();
    std::cout << endl;

    // links.test_balance_and_print(); // Testing the Balance of Tree, remove comments to check
    // words.test_balance_and_print(); // Testing the Balance of Tree, remove comments to check
    // system("pause"); // to pause and view tree balance before continuing
    cout << "Do you want to delete a word? (y/n): ";
    string delete_word_choice;
    getline(cin, delete_word_choice);
    while (delete_word_choice != "y" && delete_word_choice != "n")
    {
        cout << "Invalid Choice, Do you want to delete a word? (y/n): ";
        getline(cin, delete_word_choice);
    }

    if (delete_word_choice == "y")
    {
        cout << "Enter Word to Delete: ";
        string word_to_delete;
        getline(cin, word_to_delete);
        while (word_to_delete == "" || word_to_delete.find(" ") != string::npos)
        {
            cout << "\nWord cannot be empty or contain spaces, Enter Word to Delete: ";
            getline(cin, word_to_delete);
        }
        cout << endl
             << endl;
        bool value = words.delete_word(word_to_delete);
        if (value)
        {
            cout << "Word Deleted Successfully" << endl;
        }
        else
        {
            cout << "Word not found in any link" << endl;
        }
        cout << endl
             << endl;
    }

    // tp test word deletion
    // words.test_balance_and_print(); // Testing the Balance of Tree, remove comments to check
    // system("pause");                // to pause and view tree balance before continuing
    // cout << endl << endl;

    cout << "Enter Word to Search: ";
    string word_to_search;
    getline(cin, word_to_search);
    while (word_to_search == "" || word_to_search.find(" ") != string::npos)
    {
        cout << "\nWord cannot be empty or contain spaces, Enter Word to Search: ";
        getline(cin, word_to_search);
    }
    cout << endl
         << endl;

    queue<int> link_ids = words.search(word_to_search);
    int link_ids_size = link_ids.get_size();
    int start = 1;
    if (link_ids.empty())
    {
        cout << "\nError: Word not found in any link\n"
             << endl;
    }
    else
    {
        cout << "Word found in " << link_ids_size << " links: " << endl;
        while (!link_ids.empty())
        {
            int link_id = link_ids.pop();
            string url_text = links.search(link_id);
            cout << start << ". Link ID: " << link_id << ", URL: " << url_text << endl;
            start++;
        }
        cout << endl;
    }
    cout << endl
         << endl;

    system("pause");
    return 0;
}
