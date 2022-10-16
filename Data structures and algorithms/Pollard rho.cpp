#include <bits/stdc++.h>
#define int long long
using namespace std;

vector<int> x; // set of prime numbers
int mulMod(int a, int b, int c){
    int x = 0, y = a%c;
    while (b > 0){
        if (b & 1) x = (x+y)%c;
        y = (y*2)%c;
        b /= 2;
    }
    return x%c;
}

int Mod(int a, int b, int p){
    int res = 1;
    int x = a%p;
    while (b){
        if (b & 1) res = mulMod(res, x, p);
        x = mulMod(x, x, p);
        b /= 2;
    }
    return res%p;
}


bool millerTest(int d, int s, int n){
    int a = rand() % (n-4) + 2;
    int x = Mod(a, s, n);
    if (x==1 or x==n-1) return true;
    for (int r = 1; r < d; r++){
        x = mulMod(x, x, n);
        if (x==1) return false;
        if (x==n-1) return true;
    }
    return false;
}

bool isPrime(int n, int k = 20){ // use millerTest to test primes
    if (n <= 1 || n==4) return false;
    if (n<=3) return true;
    if (n%2==0) return false;
    int s = n-1, d = 0;
    while (s%2==0){
        s/=2;
        d++;
    }
    for (int i = 0; i < k; i++){
        if (millerTest(d, s, n) == false) return false;
    }
    return true;
}

int pollard_rho(int n){  //pollard rho implementation
    if(n%2==0) return 2;
    int x = rand()%n+1;
    int c = rand()%n+1;
    int y = x;
    int g = 1;
    //fn is f(x) = x*x + c
    while(g == 1){
        x = (mulMod(x, x, n) + c)%n;
        y = (mulMod(y, y, n) + c)%n;
        y = (mulMod(y, y, n) + c)%n;
        g = __gcd(abs(x-y),n);
    }
    return g;
}

void factorize(int n){   //fn to factorize the number
    if(n == 1) return;
    if(isPrime(n)){      //if n is prime,store it
        x.push_back(n);
        return;
    }
    int divisor = pollard_rho(n);   //get a divisor of n
    factorize(divisor);
    factorize(n/divisor);
}

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int tcase = 1; tcase <= tc; tcase++){
        int n;
        cin >> n;
        if (n==1){
            cout << 0 << '\n';
            continue;
        }
        factorize(n);
        sort(x.begin(), x.end());
        cout << x.size() << " ";
        for (int val: x){
            cout << val << " ";
        }
        cout << '\n';
        x.clear();
    }
}
