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

/// 4 directions
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

/// Default long long max => 1e18
const int INF = 1e18;

/// Default MOD => 1e9 + 7
const int MOD = 1e9 + 7;

/// Input limit
const int N = 1e5 + 5;


void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    k -= 1;
    if(m < n - 1){
        cout << "NO" << '\n';
        return;
    }
    int x = n - k - 1;
    int sum = (x - 1) * (x) / 2 + 2 * x + k;
    if(k == 2){
        sum += x;
    }
    //cout << sum << endl;
    if(m > sum){
        cout << "YES" << '\n';
    }
    else{
        cout << "NO" << '\n';
    }


}

int32_t main(){
	//freopen("C:\\Users\\nqhho\\Desktop\\CP\\test.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(0);
	int T = 1;
	cin >> T;
	while(T--){solve();}
}
