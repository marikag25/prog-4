#include <bits/stdc++.h>
using namespace std;

string process(const string& word) {
    string p;
    for (char c : word) {
        if (isalpha(c)) {
            p += tolower(c);
        }
    }
    return p;
}

struct Node {
    string key;
    bool end;
    vector<Node*> children;

    Node(const string& k = "")
        : key(k), end(false), children(26, nullptr) {}

    ~Node() {
        for (Node* child : children) {
            delete child;
        }
    }
};

class Trie {
private:
    Node* root;

    int get_index(char c) const {
        return c - 'a';
    }

    int common_prefix_length(const string& s1, const string& s2) const {
        int i = 0;
        while (i < s1.length() && i < s2.length() && s1[i] == s2[i]) {
            i++;
        }
        return i;
    }

public:
    Trie() {
        root = new Node();
    }

    ~Trie() {
        delete root;
    }

    void insert(const string& word) {
        string p = process(word);
        if (p.empty()) return;

        Node* current = root;
        string suffix = p;

        while (!suffix.empty()) {
            int index = get_index(suffix[0]);
            Node* next_node = current->children[index];

            if (next_node == nullptr) {
                current->children[index] = new Node(suffix);
                current->children[index]->end = true;
                return;
            }

            int prefix_len = common_prefix_length(suffix, next_node->key);

            if (prefix_len == next_node->key.length()) {
                suffix = suffix.substr(prefix_len);
                current = next_node;
            }
            else {
                string common_prefix = next_node->key.substr(0, prefix_len);
                Node* split_node = new Node(common_prefix);
               
                string old_node_suffix = next_node->key.substr(prefix_len);
                int old_node_index = get_index(old_node_suffix[0]);
                next_node->key = old_node_suffix;
                split_node->children[old_node_index] = next_node;
               
                string new_node_suffix = suffix.substr(prefix_len);
               
                if (new_node_suffix.empty()) {
                    split_node->end = true;
                } 
                else {
                    int new_node_index = get_index(new_node_suffix[0]);
                    Node* n = new Node(new_node_suffix);
                    n->end = true;
                    split_node->children[new_node_index] = n;
                }

                current->children[index] = split_node;
                return;
            }
        }

        current->end = true;
    }

   
    bool search(const string& word) const {
        string p = process(word);
        if (p.empty()) return false;

        Node* current = root;
        string suffix = p;

        while (!suffix.empty()) {
            int index = get_index(suffix[0]);
            Node* next_node = current->children[index];

            if (next_node == nullptr) {
                return false;
            }

            int prefix_len = common_prefix_length(suffix, next_node->key);

            if (prefix_len < suffix.length() && prefix_len < next_node->key.length()) {
                return false;
            }

            if (prefix_len == next_node->key.length()) {
                suffix = suffix.substr(prefix_len);
                current = next_node;
            } else if (prefix_len == suffix.length()) {
                return true;
            } else {
                 return false;
            }
        }
       
        return current->end;
    }
};


int main() {
    Trie trie;
    ifstream file("word_list.txt");
    int count = 0;

    if (!file.is_open()) {
        cout << "Error" << endl;
       
         
    } else {
        string word;
       
       
        while (getline(file, word)) {
            trie.insert(word);
            count++;
        }
        file.close();

       
    }

    cout << trie.search("the") << endl;
    cout << trie.search("insert") << endl;
    cout << trie.search("aaa") << endl;
    cout << trie.search("mark") << endl;
    cout << trie.search("treE") << endl;
    cout << trie.search("TRIE") << endl;

    return 0;
}