#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
    string val;

    BigInt(string s = "0") {
        if (s.empty()) s = "0";
        val = s;
    }

    bool isLess(BigInt other) {
        if (val.length() != other.val.length()) {
            return val.length() < other.val.length();
        }
        return val < other.val;
    }

    bool operator==(BigInt other) {
        return val == other.val;
    }

    BigInt operator+(BigInt other) {
        string res = "";
        int i = val.length() - 1, j = other.val.length() - 1, ostatok = 0;
        while (i >= 0 || j >= 0 || ostatok) {
            int v1 = (i >= 0) ? val[i--] - '0' : 0;
            int v2 = (j >= 0) ? other.val[j--] - '0' : 0;
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
            int v1 = val[i--] - '0';
            int v2 = (j >= 0) ? other.val[j--] - '0' : 0;
            int sub = v1 - v2 - zimaj;
            if (sub < 0) {
                sub += 10;
                zimaj = 1;
            } else {
                zimaj = 0;
            }
            res += (char)(sub + '0');
        }
        while (res.length() > 1 && res.back() == '0') res.pop_back();
        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    BigInt operator*(BigInt other) {
        int n = val.length(), m = other.val.length();
        vector<int> res(n + m, 0);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int mul = (val[i] - '0') * (other.val[j] - '0');
                int sum = mul + res[i + j + 1];
                res[i + j + 1] = sum % 10;
                res[i + j] += sum / 10;
            }
        }
        string s = "";
        for (int x : res) {
            if (s.empty() && x == 0) continue;
            s += (char)(x + '0');
        }
        return s.empty() ? BigInt("0") : BigInt(s);
    }

    pair<BigInt, BigInt> divmod(BigInt other) {
        if (other.val == "0") return {BigInt("Error"), BigInt("Error")};
        string res = "", currentStr = "";
        for (char c : val) {
            currentStr += c;
            while(currentStr.size() > 1 && currentStr[0] == '0') currentStr.erase(0, 1);
            BigInt current(currentStr);
            int count = 0;
            while (!(current.isLess(other))) {
                current = current - other;
                currentStr = current.val;
                count++;
            }
            res += (char)(count + '0');
        }
        
        int first = -1;
        for (int i = 0; i < (int)res.length(); i++) {
            if (res[i] != '0') {
                first = i;
                break;
            }
        }

        string q;
        if (first == -1) {
            q = "0";
        } else {
            q = res.substr(first);
        }

        string r = currentStr.empty() ? "0" : currentStr;
        return {BigInt(q), BigInt(r)};
    }

    BigInt operator/(BigInt other) { return divmod(other).first; }
    BigInt operator%(BigInt other) { return divmod(other).second; }
};

BigInt binpow(BigInt a, BigInt e, BigInt m) {
    BigInt res("1");
    a = a % m;
    while (!(e == BigInt("0"))) {
        pair<BigInt, BigInt> dm = e.divmod(BigInt("2"));
        if (!(dm.second == BigInt("0"))) {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        e = dm.first;
    }
    return res;
}

int main() {
    BigInt base("7");
    BigInt exp("15");
    BigInt mod("100");
    BigInt result = binpow(base, exp, mod);
    cout << result.val << endl;
    return 0;
}