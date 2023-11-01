#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cctype>
using namespace std;

// Class XMLData
class XMLData
{
public:
    string tag;
    int line;

    XMLData(const string &tag, int line)
    {
        this->tag = tag;
        this->line = line;
    }

    XMLData()
    {
        this->tag = "";
        this->line = 0;
    }
};

template <typename dataType>

class Node
{
public:
    dataType data;
    Node<dataType> *next;
    Node<dataType> *prev;

    Node(dataType data)
    {
        this->data = data;
        next = NULL;
        prev = NULL;
    }
};

template <typename dataType>

class Stack
{
private:
    Node<dataType> *top;
    Node<dataType> *bottom;
    int size;

public:
    Stack()
    {
        top = NULL;
        bottom = NULL;
        size = 0;
    }

    void push(dataType data)
    {
        Node<dataType> *newNode = new Node<dataType>(data);
        if (top == NULL)
        {
            top = newNode;
            bottom = newNode;
        }
        else
        {
            newNode->next = top;
            top->prev = newNode;
            top = newNode;
        }
        size++;
    }

    void pop()
    {
        if (top == NULL)
        {
            cout << "Stack is empty" << endl;
        }
        else
        {
            Node<dataType> *temp = top;
            top = top->next;
            delete temp;
            size--;
        }
    }

    dataType top_val()
    {
        if (top == NULL)
        {
            cout << "Stack is empty" << endl;
            return XMLData();
        }
        else
        {
            return top->data;
        }
    }

    dataType peek()
    {
        if (top == NULL)
        {
            cout << "Stack is empty" << endl;
            return 0;
        }
        else
        {
            return top->data;
        }
    }

    bool isEmpty()
    {
        if (top == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int getSize()
    {
        return size;
    }
};

class Errors
{
public:
    string error;
    int line;
};

bool isValidXML(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Failed to open file: " << filename << endl;
        return false;
    }

    Stack<XMLData> tagStack;
    string line;
    int lineNumber = 0;
    bool errorFound = false;

    while (getline(file, line))
    {
        lineNumber++;
        size_t pos = 0;

        while (pos < line.length())
        {
            if (line[pos] == '<')
            {
                if (pos + 1 < line.length() && line[pos + 1] == '!')
                {
                    // Comment, find the end of the comment
                    size_t commentEnd = line.find("-->", pos);
                    if (commentEnd == string::npos)
                    {
                        cout << "Error: Unclosed comment starting at line " << lineNumber << std::endl;
                        errorFound = true;
                        break;
                    }
                    pos = commentEnd + 3;
                }
                else if (pos + 1 < line.length() && line[pos + 1] == '/')
                {
                    // Closing tag
                    size_t closingTagEnd = line.find('>', pos);
                    if (closingTagEnd == string::npos)
                    {
                        cout << "Error: Unclosed closing tag starting at line " << lineNumber << endl;
                        errorFound = true;
                        break;
                    }
                    string closingTag = line.substr(pos + 2, closingTagEnd - pos - 2);

                    if (tagStack.isEmpty() || tagStack.top_val().tag != closingTag)
                    {
                        cout << "Error: Mismatched closing tag '" << closingTag << "' at line " << lineNumber << endl;
                        errorFound = true;
                        break;
                    }

                    tagStack.pop();
                    pos = closingTagEnd + 1;
                }
                else if (pos + 1 < line.length() && line[pos + 1] == '?')
                {
                    // Header
                    size_t headerEnd = line.find("?>", pos);
                    if (headerEnd == string::npos)
                    {
                        cout << "Error: Unclosed header starting at line " << lineNumber << endl;
                        errorFound = true;
                        break;
                    }
                    string header = line.substr(pos + 2, headerEnd - pos - 2);

                    // Check if the header has a version and encoding attribute
                    size_t versionPos = header.find("version");
                    size_t encodingPos = header.find("encoding");
                    if (versionPos == string::npos || encodingPos == string::npos)
                    {
                        cout << "Error: Invalid header syntax at line " << lineNumber << endl;
                        errorFound = true;
                        break;
                    }

                    // Check if the version attribute has a value
                    size_t versionValueStart = header.find_first_of("\"'", versionPos);
                    if (versionValueStart == string::npos)
                    {
                        cout << "Error: Invalid header syntax at line " << lineNumber << endl;
                        errorFound = true;
                        break;
                    }
                    char versionQuoteChar = header[versionValueStart];
                    size_t versionValueEnd = header.find(versionQuoteChar, versionValueStart + 1);
                    if (versionValueEnd == string::npos)
                    {
                        cout << "Error: Invalid header syntax at line " << lineNumber << endl;
                        errorFound = true;
                        break;
                    }
                    string versionValue = header.substr(versionValueStart + 1, versionValueEnd - versionValueStart - 1);
                    if (versionValue.empty())
                    {
                        cout << "Error: Invalid header syntax at line " << lineNumber << endl;
                        errorFound = true;
                        break;
                    }

                    // Check if the encoding attribute has a value
                    size_t encodingValueStart = header.find_first_of("\"'", encodingPos);
                    if (encodingValueStart == string::npos)
                    {
                        cout << "Error: Invalid header syntax at line " << lineNumber << endl;
                        errorFound = true;
                        break;
                    }
                    char encodingQuoteChar = header[encodingValueStart];
                    size_t encodingValueEnd = header.find(encodingQuoteChar, encodingValueStart + 1);
                    if (encodingValueEnd == string::npos)
                    {
                        cout << "Error: Invalid header syntax at line " << lineNumber << endl;
                        errorFound = true;
                        break;
                    }
                    string encodingValue = header.substr(encodingValueStart + 1, encodingValueEnd - encodingValueStart - 1);
                    if (encodingValue.empty())
                    {
                        cout << "Error: Invalid header syntax at line " << lineNumber << endl;
                        errorFound = true;
                        break;
                    }

                    // Check if the attributes are enclosed in quotes and/or have an equal sign in them
                    size_t attributeStart = header.find_first_of("=");
                    while (attributeStart != string::npos && attributeStart < header.length())
                    {
                        // Find the opening and closing quotes
                        size_t firstQuotePos = header.find_first_of("\"'", attributeStart);
                        if (firstQuotePos == string::npos || firstQuotePos >= header.length())
                        {
                            cout << "Error: Attribute syntax error at line " << lineNumber << endl;
                            errorFound = true;
                            break;
                        }
                        char quoteChar = header[firstQuotePos];
                        size_t secondQuotePos = header.find(quoteChar, firstQuotePos + 1);
                        if (secondQuotePos == string::npos || secondQuotePos >= header.length())
                        {
                            cout << "Error: Attribute syntax error at line " << lineNumber << endl;
                            errorFound = true;
                            break;
                        }

                        // Check if the attribute has an equal sign
                        size_t equalSignPos = header.find("=", attributeStart);
                        if (equalSignPos == string::npos || equalSignPos >= header.length() || equalSignPos > secondQuotePos)
                        {
                            cout << "Error: Attribute syntax error at line " << lineNumber << endl;
                            errorFound = true;
                            break;
                        }

                        // Move to the next character after the closing quote
                        attributeStart = secondQuotePos + 1;
                    }

                    pos = headerEnd + 2;
                }
                else
                {
                    // Opening tag
                    size_t tagEnd = line.find('>', pos);
                    if (tagEnd == string::npos)
                    {
                        cout << "Error: Unclosed opening tag starting at line " << lineNumber << endl;
                        errorFound = true;
                        break;
                    }
                    string openingTag = line.substr(pos + 1, tagEnd - pos - 1);

                    // Check if the opening tag has attributes
                    size_t attributePos = openingTag.find(' ');
                    if (attributePos != string::npos)
                    {
                        openingTag = openingTag.substr(0, attributePos);
                    }

                    tagStack.push(XMLData(openingTag, lineNumber));
                    pos = tagEnd + 1;

                    // find first opening tag and closing tag
                    size_t firstOpeningTag = line.find('<');
                    size_t firstClosingTag = line.find('>');
                    bool att_flag = false;
                    // check if there is a space between the opening tag and closing tag, then an attribute exists
                    if (firstClosingTag - firstOpeningTag > 1)
                    {
                        size_t attributePos = line.find(' ', firstOpeningTag + 1);
                        if (attributePos != string::npos && attributePos < firstClosingTag)
                        {
                            att_flag = true; // attribute exists
                        }
                    }

                    // Check for syntax errors in attributes
                    size_t attributeStart = line.find(openingTag) + openingTag.length();
                    while (attributeStart < tagEnd)
                    {
                        if (att_flag == false)
                        {
                            break; // attribute doesn't exists, so no need to check for syntax errors
                        }
                        // Skip any leading spaces or tabs
                        while (attributeStart < tagEnd && (line[attributeStart] == ' ' || line[attributeStart] == '\t'))
                        {
                            attributeStart++;
                        }
                        if (attributeStart >= tagEnd)
                        {
                            break;
                        }

                        // Find the equal sign
                        size_t equalSignPos = line.find('=', attributeStart);
                        if (equalSignPos == string::npos || equalSignPos >= tagEnd)
                        {
                            cout << "Error: Attribute syntax error at line " << lineNumber << endl;
                            errorFound = true;
                            break;
                        }

                        // Find the attribute name (before the equal sign)
                        string attributeName = line.substr(attributeStart, equalSignPos - attributeStart);

                        // Find the opening and closing quotes
                        size_t firstQuotePos = line.find_first_of("\"'", equalSignPos);
                        if (firstQuotePos == string::npos || firstQuotePos >= tagEnd)
                        {
                            cout << "Error: Attribute syntax error at line " << lineNumber << endl;
                            errorFound = true;
                            break;
                        }
                        char quoteChar = line[firstQuotePos];
                        size_t secondQuotePos = line.find(quoteChar, firstQuotePos + 1);
                        if (secondQuotePos == string::npos || secondQuotePos >= tagEnd)
                        {
                            cout << "Error: Attribute syntax error (incomplete quotes) at line " << lineNumber << endl;
                            errorFound = true;
                            break;
                        }

                        // Move to the next character after the closing quote
                        attributeStart = secondQuotePos + 1;
                    }
                }
            }
            else
            {
                pos++;
            }
        }
    }

    while (!tagStack.isEmpty())
    {
        cout << "Error: Unclosed opening tag '" << tagStack.top_val().tag << "' at line " << tagStack.top_val().line << endl;
        tagStack.pop();
    }

    if (errorFound)
    {
        return false;
    }

    cout << "XML is valid." << endl;
    return true;
}

int main()
{
    isValidXML("xml_script_errors.xml");

    system("pause");
    return 0;
}