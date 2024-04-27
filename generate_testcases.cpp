#include <bits/stdc++.h> 
#define ll long long
#define endl "\n"
#pragma GCC optimize("Ofast")
using namespace std;

void solve () {
    int n;
    cin >> n;
    string s = "";
    for (int i = 0; i < n; i+=4) {
        // Generate test cases of length divisible by 4 
        s += "AGCU";
    }
    cout << s << endl;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}