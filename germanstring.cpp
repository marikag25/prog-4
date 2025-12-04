#include <bits/stdc++.h>
using namespace std;

class GermanString {
private:
    char* text;
    int32_t size;
    char* prefix;

    void build_prefix() {
        if (size <= 12 && text) {
            prefix = new char[5];
            for (int i = 0; i < min(4, size); i++)
                prefix[i] = text[i];
            prefix[min(4, size)] = '\0';
        }
        else {
            prefix = nullptr;
        }
    }

public:
    GermanString() {
        size = 0;
        text = nullptr;
        prefix = nullptr;
    }

    GermanString(const char* str) {
        if (!str) {
            size = 0;
            text = nullptr;
            prefix = nullptr;
            return;
        }

        size = strlen(str);
        text = new char[size + 1];

        for (int i = 0; i < size; i++)
            text[i] = str[i];
        text[size] = '\0';

        build_prefix();
    }

    GermanString(const GermanString& other) {
        size = other.size;

        if (size == 0) {
            text = nullptr;
            prefix = nullptr;
            return;
        }

        text = new char[size + 1];
        for (int i = 0; i < size; i++)
            text[i] = other.text[i];
        text[size] = '\0';

        build_prefix();
    }

    GermanString& operator=(const GermanString& other) {
        if (this == &other) return *this;

        delete[] text;
        delete[] prefix;

        size = other.size;

        if (size == 0) {
            text = nullptr;
            prefix = nullptr;
            return *this;
        }

        text = new char[size + 1];
        for (int i = 0; i < size; i++)
            text[i] = other.text[i];
        text[size] = '\0';

        build_prefix();
        return *this;
    }

    ~GermanString() {
        delete[] text;
        delete[] prefix;
    }

    int size_of() const {
        return size;
    }

    void print() const {
        if (!text) return;
        cout << text << '\n';
    }

    void empty() {
        delete[] text;
        delete[] prefix;
        text = nullptr;
        prefix = nullptr;
        size = 0;
    }

    const char& operator[](int index) const {
        return text[index];
    }

    char& operator[](int index) {
        return text[index];
    }

    int find(char c) const {
        for (int i = 0; i < size; i++) {
            if (text[i] == c)
                return i;
        }
        return -1;
    }
};

GermanString operator+(const GermanString& one, const GermanString& other) {
    int new_size = one.size_of() + other.size_of();
    char* b = new char[new_size + 1];

    for (int i = 0; i < one.size_of(); i++)
        b[i] = one[i];

    for (int i = 0; i < other.size_of(); i++)
        b[one.size_of() + i] = other[i];

    b[new_size] = '\0';

    GermanString result(b);
    delete[] b;
    return result;
}

int main() {
    char a[1000], b[1000];

    cin >> a >> b;   

    GermanString s(a);
    GermanString k(b);

    cout << s.size_of() << endl;
    s.print();

    cout << s[2] << endl;
    s[2] = 'k';
    cout << s[2] << endl;

    char f = 'a';
    cout << s.find(f) << endl;

    GermanString c = s + k;
    c.print();

    return 0;
}
