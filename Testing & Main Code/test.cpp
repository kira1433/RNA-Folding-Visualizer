#include <string>
#include <queue>
#include <iostream>
#include <cstring>
#include <chrono>
using namespace std;

//RNA FOLDING ALGORITHM

int dp[5001][5001];
int mp[5001][5001];

string rna_folding(string s){
    int n = s.size();
    memset(dp,0,sizeof(dp));
    memset(mp,0,sizeof(mp));

    auto is_pairing = [&](char a,char b){
        return a=='A' && b=='U' || a=='U' && b=='A' || a=='C' && b=='G' || a=='G' && b=='C';
    };

    for(int k=5;k<=n-1;k++){
        for(int i=1;i<=n-k;i++){
            int j = i+k;
            dp[i][j] = dp[i][j-1]; 

            for(int t=i;t<=j-5;t++){
                if(is_pairing(s[t-1],s[j-1]) && dp[i][j] < 1 + dp[i][t-1] + dp[t+1][j-1])
                {
                    dp[i][j] = 1 + dp[i][t-1] + dp[t+1][j-1];
                    mp[i][j] = t;
                }
            }
        }
    }

    queue<pair<int,int>> q;
    q.push({1,n});

    string t = string(n,'.');
    while(!q.empty()){
        auto [i,j] = q.front();
        q.pop();
        if(i>j) continue;
        if(mp[i][j]){
            t[mp[i][j]-1] = '(';
            t[j-1] = ')';
            q.push({i,mp[i][j]-1});
            q.push({mp[i][j]+1,j-1});
        }
        else q.push({i,j-1});
    }

    return t;
}

int main(){
    string s;
    cin >> s;

    /*Time calculation*/
    // auto start = chrono::high_resolution_clock::now();
    string result = rna_folding(s);
    // auto stop = chrono::high_resolution_clock::now();
    // auto duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    // cout << "Time taken: " << duration << endl;

    cout << result << endl;
}