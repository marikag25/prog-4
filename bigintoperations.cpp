#include <bits/stdc++.h>
using namespace std;

class B_Int {
public:
    string v;

    B_Int(string s = "0") {
        v = s;
    }

    bool isLess(const B_Int& o) const {
        if (v.size() != o.v.size())
            return v.size() < o.v.size();
        return v < o.v;
    }

    B_Int operator+(const B_Int& o) const {
        string r;
        int i = v.size() - 1;
        int j = o.v.size() - 1;
        int k = 0;

        while (i >= 0 || j >= 0 || k) {
            int s = k;

            if (i >= 0) {
                s += v[i] - '0';
                i--;
            }
            if (j >= 0) {
                s += o.v[j] - '0';
                j--;
            }

            r.push_back(s % 10 + '0');
            k = s / 10;
        }

        reverse(r.begin(), r.end());
        return B_Int(r);
    }

    B_Int operator-(const B_Int& o) const {
        string r;
        int i = v.size() - 1;
        int j = o.v.size() - 1;
        int z = 0;

        while (i >= 0) {
            int s = (v[i] - '0') - z;
            i--;

            if (j >= 0) {
                s -= o.v[j] - '0';
                j--;
            }

            if (s < 0) {
                s += 10;
                z = 1;
            } else {
                z = 0;
            }

            r.push_back(s + '0');
        }

        while (r.size() > 1 && r.back() == '0')
            r.pop_back();

        reverse(r.begin(), r.end());
        return B_Int(r);
    }

    B_Int operator*(const B_Int& o) const {
        vector<int> r(v.size() + o.v.size(), 0);

        for (int i = v.size() - 1; i >= 0; i--) {
            for (int j = o.v.size() - 1; j >= 0; j--) {
                int s = (v[i] - '0') * (o.v[j] - '0');
                s += r[i + j + 1];

                r[i + j + 1] = s % 10;
                r[i + j] += s / 10;
            }
        }

        string s;
        for (int x : r) {
            if (!(s.empty() && x == 0))
                s.push_back(x + '0');
        }

        if (s.empty())
            return B_Int("0");
        return B_Int(s);
    }

    B_Int operator/(const B_Int& o) const {
        if (o.v == "0")
            return B_Int("Error");

        string r;
        string cur;

        for (char c : v) {
            cur.push_back(c);

            while (cur.size() > 1 && cur[0] == '0')
                cur.erase(0, 1);

            B_Int t(cur);
            int cnt = 0;

            while (!t.isLess(o)) {
                t = t - o;
                cnt++;
            }

            r.push_back(cnt + '0');
            cur = t.v;
        }

        size_t p = r.find_first_not_of('0');
        if (p == string::npos)
            return B_Int("0");

        return B_Int(r.substr(p));
    }
};

int main() {
    B_Int a("10000000000000000000");
    B_Int b("5000000000000000000");
    B_Int razlika = a - b;
    B_Int proizvod = a * b;
    B_Int kolicnik = a / b;

    cout << "A = " << a.v << endl;
    cout << "B = " << b.v << endl;

    cout << "A + B = " << zbir.v << endl;
    cout << "A - B = " << razlika.v << endl;
    cout << "A * B = " << proizvod.v << endl;
    cout << "A / B = " << kolicnik.v << endl;

    return 0;
}

