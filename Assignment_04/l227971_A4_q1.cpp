#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

int main()
{
    int count_link_val = 1;
    string filename; // store the file name
    string line;     // store each line of the file
    cout << "Enter the file name (.txt): \n> ";
    getline(cin, filename);
    while (filename.length() == 0 || filename.find(".txt") == string::npos || filename.find(" ") != string::npos)
    {
        cout << "\nError, Please Enter Valid Filename.\n"
             << endl;
        cout << "Enter the file name (.txt): \n> ";
        getline(cin, filename);
    }
    int count_empty_line = 0; // if file has 2 empty lines, then it is the end of the file

    ifstream file(filename.c_str());
    if (!file)
    {
        cout << "\nError opening file.\n"
             << endl;
        system("pause");
        return 0;
    }

    string prev_link = ""; // store the previous link

    string word_to_search; // store the word to search
    cout << "\nEnter the word to search: \n> ";
    getline(cin, word_to_search);

    while (word_to_search.length() == 0 || word_to_search.find(" ") != string::npos) // if it has size 0 or has a space it it
    {
        cout << "\nEnter a Single Valid Word.\n"
             << endl;
        cout << "Enter the word to search: \n> ";
        getline(cin, word_to_search);
    }

    cout << endl;

    while (getline(file, line))
    {
        if (line.length() == 0) // if line is empty
        {
            count_empty_line++;
            if (count_empty_line == 2) // if file has 2 empty lines, then it is the end of the file
            {
                break; // break the loop
            }
        }
        else
        {
            count_empty_line = 0;
        }

        if (line.length() > 0) // if the line is not empty
        {
            if (line.find("http://www.") != string::npos && line.find(".html") != string::npos) // Is a Link Line
            {
                string new_link = line.substr(line.find("http://www."), line.find(".html") + 5 - line.find("http://www.")); // get the link

                if (prev_link != new_link) // if the previous link is not the same as the current link
                {
                    prev_link = new_link; // store the current link as the previous link
                }
                continue;
            }
            else // Is a Word Line
            {
                // get the first word of the line
                string word = line.substr(0, line.find(" "));
                if (word == word_to_search) // if the word is the same as the word to search
                {
                    cout << count_link_val << ". " << prev_link << endl;
                    count_link_val++;
                    continue;
                }
                bool flag = false; // flag to check if the word is found
                // now doing the same for the rest of the words
                while (line.find(" ") != string::npos)
                {
                    line = line.substr(line.find(" ") + 1, line.length() - line.find(" ") - 1);
                    word = line.substr(0, line.find(" "));
                    if (word == word_to_search)
                    {
                        cout << count_link_val << ". " << prev_link << endl;
                        flag = true;
                        count_link_val++;
                        break;
                    }
                }
                if (flag == true)
                {
                    continue;
                }
            }
        }
    }
    cout << endl;

    if (count_link_val - 1 == 0)
    {
        cout << "No Links Found." << endl;
    }
    else if (count_link_val - 1 > 0)
    {
        cout << "Total Links Found: " << count_link_val - 1 << endl;
    }

    cout << endl;

    // only CLI UI was required, but i implimented loading and printed manually to test the UI,
    // but used to TREES or any other data structure

    system("pause");
    return 0;
}