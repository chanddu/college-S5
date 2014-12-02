#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
 
using namespace std;
const int MAXN = 2100;
const long long MOD = 1000000007;
 
class WinterAndSnowmen {
public:
  int getNumber(int, int);
};
 
long long dp[MAXN][2]; //xor, first bit
long long nval[MAXN][2];
 
int WinterAndSnowmen::getNumber(int N, int M) {
  long long ans = 0;
  for (int i = 0; i < 11; i++) // first bit where dif
  {
    for (int j = 0; j < MAXN; j++)
      for (int k = 0; k < 2; k++)
        dp[j][k] = nval[j][k] = 0;
    dp[0][0] = 1;
    
    for (int j = 1; j <= max (N, M); j++)
    {
      for (int k = 0; k < MAXN; k++)
        nval[k][0] = nval[k][1] = 0;
      
      for (int k = 0; k < MAXN; k++)
        for (int l = 0; l < 2; l++)
        {
          if (j <= N)
          {
            int nl = l;
            if (j & (1 << i))
              nl = 1 - nl;
            nval[k ^ j][nl] += dp[k][l];
          }
          if (j <= M)
          {
            nval[k ^ j][l] += dp[k][l];
          }
        }
      
      for (int k = 0; k < MAXN; k++)
        for (int l = 0; l < 2; l++)
          dp[k][l] = (dp[k][l] + nval[k][l]) % MOD;
    }
    
    for (int j = 0; j < MAXN; j++)
      if (j / (1 << i) == 1)
        ans = (ans + dp[j][0]) % MOD;
  }
  return ans;
}

int main(){
	int n,m,val;
	cin>>n;
	cin>>m;
	WinterAndSnowmen was;
	val = was.getNumber(n,m);
	cout<<"Returns: "<<val<<endl;
	return 0;
}