#include "ladder.h"

int main() {
    set<string> dictionary;
    load_words(dictionary, "words.txt");
    
    cout << "Enter start word: ";
    string start, end;
    cin >> start;
    cout << "Enter end word: ";
    cin >> end;
    
    transform(start.begin(), start.end(), start.begin(), ::tolower);
    transform(end.begin(), end.end(), end.begin(), ::tolower);
    
    if (start == end) {
        error(start, end, "Start and end words must be different");
        return 1;
    }
    if (!dictionary.count(end)) {
        error(start, end, "End word not in dictionary");
        return 1;
    }
    
    vector<string> ladder = generate_word_ladder(start, end, dictionary);
    print_word_ladder(ladder);
    verify_word_ladder(ladder, dictionary, start, end);
    
    return 0;
}