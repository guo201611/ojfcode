#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
struct Point{
	int x;
	int y;
};

ll area(const vector<Point>& p) {
	if (p.empty()) {
		return 0;
	}
	int minX = p[0].x;
	int maxX = p[0].x;
	int minY = p[0].y;
	int maxY = p[0].y;
	for(int i = 0 ; i <p.size() ;i++ ){
		const Point& pt = p[i];
		minX = min(minX, pt.x);
		maxX = max(maxX, pt.x);
		
		minY = min(minY, pt.y);
		maxY = max(maxY, pt.y);
	}
	return 1LL * (maxX - minX) * (maxY - minY);
}


// 按横坐标从小到大排序
bool cmpX(Point A, Point B) {
	if (A.x != B.x) {
		return A.x < B.x;
	}
	
	// 横坐标相同，再按纵坐标排序
	return A.y < B.y;
}

// 按纵坐标从小到大排序
bool cmpY(Point A, Point B) {
	if (A.y != B.y) {
		return A.y < B.y;
	}
	// 纵坐标相同，再按横坐标排序
	return A.x < B.x;
}


ll solve(vector<Point>& p , int k){
	int s = static_cast<int>(p.size());
	if (s <= k) {
		return 0;
	}
	// 先考虑只使用一个矩形
	ll ans = area(p);
	// 只有一个矩形，不能继续分割
	// 或者面积已经为0，不可能更小
	if (k == 1 || ans == 0) {
		return ans;
	}
	// dir = 0：按x排序，尝试竖直分割
	// dir = 1：按y排序，尝试水平分割
	for(int dir =0 ; dir < 2 ;dir++){
		if (dir == 0) {
			sort(p.begin(), p.end(), cmpX);
		} else {
			sort(p.begin(), p.end(), cmpY);
		}
		for(int cut = 1 ; cut < s ; cut ++){
			if(dir == 0 && p[cut -1].x == p[cut].x){
				continue;
			}
			if(dir == 1 && p[cut -1].y == p[cut].y){
				continue;
			}
			vector<Point>A(p.begin() ,p.begin()+cut);
			vector<Point>B(p.begin()+cut , p.end());
			for(int t = 1 ; t < k ; t++){
				ll newAns = solve(A ,t) + solve(B , k -t);
				ans = min(ans , newAns);
			}
			
		}
	}
	return ans;
}

int main(){
	int n , k;
	cin >>n>>k;
	vector<Point> p(n);
	for(int i =0;i < n ;i ++){
		int x , y;
		cin >> x >> y;
		p[i] = {x , y};
	}
	ll ans = solve(p , k);
	cout << ans;
	return 0;
}
