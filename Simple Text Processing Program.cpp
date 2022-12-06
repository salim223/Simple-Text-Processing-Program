#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool quit = false;
void intro()
{
    cout << "--------------------------------------------------------------" << endl;
    cout << "Please make your choice:" << endl;
    cout << " 0 - Exit" << endl;
    cout << " 1 - Word count" << endl;
    cout << " 2 - Find the longest word that appears the last alphabetically" << endl;
    cout << " 3 - Replace all none alphabetical characters with whitespaces and output the new text on screen" << endl;
    cout << " 4 - Output all words in order of their lengths and alphabetically" << endl;
    cout << "--------------------------------------------------------------" << endl;
}
void countWords(string filename)
{
    int count = 0;
    string word;
    ifstream input;
    input.open(filename);
    vector <string> words;

    string text;
    ofstream output("secondFile.txt");

    // Erase non_ascii characters from file and copy it in a second text file
    while (getline(input, text))
    {
        for (unsigned int i = 0; i < text.size(); i++)
        {
            if (!isascii(text.at(i)))
            {
                text.erase(i, 1);
                i--;
            }
        }
        output << text << endl;
    }
    input.close();

    ifstream input2;
    input2.open("secondFile.txt");

    // count words in second text file
    while (input2 >> word)
    {
        if (word.size() < 2 && word != "a" && word != "A" && word != "I") // a, A, I are considered single character word
        {
            continue;
        }
        else
        {
            count++;
        }
    }
    input2.close();

    cout << "The number of words in the text is " << count << endl;
}
void findlongestWord(string filename)
{
    string text;
    vector <string> words;
    string longestWord = "";
    ifstream input;
    input.open(filename);


    while (input >> text)
    {
        unsigned int last_index = text.size() - 1;
        if (!isalpha(text.at(last_index)))
        {
            text = (text).substr(0, last_index);
        }
        words.push_back(text);
    }
    for (unsigned int i = 0; i < words.size(); i++)
    {
        string temp = words[i];
        if (temp.size() > longestWord.size())
        {
            longestWord = temp;
        }
        else if (temp.size() == longestWord.size())
        {
            for (unsigned int y = 0; y < temp.size(); y++)
            {
                if (temp.at(y) > longestWord.at(y))
                {
                    longestWord = temp;
                    break;
                }
                else if (temp.at(y) < longestWord.at(y))
                {
                    longestWord = longestWord;
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    input.close();
    cout << "The longest word that appears the last alphabetically is " << longestWord << endl;
}
void replaceNoneAlphacharacters(string filename)
{
    string text;
    string text2;
    ifstream input;
    input.open(filename);
    ofstream output("newText.txt");

    // Erase non_ascii characters from file and copy it in a second text file
    while (getline(input, text))
    {
        for (unsigned int i = 0; i < text.size(); i++)
        {
            if (!isascii(text.at(i)))
            {
                text.erase(i, 1);
                i--;
            }
        }
        output << text << endl;
    }
    input.close();

    // Replace non-ascii characters with space
    ifstream input2;
    input2.open("newText.txt");
    while (getline(input2, text2))
    {
        if (text2 == "") continue;
        else
        {
            for (unsigned int i = 0; i < text2.size(); i++)
            {
                if (!isalpha(text2.at(i)))
                {
                    text2.at(i) = ' ';
                }
            }
            cout << text2 << endl;
        }
    }
    input2.close();

}
void wordsByLengthsAlphabet(string filename)
{
    string text, text2;
    vector <string> sortedWords;
    ifstream input;
    input.open(filename);
    ofstream output("secondFile.txt");
    ofstream outputFile("sorted.txt");

    // Erase non_ascii characters from file and copy it in a second text file
    while (getline(input, text))
    {
        for (unsigned int i = 0; i < text.size(); i++)
        {
            if (!isascii(text.at(i)))
            {
                text.erase(i, 1);
                i--;
            }
        }
        output << text << endl;
    }
    input.close();

    ifstream input2;
    input2.open("secondFile.txt");

    // Rearrange all words in order of their lengths and alphabetically in a vectror

    while (input2 >> text2)
    {

        if (isalpha(text2.at(0)))
        {
            unsigned int last_index = text2.size() - 1;
            if (!isalpha(text2.at(last_index)))
            {
                text2 = (text2).substr(0, last_index);
            }
            sortedWords.push_back(text2);
        }
    }
    for (unsigned int i = 0; i < sortedWords.size(); i++)
    {
        for (unsigned int y = i + 1; y < sortedWords.size(); y++)
        {
            string temp;
            if (sortedWords[i].size() > sortedWords[y].size())
            {
                temp = sortedWords[i];
                sortedWords[i] = sortedWords[y];
                sortedWords[y] = temp;
            }
            else if (sortedWords[i].size() == sortedWords[y].size())
            {
                for (unsigned int z = 0; z < sortedWords[i].size(); z++)
                {
                    string word1 = sortedWords[i];
                    string word2 = sortedWords[y];
                    if (word1.at(z) > word2.at(z))
                    {
                        temp = sortedWords[i];
                        sortedWords[i] = sortedWords[y];
                        sortedWords[y] = temp;
                        break;
                    }
                    else if (word1.at(z) < word2.at(z))
                    {
                        sortedWords[i] = sortedWords[i];
                        sortedWords[y] = sortedWords[y];
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }

    // Output all words in order of their lengths and alphabetically
    for (unsigned int i = 0; i < sortedWords.size(); i++)
    {
        if ((sortedWords[i]).at((sortedWords[i]).size() - 1) == '.')
        {
            sortedWords[i] = (sortedWords[i]).substr(0, (sortedWords[i]).size() - 1);
        }
        outputFile << sortedWords[i] << endl;
    }
}
int main()
{
    string filename;
    cin >> filename;
    int choice;
    ifstream input;
    input.open(filename);

    if (!input.is_open())
    {
        cout << "File not found!" << endl;
        quit = true;
    }

    else
    {
        intro();
        cin >> choice;

        // In case user uses wrong choice
        while ((choice != 0) && (choice != 1) && (choice != 2) && (choice != 3) && (choice != 4))
        {
            cout << "Please only enter 0, 1, 2, 3, or 4!" << endl;
            cin >> choice;
        }

        // diferrent cases
        while (choice != 0)
        {
            switch (choice)
            {
            case 1:
                countWords(filename);
                break;
            case 2:
                findlongestWord(filename);
                break;
            case 3:
                replaceNoneAlphacharacters(filename);
                break;
            case 4:
                wordsByLengthsAlphabet(filename);
                break;
            }
            if (quit == true)
            {
                break;
            }
            else
            {
                intro();
                cin >> choice;
                while ((choice != 0) && (choice != 1) && (choice != 2) && (choice != 3) && (choice != 4))
                {
                    cout << "Please only enter 0, 1, 2, 3, or 4!" << endl;
                    intro();
                    cin >> choice;
                }
            }
        }
    }
}
