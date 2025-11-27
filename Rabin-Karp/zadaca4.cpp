#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const long long base = 31;
    const long long mod = 1000000009;

    vector<long long> power;
    vector<long long> prefix;
    int n;

    long long getHash(int l, int r) {
        long long h = (prefix[r] - prefix[l] + mod) % mod;
        h = (h * power[n - l - 1]) % mod;
        return h;
    }

    int existsDuplicate(int d) {
        unordered_set<long long> seen;
        for (int i = 0; i + d <= n; i++) {
            long long h = getHash(i, i + d);
            if (seen.count(h))
                return i;
            seen.insert(h);
        }
        return -1;
    }

    string longestDupSubstring(string s) { 
        n = s.size();
        power.resize(n + 1);
        prefix.resize(n + 1);

        power[0] = 1;
        for (int i = 1; i <= n; i++)
            power[i] = (power[i - 1] * base) % mod;

        prefix[0] = 0;
        for (int i = 0; i < n; i++)
            prefix[i + 1] = (prefix[i] + (s[i] - 'a' + 1) * power[i]) % mod;

        int left = 1, right = n;
        int bestLen = 0, bestPos = -1;

        while (left <= right) {
            int mid = (left + right) / 2;
            int pos = existsDuplicate(mid);

            if (pos != -1) {
                bestLen = mid;
                bestPos = pos;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (bestPos == -1)
            return "";

        return s.substr(bestPos, bestLen);
    }
};

int main() {
    Solution sol;
    string s;

    cin >> s;

    string result = sol.longestDupSubstring(s);

    if (result == "")
        cout << "Nema";
    else
        cout << result << endl;

    return 0;
}
