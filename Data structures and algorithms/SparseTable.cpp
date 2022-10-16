#include<bits/stdc++.h>
using namespace std;

struct SparseTable{
    int n;
    vector<int> a;
    vector<vector<int> > st;
    int K; // K = log2(n)
    SparseTable(){}
    SparseTable(int n){
        this-> n = n;
        K = log2(n) + 3;
        a = vector<int> (n + 5, 0);
        st = vector<vector<int> > (n + 5, vector<int> (K, 1e9)); // min(l, r)
    }
    void build(){
        for(int i = 1; i <= n; i++){
            st[i][0] = a[i];
        }
        for(int t = 1; t < K; t++){
            for(int i = 1; i <= n; i++){
                if(i + (1 << (t - 1)) > n) break;
                st[i][t] = min(st[i][t - 1], st[i + (1 << (t - 1))][t - 1]);
            }
        }
    }
    int query(int l, int r){
        int t = log2(r - l + 1);
        return min(st[l][t], st[r - (1 << t) + 1][t]);
    }
};

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    SparseTable table(n);
    for(int i = 1; i <= n; i++){
        cin >> table.a[i];
    }
    table.build();

    int m;
    cin >> m;
    for(int i = 1; i <= m; i++){
        int l, r;
        cin >> l >> r;
        cout << table.query(l, r) << '\n';
    }
}
/*
5
4 2 1 5 3
5
1 2
1 1
2 3
2 4
3 5
*/
