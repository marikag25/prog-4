#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
    string val;

    BigInt(string s = "0") {
        val = s;
    }

    bool isLess(BigInt other) {
        if (val.length() != other.val.length()) {
            return val.length() < other.val.length();
        }
        return val < other.val;
    }

    BigInt operator+(BigInt other) {
        string res = "";
        int i = val.length() - 1, j = other.val.length() - 1, ostatok = 0;
        while (i >= 0 || j >= 0 || ostatok) {
            int v1 = 0;
            int v2 = 0;
            if (i >= 0) {
                v1 = val[i] - '0';
                i--;
            }
            if (j >= 0) {
                v2 = other.val[j] - '0';
                j--;
            }
            int sum = ostatok + v1 + v2;
            res += (char)((sum % 10) + '0');
            ostatok = sum / 10;
        }
        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    BigInt operator-(BigInt other) {
        string res = "";
        int i = val.length() - 1, j = other.val.length() - 1, zimaj = 0;
        while (i >= 0) {
            int v1 = val[i] - '0';
            i--;
            int v2 = 0;
            if (j >= 0) {
                v2 = other.val[j] - '0';
                j--;
            }
            int sub = v1 - v2 - zimaj;
            if (sub < 0) {
                sub = sub + 10;
                zimaj = 1;
            } else {
                zimaj = 0;
            }
            res += (char)(sub + '0');
        }
        while (res.length() > 1 && res.back() == '0') {
            res.pop_back();
        }
        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    BigInt operator*(BigInt other) {
        int n = val.length(), m = other.val.length();
        vector<int> res_vec(n + m, 0);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int mul = (val[i] - '0') * (other.val[j] - '0');
                int sum = mul + res_vec[i + j + 1];
                res_vec[i + j + 1] = sum % 10;
                res_vec[i + j] += sum / 10;
            }
        }
        string s = "";
        for (int x : res_vec) {
            if (s.empty() && x == 0) {
                continue;
            }
            s += (char)(x + '0');
        }
        if (s == "") {
            return BigInt("0");
        } else {
            return BigInt(s);
        }
    }

    BigInt operator/(BigInt other) {
        if (other.val == "0") return BigInt("Error");
        string res = "", currentStr = "";
        for (char c : val) {
            currentStr += c;
            while (currentStr.size() > 1 && currentStr[0] == '0') {
                currentStr.erase(0, 1);
            }
            BigInt current_bi(currentStr);
            int count = 0;
            while (!(current_bi.isLess(other))) {
                current_bi = current_bi - other;
                if (current_bi.val == "0") {
                    currentStr = "";
                } else {
                    currentStr = current_bi.val;
                }
                count++;
            }
            res += (char)(count + '0');
        }
        string final_res = "";
        bool leading_zero = true;
        for (char c : res) {
            if (leading_zero && c == '0') {
                continue;
            }
            leading_zero = false;
            final_res += c;
        }
        if (final_res == "") {
            return BigInt("0");
        } else {
            return BigInt(final_res);
        }
    }
};

struct Compare {
    bool operator()(pair<BigInt, BigInt> p1, pair<BigInt, BigInt> p2) {
        return p2.first.isLess(p1.first);
    }
};

void dijkstraBigIntPrimes(int n) {
    priority_queue<pair<BigInt, BigInt>, vector<pair<BigInt, BigInt>>, Compare> q;

    cout << "2 ";
    q.push({BigInt("4"), BigInt("2")});

    for (int i = 3; i <= n; i++) {
        BigInt current(to_string(i));

        if (current.isLess(q.top().first)) {
            cout << i << " ";
            q.push({current * current, current});
        } else {
            while (current.val == q.top().first.val) {
                pair<BigInt, BigInt> top_pair = q.top();
                q.pop();
                q.push({top_pair.first + top_pair.second, top_pair.second});
            }
        }
    }
    cout << endl;
}

int main() {
    dijkstraBigIntPrimes(50);
    return 0;
}