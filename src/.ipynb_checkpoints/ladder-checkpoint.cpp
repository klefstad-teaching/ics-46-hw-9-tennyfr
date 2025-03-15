#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>
#include <string>

using namespace std;

vector<string> ladder;
set<string> word_list;
string start_word;
string end_word;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    const int len1 = str1.length();
    const int len2 = str2.length();
    
    if (abs(len1 - len2) > d) return false;
    
    int i = 0, j = 0, diffs = 0;
    while (i < len1 && j < len2 && diffs <= d) {
        if (str1[i] != str2[j]) {
            diffs++;
            if (len1 > len2) i++;
            else if (len2 > len1) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    diffs += (len1 - i) + (len2 - j);
    return diffs <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> q;
    set<string> visited;
    
    if (word_list.find(end_word) == word_list.end()) return {};
    
    q.push({begin_word});
    visited.insert(begin_word);
    
    while (!q.empty()) {
        vector<string> current_ladder = q.front();
        q.pop();
        string last_word = current_ladder.back();
        
        for (const string& word : word_list) {
            if (!is_adjacent(last_word, word)) continue;
            if (visited.find(word) != visited.end()) continue;
            
            vector<string> new_ladder = current_ladder;
            new_ladder.push_back(word);
            
            if (word == end_word) return new_ladder;
            
            visited.insert(word);
            q.push(new_ladder);
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream fin(file_name);
    if (!fin) {
        cerr << "Error: Cannot open " << file_name << endl;
        exit(1);
    }
    
    string word;
    while (fin >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
    fin.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << " ";
    }
    cout << endl;
}

void verify_word_ladder() {
    if (ladder.empty()) return;
    
    bool valid = true;
    if ((ladder[0] != start_word) || (ladder.back() != end_word)) {
        cerr << "Invalid ladder" << endl;
        valid = false;
    }
    for (size_t i = 1; i < ladder.size(); ++i) {
        if (!word_list.count(ladder[i])) {
            cerr << "Word does not exist: " << ladder[i] << endl;
            valid = false;
        }
        if (!is_adjacent(ladder[i-1], ladder[i])) {
            cerr << "Not adjacent: " << ladder[i-1] << " -> " << ladder[i] << endl;
            valid = false;
        }
    }
    if (valid)
        cout << "Ladder validation successful" << endl;
}