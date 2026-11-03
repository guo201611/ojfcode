#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 10005
int a[MAXN];
int main(){
	int n;
	cin >> n;
	for(int i=0 ;i < n ;i ++){
		cin >> a[i];
	}
	int ans =1;
	for(int i =0 ;i < n ;i ++){
		int j = i;
		while(a[i]== a[j] && j < n){
			j++;
		}
		ans = max(ans , j - i );
	}
	cout << ans;
}
