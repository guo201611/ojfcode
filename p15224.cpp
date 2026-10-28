#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int q;
	cin >> q;
	
	vector<int> n(q), k(q);
	vector<int> ans(q);
	
	int N = 0;
	
	for (int i = 0; i < q; i++) {
		cin >> n[i] >> k[i];
		
		// 因数不可能超过 n
		k[i] = min(k[i], n[i]);
		
		N = max(N, n[i]);
	}
	
	// 按 k 把询问分组
	vector<int> head(N + 1, -1);
	vector<int> nxt(q);
	
	for (int i = 0; i < q; i++) {
		nxt[i] = head[k[i]];
		head[k[i]] = i;
	}
	
	// cnt[x]：已经处理的因数中，
	// 有多少个能整除 x
	vector<int> cnt(N + 1, 0);
	
	// 从小到大枚举因数 d
	for (int d = 1; d <= N; d++) {
		
		// 给 d 的所有倍数增加一次计数
		for (int j = d; j <= N; j += d) {
			cnt[j]++;
		}
		
		// 回答所有 k=d 的询问
		for (int i = head[d]; i != -1; i = nxt[i]) {
			ans[i] = cnt[n[i]];
		}
	}
	
	// 按输入顺序输出
	for (int i = 0; i < q; i++) {
		cout << ans[i] << '\n';
	}
	
	return 0;
}

