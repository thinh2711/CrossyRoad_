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
    ifstream file("words\\" + fileName);
    if (!file.is_open())
        return "";

    string line;
    while (getline(file, line)) {
        if (!line.empty())
            vocabulary.push_back(normalize(line));
    }

    file.close();

    if (vocabulary.empty())
        return "";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, vocabulary.size() - 1);

    string word;
    do {
        word = vocabulary[dis(gen)];
    } while ((word.length() > 5 && difficult) || (word.length() < 5 && !difficult));

    return word;
}
bool contains(string word, char guess) {
    return (word.find(guess) != string::npos);
}