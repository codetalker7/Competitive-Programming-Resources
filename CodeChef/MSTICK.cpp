
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: MSTICK
	 date created: 2021-05-02 18:56:41
*/
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<stack>
#include<unordered_set>
#include<cmath>
#include<numeric>
#include<iterator>
#include<set>
#include<unordered_map>
#include<map>
#include<queue>
#include<cstring>
#include<stdio.h>
#include<fstream>
#include<iomanip>
#include<functional>
#include<bitset>
#include<chrono>
#include<climits>
#include<assert.h>
using namespace std;

//type declarations
using ll = long long int;
using ull = unsigned long long int;
using vint = vector<int>;
using vll = vector<ll>;
using vch = vector<char>;
using vs = vector<string>;
using sll = set<ll>;
using msll = multiset<ll>;
using ldb = long double;

//constants
const ll MOD = 1000000007;
const ll INF = 1e18;
const int INFINT = 1e9 + 5;
const ldb PI = 3.14159265359;

//some useful algos
template <class T> T mceil(T a, T b){return (a % b == 0) ? a/b : a/b + 1;}
template <class T> T expo(T base , T exp , T mod){T res = 1;base = base % mod;while (exp > 0){if (exp & 1)res = (res*base) % mod;exp = exp>>1;base = (base*base) % mod;}return res;}
template <class T> ll maxpower(T a , T b){ll ans = 0;while(a > 0 && a % b == 0){ans++;a /= b;}return ans;}
template <class T> T extgcd(T a, T b , T &x , T &y) {x = 1, y = 0;T x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) { T q = a1 / b1; tie(x, x1) = make_tuple(x1, x - q * x1); tie(y, y1) = make_tuple(y1, y - q * y1); tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;}
template <class T> T modinv (T a , T m , T &x , T &y){T g = extgcd(a , m , x , y); if (g != 1) cerr << "Division by zero!"; else x = (x % m + m) % m; return x;}
template <class T> T signed_floor(T a , T b){if (a >= 0 && b >= 0) return a/b; else if (a < 0 & b < 0) return (-a)/(-b); else if (a < 0 & b >= 0){if (a % b == 0) return -((-a)/b); else return -((-a)/b) - 1;} else if (a >= 0 && b < 0){if(a % b == 0) return -(a/(-b)); else return -(a/(-b)) - 1;}}
template <class T> pair<T,T> log_base_2(T n){T temp = 1 , k = 0; while(temp <= n){temp <<= 1; k++;} temp >>= 1; k--; return {k , temp};}
//define global variables here

void solve(ll mcase){

}

//main function
int main(){
    //faster io
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

/*
    if there is an online judge, we use the
    standard io streams. Otherwise, we use custom
    io files.
*/
#ifndef ONLINE_JUDGE
    //works in codechef and codeforces
    FILE* inp = freopen("input.txt", "r" , stdin);
    FILE* err = freopen("error.txt", "w" , stderr);
    FILE* out = freopen("output.txt", "w" , stdout);
#endif

    //for testcases, use the below format
    /*
    ll t , mcase = 1; //testcases
    cin >> t;
    while(t > 0){
    	solve(mcase); //write a separate solve function
    	t--;
    	mcase++;
    }
    */
    ll N; cin >> N;	
    ll b[100001];
    for (ll i = 1; i <= N; i++){
    	cin >> b[i];
    }

    //making the max and min sparse tables
    vector <vll> max_sparse(N + 1);
    vector <vll> min_sparse(N + 1);

    for (ll i = 1; i <= N; i++){
    	max_sparse[i].push_back(b[i]);
    	min_sparse[i].push_back(b[i]);
    }

    for (ll j = 1; j <= 20; j++){
    	for (ll i = 1; i + (1 << j) - 1 <= N; i++){
    		//make room in the vectors
    		max_sparse[i].push_back(-1);
    		min_sparse[i].push_back(-1);

    		max_sparse[i][j] = max(max_sparse[i][j - 1] , max_sparse[i + (1 << (j - 1))][j - 1]);
    		min_sparse[i][j] = min(min_sparse[i][j - 1] , min_sparse[i + (1 << (j - 1))][j - 1]);
    	}
    }

    ll Q; cin >> Q;
    for (ll x = 1; x <= Q; x++){
    	ll L , R;
    	cin >> L >> R;
    	L++; R++;

    	pair <ll , ll> p;
    	//let m be the minimum in the range [L , R]
    	p = log_base_2(R - L + 1);
    	ll m = min(min_sparse[L][p.first] , min_sparse[R - p.second + 1][p.first]);

    	//let M be the maximum in the range [L , R]
    	ll M = max(max_sparse[L][p.first] , max_sparse[R - p.second + 1][p.first]);

    	ll M1 , M2;
    	if (1 <= L - 1){
    		p = log_base_2(L - 1);
    		M1 = max(max_sparse[1][p.first] , max_sparse[L - 1 - p.second + 1][p.first]);
    	}
    	if (R + 1 <= N){
    		p = log_base_2(N - (R + 1) + 1);
    		M2 = max(max_sparse[R + 1][p.first] , max_sparse[N- p.second + 1][p.first]);
    	}

    	float ans = ((float)(M - m))/((float)2);
    	if (1 <= L - 1)
    		ans = max(ans , (float)M1);
    	if (R + 1 <= N)
    		ans = max(ans , (float)M2);
    	printf("%.1f\n" , ans + (float)m);
    }
    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
