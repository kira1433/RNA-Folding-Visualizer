#include <string>
#include <cstring>
#include <queue>
#include <emscripten.h>
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

extern "C" {
    const char* EMSCRIPTEN_KEEPALIVE rna_folding_c(const char* s) {
        std::string input(s); // Convert the input C-style string to std::string
        std::string foldedSequence = rna_folding(input);
        char* result = static_cast<char*>(malloc(foldedSequence.length() + 1)); // +1 for null terminator
        // Copy the folded sequence to the allocated memory
        strcpy(result, foldedSequence.c_str());
        return result; // Return the folded sequence as a C-style string
    }
}
