#include<bits/stdc++.h>
using namespace std;

#define int long long

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define ld long double

typedef pair<int, int> II;
typedef pair<string, II> III;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

const int INF = 1e18;
const int MOD = 1e9 + 7;
int n, m;
int a[300005], b[300005];
III test[300005];

struct Trie
{
    struct node{
        int num, val;
        int child[2];
    };

    vector<node> tree;
    int res = 0;

    Trie() {}

    node newNode(){
        node a;
        a.num = 0;
        a.val = 0;
        for(int i = 0; i < 2; i++)
            a.child[i] = -1;
        return a;
    }

    void newTree(){
        tree.clear();
        tree.push_back(newNode());
    }

    void addWord(int s){
        int index = 0;
        for(int i = 50; i >= 0; i--){
            tree[index].num++;
            int w = (s >> i) & 1;
            if(tree[index].child[w] == -1){
                tree.push_back(newNode());
                tree[index].child[w] = tree.size() - 1;
            }
            index = tree[index].child[w];
        }
        tree[index].num++;
        tree[index].val++;
    }

    void deleteWord(int s){
        int index = 0;
        for(int i = 50; i >= 0; i--){
            tree[index].num--;
            int w = s >> i & 1;
            index = tree[index].child[w];
        }
        tree[index].num--;
        tree[index].val--;
    }

    int countAnswer(int s, int Xor){
        int index = 0;
        int ans = tree[index].num;
        for(int i = 50; i >= 0; i--){
            int w = (s >> i) & 1;
            int x = (Xor >> i) & 1;
            if(x == 1){
                if(w == 1){
                    index = tree[index].child[0];
                    if(index == -1) return ans;
                }
                else{
                    if(tree[index].child[0] != -1){
                        ans -= tree[tree[index].child[0]].num;
                    }
                    index = tree[index].child[1];
                    if(index == -1) return ans;
                }
            }
            else{
                if(w == 1){
                    index = tree[index].child[1];
                    if(index == -1) return ans;
                }
                else{
                    if(tree[index].child[1] != -1){
                        ans -= tree[tree[index].child[1]].num;
                    }
                    index = tree[index].child[0];
                    if(index == -1) return ans;
                }
            }

        }
        return ans;
    }
};


void solve(){
    Trie tree;
    tree.newTree();
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    cin >> m;
    for(int i = 1; i <= m; i++){
        cin >> test[i].fi;
        if(test[i].fi.back() == 'H'){
            cin >> test[i].se.fi;
            continue;
        }
        if(test[i].fi.back() == 'T'){
            cin >> test[i].se.fi >> test[i].se.se;
        }
    }
    tree.addWord(0);
    for(int i = 1; i <= n; i++){
        b[i] = a[i] ^ b[i - 1];
        tree.addWord(b[i]);
    }
    int bd = 0;
    int Xor = 0;
    for(int i = 1; i <= m; i++){
        string s = test[i].fi;
        int u = test[i].se.fi, v = test[i].se.se;
        if(s.back() == 'P'){
            bd += 1;
            Xor ^= a[bd - 1];
            tree.deleteWord(b[bd - 1]);
        }
        if(s.back() == 'H'){
            n += 1;
            a[n] = u;
            b[n] = b[n - 1] ^ a[n];
            tree.addWord(b[n]);
        }
        if(s.back() == 'T'){
            int r = tree.countAnswer(v, Xor);
            if(u == 0){
                cout << r << '\n';
                continue;
            }
            int l = tree.countAnswer(u - 1, Xor);
            cout << r - l << '\n';
        }
    }
}

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	int Test = 1;
	//cin >> Test;
	for(int i = 1; i <= Test; i++) solve();
}
