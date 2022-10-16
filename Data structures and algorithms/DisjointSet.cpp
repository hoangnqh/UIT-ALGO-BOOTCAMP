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

struct DJS{
    int n;
    vector<int> par;
    DJS(int n): n(n), par(n + 5, -1){}

    int finds(int u){
        return par[u] < 0 ? u : par[u] = finds(par[u]);
    }

    int join(int u, int v){
        u = finds(u);
        v = finds(v);
        if(u == v) return 0;
        if(par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return 1;
    }
};

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    vector<III> e;
    cin >> n >> m;
    DJS D(n);
    for(int i = 1; i <= m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        e.push_back(mp(w, mp(u, v)));
    }
    sort(e.begin(), e.end());
    int res = 0;
    for(auto it: e){
        int w = it.fi, u = it.se.fi, v = it.se.se;
        if(D.join(u, v)){
            res += w;
        }
    }
    cout << res;
}
