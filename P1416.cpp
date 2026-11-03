#include <iostream>
#include <algorithm>
using namespace std;
#define MAXM 105
int a[MAXM][MAXM];
int dist[MAXM][MAXM][2][2];
#define INF 100000000
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int ans = INF;
int M ;
void dfs(int x , int y ,int color, int um , int cost){
	if (cost >= ans) {
		return;
	}
	if (x == M && y == M) {
		ans = cost;
		return;
	}
	if (cost >= dist[x][y][color][um]) {
		return;
	}
	
	dist[x][y][color][um] = cost;
	
	
	for (int i = 0; i < 4; i++) {
		int nr = x + dr[i];
		int nc = y + dc[i];	
		if (nr < 1 || nr >= M +1 ||
			nc < 1 || nc >= M +1 )
			continue;

		int new_cost = 0;
		int new_um = 0;
		int new_color;
		if(a[nr][nc] == 0){
			if(um == 0){
				new_cost = 2;
				new_um = 1;
				new_color = color;
			}else{
				continue;
			}
		}else{
			new_color = a[nr][nc] - 1;
			if (new_color == color) {
				new_cost = 0;
			} else {
				new_cost = 1;
			}
		}
		dfs(nr,nc,new_color ,new_um,cost + new_cost);
	}
}



int main(){
	int n ;
	cin >> M >> n;
	for(int i = 0 ;i < n ;i ++){
		int x , y , c;
		cin >> x >> y >> c;
		a[x][y] = c+1;
	}
	
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= M; j++) {
			for (int c = 0; c < 2; c++) {
				for (int u = 0; u < 2; u++) {
					dist[i][j][c][u] = INF;
				}
			}
		}
	}
	
	dfs(1,1,a[1][1] -1, 0,0);
	if (ans == INF) {
		cout << -1;
	} else {
		cout << ans;
	}
	return 0;
}
