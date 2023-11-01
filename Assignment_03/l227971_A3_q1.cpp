#include <iostream> // for cin and cout
#include <string>   // for text
#include <cmath>    // for cos and sin to calc angles
#include <thread>   // for sleep
#include <chrono>   // for calculating time for sleep
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

template <typename dataType>

class Node
{
public:
    dataType data;
    Node *next;
    Node(dataType data)
    {
        this->data = data;
        this->next = NULL;
    }

    Node(dataType data, Node *next)
    {
        this->data = data;
        this->next = next;
    }

    ~Node()
    {
        if (next != NULL)
        {
            delete next;
        }
    }
};

template <typename dataType>

class Josephus_Queue // queue using linked list
{
public:
    Node<dataType> *head;
    Node<dataType> *tail;
    int size;

    Josephus_Queue()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    ~Josephus_Queue()
    {
        if (head != NULL)
        {
            delete head;
        }
    }

    void push(dataType data)
    {
        if (head == NULL)
        {
            head = new Node<dataType>(data);
            tail = head;
        }
        else
        {
            tail->next = new Node<dataType>(data);
            tail = tail->next;
        }
        size++;
    }

    void push_node(Node<dataType> *node)
    {
        if (head == NULL)
        {
            head = node;
            tail = head;
        }
        else
        {
            tail->next = node;
            tail = tail->next;
        }
        size++;
    }

    dataType pop()
    {
        if (head == NULL)
            return -1;
        else
        {
            dataType data = head->data;
            Node<dataType> *temp = head;
            head = head->next;
            temp->next = NULL;
            delete temp;
            size--;
            return data;
        }
    }

    Node<dataType> *pop_node()
    {
        if (head == NULL)
            return NULL;
        else
        {
            Node<dataType> *temp = head;
            head = head->next;
            temp->next = NULL;
            size--;
            return temp;
        }
    }

    int get_size()
    {
        return size;
    }

    void print()
    {
        Node<dataType> *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    dataType front()
    {
        if (head == NULL)
        {
            return -1;
        }
        else
        {
            return head->data;
        }
    }

    dataType back()
    {
        if (tail == NULL)
        {
            return -1;
        }
        else
        {
            return tail->data;
        }
    }

    dataType value(int index)
    {
        // starts from 0
        if (index < 0 || index >= size)
        {
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

    bool is_empty()
    {
        if (head == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

template <typename dataType>

struct Person
{
public:
    dataType id;
    bool alive;

    Person()
    {
        this->id = 0;
        this->alive = true;
    }

    Person(dataType id)
    {
        this->id = id;
        this->alive = true;
    }

    Person(dataType id, bool alive)
    {
        this->id = id;
        this->alive = alive;
    }

    void setAlive(bool isAlive)
    {
        alive = isAlive;
    }
};

int isValid(int size, int to_kill)
{
    if (to_kill > size)
    {
        return to_kill % size;
    }
    else
    {
        return to_kill;
    }
}

int total_alive(Josephus_Queue<Person<int>> people)
{
    int count = 0;
    for (int i = 0; i < people.get_size(); i++)
    {
        if (people.value(i).alive == true)
        {
            count++;
        }
    }
    return count;
}

int main()
{
    Josephus_Queue<int> queue;
    Josephus_Queue<int> queue_gui;
    int size;
    cout << "Enter Size of the Queue: ";
    cin >> size;

    while (size < 2 || size > 25)
    {
        cout << "Error: Size must be Between 1 and 25!" << endl;
        cout << "Enter Size Again: ";
        cin >> size;
    }
    for (int i = 1; i <= size; i++)
    {
        queue.push(i);
        queue_gui.push(i);
    }
    cout << "Your queue will have the following members: " << endl;
    queue.print();
    cout << endl;
    cout << "Enter the Number you want to start from: ";
    int start;
    cin >> start;
    while (start < 1 || start > size)
    {
        cout << "Error: Enter a Number Between 1 and " << size << endl;
        cin >> start;
    }
    for (int i = 1; i < start; i++)
    {
        queue.push(queue.pop());
        queue_gui.push(queue_gui.pop());
    }

    int skip;
    cout << "Enter the count you want to skip before killing: ";
    cin >> skip;
    while (skip < 0)
    {
        cout << "Error: Enter a Positive Number!" << endl;
        cin >> skip;
    }

    /**
     * now using this data to perform the josephus problem
     * if we have 5 members
     * for skip = 0, we kill 1 2 3 4 in that order
     * for skip = 1, we kill 2 4 1 5 in that order
     */
    Josephus_Queue<int> queue_kill_order;
    int count = 0;
    while (queue.get_size() > 1)
    {
        int data = queue.pop();
        count++;
        if (count == skip + 1)
        {
            count = 0;
            cout << data << " ";
            queue_kill_order.push(data);
        }
        else
        {
            queue.push(data);
        }
    }
    cout << endl;
    int winner_id = queue.pop();
    cout << "The last member to survive is: " << winner_id << endl;

    RenderWindow window(VideoMode(1300, 900), "Josephus Problem", Style::Titlebar | Style::Close);
    // placing window in the middle of the screen
    window.setPosition(Vector2i((VideoMode::getDesktopMode().width / 2) - (window.getSize().x / 2),
                                (VideoMode::getDesktopMode().height / 2) - (window.getSize().y / 2) - 45));

    // framerate is 60
    window.setFramerateLimit(60);

    // Setting background
    Texture background;
    background.loadFromFile("Resources/Background.png");
    Sprite background_sprite(background);

    // Setting texture for Person
    Texture person;
    person.loadFromFile("Resources/Person.png");
    Sprite person_sprite(person);
    person_sprite.setScale(0.2f, 0.2f);

    // Setting Texture for Person Dead
    Texture person_dead;
    person_dead.loadFromFile("Resources/Person_Dead.png");
    Sprite person_dead_sprite(person_dead);
    person_dead_sprite.setScale(0.25f, 0.25f);

    // load font
    Font font;
    font.loadFromFile("Resources/Font.ttf");

    // radius defining
    float circleRadius;
    if (size < 6)
    {
        circleRadius = 150.0f;
    }
    else if (size < 10)
    {
        circleRadius = 200.0f;
    }
    else if (size < 17)
    {
        circleRadius = 250.0f;
    }
    else if (size < 26)
    {
        circleRadius = 350.0f;
    }
    const Vector2f circleCenter(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    float text_radius = circleRadius + 100.f;

    // create arrow texture
    Texture arrow_texture;
    arrow_texture.loadFromFile("Resources/Arrow.png");
    Sprite arrow_sprite(arrow_texture);
    arrow_sprite.setScale(0.2f, 0.2f);

    // create a queue of people
    Josephus_Queue<Person<int>> people;
    for (int i = 1; i <= size; i++)
    {
        people.push(Person<int>(i));
    }

    // start from the given number
    for (int i = 1; i < start; i++)
    {
        people.push(people.pop());
    }

    bool winner = false;

    int *already_killed = new int[queue_kill_order.get_size()];
    // putting -1 in each index
    for (int i = 0; i < queue_kill_order.get_size(); i++)
    {
        already_killed[i] = -1;
    }

    int already_killed_index = 0;
    int already_killed_size = queue_kill_order.get_size();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
        }

        window.clear();
        window.draw(background_sprite);

        // Draw people in a circle
        int numPeople = queue_gui.get_size();
        for (int i = 0; i < people.size; i++)
        {
            float angle = 2 * std::acos(-1.0) * i / numPeople;
            float x = circleCenter.x + circleRadius * cos(angle) - 60;
            float y = circleCenter.y + circleRadius * sin(angle) - 45;

            // person_dead_sprite.setPosition(x - 15, y - 10);
            person_sprite.setPosition(x, y);
            person_dead_sprite.setPosition(x, y);
            // if dead, draw dead sprite, else draw normal sprite
            if (people.value(i).alive == false)
            {
                window.draw(person_dead_sprite);
            }
            else if (people.value(i).alive == true)
            {
                window.draw(person_sprite);
            }
        }

        // Draw text in a circle
        for (int i = 0; i < numPeople; i++)
        {
            float angle = 2 * std::acos(-1.0) * i / numPeople;
            float x = circleCenter.x + text_radius * cos(angle) - 10;
            float y = circleCenter.y + text_radius * sin(angle) - 10;

            Text text;
            text.setFont(font);
            text.setString(to_string(people.value(i).id));
            text.setCharacterSize(30);
            // if alive, black, else red
            if (people.value(i).alive == true)
            {
                text.setFillColor(Color::Black);
            }
            else if (people.value(i).alive == false)
            {
                text.setFillColor(Color::Red);
            }
            // text.setFillColor(Color::Black);
            text.setPosition(x, y);
            window.draw(text);
        }

        // Draw arrow of the right of the 1st person
        float angle = 2 * std::acos(-1.0) * 0 / numPeople;
        float x = circleCenter.x + circleRadius * cos(angle) + 235;
        float y = circleCenter.y + circleRadius * sin(angle) - 10;
        arrow_sprite.setPosition(x, y);
        // rotate 90 degrees
        arrow_sprite.setRotation(90);
        window.draw(arrow_sprite);

        // if winner is true writing winner text on top left
        if (winner == true)
        {
            Text text;
            text.setFont(font);
            string winner_text = "Winner is: " + to_string(winner_id);
            text.setString(winner_text);
            text.setCharacterSize(50);
            text.setFillColor(Color::Green);
            text.setPosition(50, 50);
            window.draw(text);
        }

        window.display();

        if (queue_kill_order.get_size() > 0)
        {
            int to_kill = queue_kill_order.pop();
            // switch bool from true to false
            for (int i = 0; i < people.get_size(); i++)
            {

                int temp_id = people.pop().id;
                if (temp_id == to_kill)
                {
                    // don't recreate the complete object, just change the bool
                    Node<Person<int>> *temp_node = new Node<Person<int>>(Person<int>(temp_id, false));
                    already_killed[already_killed_index] = temp_id;
                    already_killed_index++;
                    people.push_node(temp_node);
                    // break;
                }
                else
                {
                    Node<Person<int>> *temp_node = new Node<Person<int>>(Person<int>(temp_id, true));
                    people.push_node(temp_node);
                }
            }
        }
        else if (queue_kill_order.get_size() == 0 && winner == false)
        {
            // switch bool from true to false
            for (int i = 0; i < people.get_size(); i++)
            {

                int temp_id = people.pop().id;
                if (temp_id == winner_id)
                {
                    Node<Person<int>> *temp_node = new Node<Person<int>>(Person<int>(temp_id, true));
                    people.push_node(temp_node);
                    // break;
                }
                else
                {
                    Node<Person<int>> *temp_node = new Node<Person<int>>(Person<int>(temp_id, false));
                    people.push_node(temp_node);
                }
            }
            winner = true;
        }

        for (int j = 0; j < people.get_size(); j++)
        {
            int temp_id_people;
            bool temp_alive_people;
            temp_id_people = people.front().id;
            temp_alive_people = people.front().alive;
            people.pop();
            bool flag = false;
            for (int k = 0; k < already_killed_size; k++)
            {
                if (temp_id_people == already_killed[k])
                {
                    flag = true;
                    break;
                }
            }
            if (flag == false)
            {
                people.push(Person<int>(temp_id_people, true));
            }
            else if (flag == true)
            {
                people.push(Person<int>(temp_id_people, false));
            }
        }
        // sleep for 2 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    system("pause");
    return 0;
}