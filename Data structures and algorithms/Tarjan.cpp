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
    vector<vector<int> > a;
    vector<int> num, low, pos;
    int Time = 0;

    int TPLTM = 0;
    stack<int> s;
    vector<vector<int> > g;

    Bridge(){}
    Bridge(int n, int m): n(n), m(m), a(n + 5), num(n + 5, 0), low(n + 5, 0), pos(n + 5, 0), g(n + 5){
    }

    void addEdge(int u, int v){
        a[u].push_back(v);
    }

    void visit(int u, int p){
        s.push(u);
        num[u] = low[u] = ++Time;
        for(int i = 0; i < (int)a[u].size(); i++){
            int v = a[u][i];
            if(num[v]){
                low[u] = min(low[u], num[v]);
            }
            else{
                visit(v, u);
                low[u] = min(low[u], low[v]);
            }
        }

        if (num[u] == low[u]) {  // found one
            TPLTM += 1;
            int v;
            do {
                v = s.top();
                pos[v] = TPLTM;
                g[TPLTM].push_back(v);
                s.pop();
                num[v] = low[v] = INF;  // remove v from graph
            } while (v != u);
        }
    }

    void solve(){
        for(int i = 1; i <= n; i++){
            if(num[i] == 0) visit(i, i);
        }
        cout << TPLTM << endl;
        /** New graph
        set<II> Set;
        for(int u = 1; u <= n; u++){
            for(int v: a[u]){
                if(pos[u] == pos[v]) continue;
                Set.insert(mp(pos[u], pos[v]));
            }
        }
        for(auto it: Set){
            int u = it.fi;
            int v = it.se;
            ...
        }
        */
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
