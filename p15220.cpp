#include <iostream>
using namespace std;
#define MAXN 15
int a[MAXN][MAXN];
int v[MAXN][MAXN];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int ans = 0;
int R , C;
void dfs(int r , int c , int used , int len){
	ans = max(ans, len);
	// 枚举上下左右四个方向
	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (nr < 0 || nr >= R ||
			nc < 0 || nc >= C)
			continue;
		if (v[nr][nc] == 1){
			continue;
		}
		
		// 3. 海拔相同不能走（新增）
		if (a[nr][nc] == a[r][c]) {
			continue;
		}
		int newUsed = used;	
		// 判断是否上坡
		if (a[nr][nc] > a[r][c]) {
			if(newUsed){
				continue;
			}
			newUsed = 1;
		}
		// 标记已经经过
		v[nr][nc] = 1;
		dfs(nr,nc,newUsed,len+1);
		v[nr][nc] = 0;
	}
	
}


int main(){
	
	cin >> R >> C;
	for(int r =0 ;r < R; r++ ){
		for(int c =0 ;c < C ; c++){
			cin >> a[r][c];
		}
	}
	for(int r =0 ;r < R; r++ ){
		for(int c =0 ;c < C ; c++){
			v[r][c] = 1;
			dfs(r ,c, 0 , 1);
			v[r][c] = 0;
		}
	}
	cout << ans;
	
	
	return 0;
}



