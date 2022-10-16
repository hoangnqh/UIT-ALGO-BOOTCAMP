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
const int N = 1e5 + 5;

struct Graham{
    int n;
    int pos = 0;
    vector<pair<int, int> > a;
    pair<int, int> origin;

    Graham(){}
    Graham(int n): n(n), a(n + 5){}

    void addPoint(int u, int v){
        pos += 1;
        a[pos] = make_pair(u, v);
    }

    bool ccw(pair<int, int> O, pair<int, int> A, pair<int, int> B) {
        A.first -= O.first, A.second -= O.second;
        B.first -= O.first, B.second -= O.second;
        return 1ll * A.first * B.second > 1ll * A.second * B.first;
    }

    void process(){
        sort(a.begin() + 1, a.begin() + n + 1);
        origin = a[1];
        sort(a.begin() + 2, a.begin() + n + 1, [&](pair<int, int> A, pair<int, int> B){
             return ccw(origin, A, B);
            });
        a[0] = a[n];
        a[n + 1] = a[1];
        int j = 1;
        for (int i = 1; i <= n + 1; i++) {
            while (j > 2 && !ccw(a[j - 2], a[j - 1], a[i])) j--;
            a[j++] = a[i];
        }
        n = j - 2;

        cout << n << '\n';
        for(int i = 1; i <= n; i++){
            cout << a[i].first << " " << a[i].second << '\n';
        }
    }
};


int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    Graham g(n);
    for(int i = 1; i <= n; i++){
        int x, y;
        cin >> x >> y;
        g.addPoint(x, y);
    }
    g.process();
}
