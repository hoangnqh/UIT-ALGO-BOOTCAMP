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
    vector<vector<II> > d;
    vector<int> h;
    LCA(){}
    LCA(int n){
        this->n = n;
        a = vector<vector<II> > (n + 5);
        h = vector<int> (n + 5, 0);
        k = log2(n);
        p = vector<vector<int> > (n + 5, vector<int> (k + 1, -1));
        d = vector<vector<II> > (n + 5, vector<II> (k + 1, mp(INF, -INF)));
    }
    void addEdge(int u, int v, int w){
        a[u].push_back(make_pair(w, v));
        a[v].push_back(make_pair(w, u));
    }
    void dfs(int u, int par, int W, int height){
        p[u][0] = par;
        h[u] = height;
        d[u][0] = mp(W, W);
        for(auto [w, v]: a[u]){
            if(v == par) continue;
            dfs(v, u, w, height + 1);
        }
    }
    inline II optimize(II a, II b){
        return make_pair(min(a.fi, b.fi), max(a.se, b.se));
    }
    void build(){
        dfs(1, 1, 0, 0);
        for(int t = 1; t <= k; t++){
            for(int u = 1; u <= n; u++){
                if(p[u][t - 1] == -1) continue;
                p[u][t] = p[p[u][t - 1]][t - 1];
                d[u][t] = optimize(d[u][t - 1], d[p[u][t - 1]][t - 1]);
            }
        }
    }
    II getLCA(int u, int v){
        II res = mp(INF, -INF);
        // goi h[u] la nut xa hon
        if(h[u] < h[v]) swap(u, v);

        int diff = h[u] - h[v];
        // tim to tien u' cua u sao cho h[u'] = h[v]
        int t = k;
        for(int i = 0; i <= k; i++){
            if(diff >> i & 1){
                res = optimize(res, d[u][i]);
                u = p[u][i];
            }
        }

        if(u == v) return res;

        // tinh LCA
        for(int i = t; i >= 0; i--){
            if(p[u][i] != p[v][i]){
                res = optimize(res, d[u][i]);
                res = optimize(res, d[v][i]);
                u = p[u][i];
                v = p[v][i];
            }
        }
        res = optimize(res, d[u][0]);
        res = optimize(res, d[v][0]);
        return res;
    }



    /// https://oj.vnoi.info/problem/lubenica

    void get(int u, int v){
        II res = getLCA(u, v);
        cout << res.fi << " " << res.se << '\n';
    }
};



void solve(){
    int n;
    cin >> n;
    LCA g(n);
    for(int i = 1; i < n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    g.build();
    int q;
    cin >> q;
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
