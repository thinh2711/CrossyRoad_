#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

string normalize(const string& s) {
    string news = s;
    for (char& c : news) {
        if (islower(c)) {
            c = toupper(c);
        }
    }
    return news;
}


string chooseWord(const string& fileName, int difficult) {
    vector<string> vocabulary;
    ifstream file("word/" + fileName);
    if (!file.is_open())
        {
            return " ";
        }
    while (!file.eof()) 
    {
        string line;
        getline(file, line);
        if (file && !line.empty())
            vocabulary.push_back(normalize(line));
    }

    int n = vocabulary.size();
    if (n > 0) {
        string word;
        do {
            word = vocabulary[rand() % n];
        } while ((word.length() > 5 && difficult) || (word.length() < 5 && !difficult));
        return word;
    } else {
        return " ";
    }
}

bool contain(string word, char guess) {
    if (word.find(guess) != string::npos) {
        return true;
    } else {
        return false;
    }
}