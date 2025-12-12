#include <bits/stdc++.h>
using namespace std;

struct Node {
    bool end;
    vector<Node*> children;

    Node() : end(false), children(26, nullptr) {}

    ~Node() {
        for (Node* child : children) {
            delete child;
        }
    }
};

class Trie {
private:
    Node* root;

public:
    Trie() {
        root = new Node();
    }

    ~Trie() {
        delete root;
    }

    void insert(const string& word) {
        Node* curr = root;

        for (char c : word) {
            if (!isalpha(c)) continue;

            c = tolower(c);
            int idx = c - 'a';

            if (curr->children[idx] == nullptr)
                curr->children[idx] = new Node();

            curr = curr->children[idx];
        }

        curr->end = true;
    }

    bool search(const string& word) const {
        Node* curr = root;

        for (char c : word) {
            if (!isalpha(c)) continue;

            c = tolower(c);
            int i = c - 'a';

            if (curr->children[i] == nullptr)
                return false;

            curr = curr->children[i];
        }
        return curr->end;
    }
};

int main() {
    Trie trie;
    ifstream file("word_list.txt");

    if (!file.is_open()) {
        cout << "Error\n";
        return 1;
    }

    string w;
    int c = 0;

    while (getline(file, w)) {
        trie.insert(w);
        c++;
    }

    file.close();


    cout << trie.search("yes") << "\n";
    cout << trie.search("table") << "\n";
    cout << trie.search("abc") << "\n";
    cout << trie.search("no") << "\n";

    return 0;
}
