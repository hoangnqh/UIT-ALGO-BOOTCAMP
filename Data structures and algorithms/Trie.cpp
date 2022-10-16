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
const int N = 1e5 + 5;

struct Trie
{
    struct node{
        /*
            sum: giá trị tổng nút
            val: giá trị tại nút
        */
        int sum, val;
        int child[256 + 5];
    };

    vector<node> tree;
    int res = 0;

    Trie() {}

    int convert(char c){
        if('a' <= c && c <= 'z') return c - 'a';
        else return c - 'A' + 'z' - 'a';
    }

    node newNode(){
        node a;
        a.sum = 0;
        a.val = 0;
        for(int i = 0; i < 100; i++)
            a.child[i] = -1;
        return a;
    }

    void newTree(){
        tree.clear();
        tree.push_back(newNode());
    }

    void addWord(string s){
        int index = 0;
        for(int i = 0; i < s.size(); i++){
            tree[index].sum++;
            int w = convert(s[i]);
            if(tree[index].child[w] == -1){
                tree.push_back(newNode());
                tree[index].child[w] = tree.size() - 1;
            }
            index = tree[index].child[w];
        }
        tree[index].sum++;
        tree[index].val++;
    }

    int countPrefix(string s){
        int index = 0;
        for(int i = 0; i < s.size(); i++){
            int w = convert(s[i]);
            if(tree[index].child[w] == -1) return 0;
            index = tree[index].child[w];
        }
        return tree[index].sum;
    }

    int countWord(string s){
        int index = 0;
        for(int  i = 0; i < s.size(); i++){
            int w = convert(s[i]);
            if(tree[index].child[w] == -1) return 0;
            index = tree[index].child[w];
        }
        return tree[index].val;
    }

    void deleteWord(string s){
        if(countPrefix(s) == 0) return;
        int index = 0;
        for(int i = 0; i < s.size(); i++){
            tree[index].sum--;
            int w = convert(s[i]);
            index = tree[index].child[w];
        }
        tree[index].sum--;
        tree[index].val--;
    }

    void get(int index, int ans){
        for(int i = 0; i < 26; i++){
            if(tree[index].child[i] == -1) res = max(res, ans + tree[index].val);
            else{
                get(tree[index].child[i], ans + tree[index].val);
            }
        }
    }

    void answer(){
        get(0, 0);
        cout << res;
    }
};

int n;
string s;


int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    Trie tree;
    tree.newTree();
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> s;
        tree.addWord(s);
    }
    tree.answer();
}

