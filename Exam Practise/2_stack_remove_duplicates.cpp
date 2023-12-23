#include <iostream>
#include <stack>
#include <string>
using namespace std;

string removePairs(string input)
{
    stack<char> stack1;
    stack<char> stack2;
    for (int i = 0; i < input.length(); ++i)
    {
        stack1.push(input[i]);
    }
    char topOfStack2 = '\0';
    while (!stack1.empty())
    {
        char C = stack1.top();
        stack1.pop();
        while (!stack1.empty() && stack1.top() != C)
        {
            stack2.push(stack1.top());
            stack1.pop();
        }
        bool matched = false;
        if (!stack1.empty())
        {
            matched = true;
            stack1.pop();
        }
        while (!stack2.empty() && stack2.top() != topOfStack2)
        {
            stack1.push(stack2.top());
            stack2.pop();
        }
        if (!matched)
        {
            stack2.push(C);
            topOfStack2 = C;
        }
    }
    string result;
    while (!stack2.empty())
    {
        char C = stack2.top();
        stack2.pop();
        result.push_back(C);
    }
    return result;
}

int main()
{
    cout << removePairs("assassin") << endl;
    cout << removePairs("an assassin sins") << endl;
    cout << removePairs("pacific ocean") << endl;
    return 0;
}