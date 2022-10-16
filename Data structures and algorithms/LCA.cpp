#include<bits/stdc++.h>
using namespace std;

#define int long long

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define ld long double

typedef pair<int, int> II;
typedef pair<int, II> III;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

const int INF = 1e18;
const int MOD = 1e9 + 7;

const int N = 1e5 + 5;

struct LCA{
    int n, k;
    vector<vector<II> > a;
    vector<vector<int> > p;
    vector<int> h, d;
    LCA(){}
    LCA(int n){
        this->n = n;
        a = vector<vector<II> > (n + 5);
        h = vector<int> (n + 5, 0);
        d = vector<int> (n + 5, 0);
        k = log2(n);
        p = vector<vector<int> > (n + 5, vector<int> (k + 1, -1));
    }
    void addEdge(int u, int v, int w){
        a[u].push_back(make_pair(w, v));
        a[v].push_back(make_pair(w, u));
    }
    void dfs(int u, int par, int W, int height){
        p[u][0] = par;
        h[u] = height;
        d[u] = d[par] + W;
        for(auto [w, v]: a[u]){
            if(v == par) continue;
            dfs(v, u, w, height + 1);
        }
    }
    void build(){
        dfs(1, 1, 0, 0);
        for(int t = 1; t <= k; t++){
            for(int u = 1; u <= n; u++){
                if(p[u][t - 1] == -1) continue;
                p[u][t] = p[p[u][t - 1]][t - 1];
            }
        }
    }
    int getLCA(int u, int v){
        // goi h[u] la nut xa hon
        if(h[u] < h[v]) swap(u, v);

        // tim to tien u' cua u sao cho h[u'] = h[v]
        int t = log2(h[u]);
        for(int i = t; i >= 0; i--){
            if(h[u] - (1 << i) >= h[v]){
                u = p[u][i];
            }
        }

        if(u == v) return u;

        // tinh LCA
        for(int i = t; i >= 0; i--){
            if(p[u][i] != -1 && p[u][i] != p[v][i]){
                u = p[u][i];
                v = p[v][i];
            }
        }
        return p[u][0];
    }

    /// https://oj.vnoi.info/problem/pwalk
    /// Tim do dai duong di tu u toi v
    void get(int u, int v){
        int P = getLCA(u, v);
        //cout << P << endl;
        cout << d[v] + d[u] - 2 * d[P] << '\n';
    }
};



void solve(){
    int n, q;
    cin >> n >> q;
    LCA g(n);
    for(int i = 1; i < n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    g.build();
    for(int i = 1; i <= q; i++){
        int u, v;
        cin >> u >> v;
        g.get(u, v);
    }

}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	int Test = 1;
	//cin >> Test;
	for(int i = 1; i <= Test; i++) solve();
}
