#include <iostream>
#include <algorithm>
using namespace std;
using  ll = long long ;
#define MAXN 100005
ll a[MAXN];
int main(){
	int n;
	cin >> n;
	for(int i =0; i< n; i++){
		cin >> a[i];
	}
	sort(a , a + n);
	int i = 0;

	int m =0;
	if(n %2 == 0){
		int j = n -1;
		while(i < j){
			if(m < a[i] + a[j]){
				m = a[i] + a[j];
			}
			i++;
			j--;
		}
	}
	else{
		int j = n -2;
		while(i < j){
			if(m < a[i] + a[j]){
				m = a[i] + a[j];
			}
			i++;
			j--;
		}
		if(m < a[n-1]){
			m = a[n-1];
		}
	}
	cout << m;
	return 0;
}
