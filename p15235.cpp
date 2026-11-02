#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main(){
	int n , m;
	cin >> n>> m;
	vector<int> a(n + 1), last(m + 1);
	for(int i =1 ;i <= n ;i ++){
		cin >> a[i];
		last[a[i]] = i;
	}
	vector<ll> cnt(n + 2, 0), ans(m + 1, 0);
	for (int i = 1; i <= n; ++i){
		cnt[i] = 1;
	}
	for(int i = 1 ;i <= n ;i++){
		ans[a[i]] += cnt[i];
		int next = last[a[i]]+1;
		if(next <= n){
			cnt[next] += cnt[i];
		}
	}
	for(int i = 1 ;i <= m ;i++){
		if(i > 1){
			cout <<" ";
		}
		cout << ans[i];
	}
	return 0;
}
