#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

struct Block {
	ll sum;     // 块内石子总数
	ll cost;    // 块内前缀和的总和
	int cnt;    // 块内原始石子堆数量
	int next;   // 下一块编号
};

int n;
vector<ll> a;

vector<Block> L, R;

// 在一条旧块链的最前面，加入一堆 value 颗石子
Block build(ll value, int head, const vector<Block>& b) {
	
	// 新加入的一堆，先单独作为一个块
	Block cur = {value, value, 1, 0};
	
	while (head != 0) {
		
		// 平均值比较：
		// cur.sum / cur.cnt < b[head].sum / b[head].cnt
		//
		// 用交叉相乘避免浮点数误差
		if (cur.sum * b[head].cnt <
			b[head].sum * cur.cnt) {
			break;
		}
		
		// 平均值没有递增，把两块合并
		// cur 必须在旧块前面处理
		cur.cost += cur.sum * b[head].cnt
		+ b[head].cost;
		
		cur.sum += b[head].sum;
		cur.cnt += b[head].cnt;
		
		// 继续检查下一块
		head = b[head].next;
	}
	
	cur.next = head;
	return cur;
}

// 预处理所有位置对应的左侧、右侧块链
void prepare() {
	
	L.assign(n + 2, Block{0, 0, 0, 0});
	R.assign(n + 2, Block{0, 0, 0, 0});
	
	// L[i] 对应从 i 开始不断向左处理：
	// a[i], a[i-1], ..., a[1]
	for (int i = 1; i <= n; i++) {
		L[i] = build(a[i], i - 1, L);
	}
	
	// R[i] 对应从 i 开始不断向右处理：
	// a[i], a[i+1], ..., a[n]
	for (int i = n; i >= 1; i--) {
		int head = (i == n ? 0 : i + 1);
		
		R[i] = build(a[i], head, R);
	}
}

// 从第 start 堆开始合并的最小总费用
ll query(int start) {
	
	// 左侧从 start-1 开始
	int p = start - 1;
	
	// 右侧从 start+1 开始
	int q = (start == n ? 0 : start + 1);
	
	// 最初选中的大堆
	ll current = a[start];
	
	ll answer = 0;
	
	while (p != 0 || q != 0) {
		
		Block b;
		
		// 如果右边没有块，选左边；
		// 或者左边当前块的平均值更小，选左边
		if (q == 0 ||
			(p != 0 &&
			 L[p].sum * R[q].cnt <=
			 R[q].sum * L[p].cnt)) {
			
			b = L[p];
			p = b.next;
			
		} else {
			
			b = R[q];
			q = b.next;
		}
		
		// 一次算出处理整个块的费用
		answer += current * b.cnt + b.cost;
		
		// 当前大堆增加这个块的石子总数
		current += b.sum;
	}
	
	return answer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int l, r;
	cin >> n >> l >> r;
	
	a.resize(n + 1);
	
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	
	prepare();
	
	for (int start = l; start <= r; start++) {
		
		if (start != l) {
			cout << ' ';
		}
		
		cout << query(start);
	}
	
	cout << '\n';
	
	return 0;
}




//#include <iostream>
//#include <vector>
//#include <algorithm>  // min
//#include <climits>    // LLONG_MAX
//using namespace std;
//using ll = long long;
//const ll INF = LLONG_MAX / 4;
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(nullptr);
//	int n , l , r;
//	cin >> n >> l >> r;
//	
//	vector<ll> a(n + 1);
//	vector<ll> s(n+1 , 0);
//	for(int i =1 ;i <= n ;i ++){
//		cin >> a[i];
//		s[i] = s[i-1]+ a[i];
//	}
//
//	vector<ll> dp(n + 2, INF);
//	dp[1] = 0;
//	for(int len = n -1 ; len >= 1 ; len --){
//		// 必须从右往左更新！
//		for (int i = n - len + 1; i >= 1; i--) {
//			int j =  i + len - 1;
//			// 暂存当前区间[i,j]的新答案
//			ll best = INF;
//			if(i > 1){
//				ll cost = s[j] - s[i -2];
//				best = min(best ,
//							   cost +dp[i - 1]
//							   );
//			}
//			if (j < n) {
//				ll cost = s[j+1] - s[i -1];
//				best = min(best ,
//							   cost +dp[i]
//							   );
//			}
//			dp[i] = best;
//		}
//	}
//	// 从第start堆开始，初始区间就是[start,start]
//	for (int start = l; start <= r; start++) {
//		if (start > l) {
//			cout << ' ';
//		}
//		
//		cout << dp[start];
//	}
//	return 0;
//}



//#include <iostream>
//#include <vector>
//#include <algorithm>  // min
//#include <climits>    // LLONG_MAX
//using namespace std;
//using ll = long long;
//const ll INF = LLONG_MAX / 4;
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(nullptr);
//	int n , l , r;
//	cin >> n >> l >> r;
//	
//	vector<ll> a(n + 1);
//	vector<ll> s(n+1 , 0);
//	for(int i =1 ;i <= n ;i ++){
//		cin >> a[i];
//		s[i] = s[i-1]+ a[i];
//	}
//	// dp[i][j]：
//	// 第i～j堆已经合并，继续合并全部剩余石子的最小费用
//	vector<vector<ll>> dp(
//						  n + 1, vector<ll>(n + 1, INF)
//						  );
//	// 所有石子已经合并完，不需要再花费
//	dp[1][n] = 0;
//	for(int len = n -1 ; len >= 1 ; len --){
//		for(int i =1 ;i + len -1 <= n ;i++){
//			int j =  i + len - 1;
//			if(i > 1){
//				ll cost = s[j] - s[i -2];
//				dp[i][j] = min(dp[i][j] ,
//							   cost +dp[i-1][j]
//							   );
//			}
//			if (j < n) {
//				ll cost = s[j+1] - s[i -1];
//				dp[i][j] = min(dp[i][j] ,
//							   cost +dp[i][j+1]
//							   );
//			}
//		}
//	}
//	// 从第start堆开始，初始区间就是[start,start]
//	for (int start = l; start <= r; start++) {
//		if (start > l) {
//			cout << ' ';
//		}
//		
//		cout << dp[start][start];
//	}
//	return 0;
//}
