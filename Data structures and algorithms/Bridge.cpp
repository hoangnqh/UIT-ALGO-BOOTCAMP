#include<bits/stdc++.h>
using namespace std;

#define int long long

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair<int, int> II;
typedef pair<int, II> III;

const int INF = 1e18;
const int MOD = 1e9 + 7;
const int N = 100005;

struct Bridge{
    int n, m;
    vector<vector<II> > a;
    vector<II> e;
    vector<int> num, low, cau, khop;
    int Time = 0;

    Bridge(){}
    Bridge(int n, int m): n(n), m(m), a(n + 5), num(n + 5, 0), low(n + 5, 0), cau(m + 5, 0), khop(n + 5, 0){
        e.clear();
    }

    void addEdge(int u, int v){
        e.push_back(mp(u, v));
        a[u].push_back(make_pair(v, e.size()));
        a[v].push_back(make_pair(u, e.size()));
    }

    void visit(int u, int p){
        int numChild = 0;
        num[u] = low[u] = ++Time;
        for(int i = 0; i < (int)a[u].size(); i++){
            int v = a[u][i].fi;
            int pos = a[u][i].se;
            if(v == p) continue;
            if(num[v]){
                low[u] = min(low[u], num[v]);
            }
            else{
                visit(v, u);
                numChild += 1;
                low[u] = min(low[u], low[v]);

                // Cau
                if(low[v] > num[u]){
                    cau[pos] = 1;
                }

                // Khop
                if(u == p){
                    if(numChild >= 2) khop[u] = 1;
                }
                else{
                    if(low[v] >= num[u]) khop[u] = 1;
                }
            }
        }
    }

    void solve(){
        for(int i = 1; i <= n; i++){
            if(num[i] == 0) visit(i, i);
        }
        int cntCau = 0, cntKhop = 0;
        for(int i = 1; i <= m; i++){
            if(cau[i] == 1){
                cntCau += 1;
                // cout << e[i - 1].fi << " " << e[i - 1].se << endl;
            }
        }
        for(int i = 1; i <= n; i++){
            if(khop[i] == 1){
                cntKhop += 1;
            }
        }
        cout << cntKhop << " " << cntCau << endl;
    }

};

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    Bridge g(n, m);
    for(int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    g.solve();
}
