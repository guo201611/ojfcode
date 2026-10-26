#include <iostream>
using namespace std;
using ll = long long;
#define MOD  998244353
#define MAXN 1000005
ll f[MAXN];
int main(){
	ll n ;
	cin >> n;
	ll k = (n+1)/2;
	f[0] = 1;
	if (n >= 1) f[1] = 2;
	for(int i =2 ;i <=n ;i++){
		f[i] = (f[i-1]+f[i-2])%MOD;
	}
	cout<<f[k-1]*f[n-k]% MOD;
	return 0;
}
