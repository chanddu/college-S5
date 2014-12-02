#include<iostream>
#include<algorithm>

using namespace std;

static const int MOD      = 1000000007;
static const int MAX_BITS = 11;
static const int MAX_N    = 2000; 
long dp[MAX_N + 1][1 << MAX_BITS][2];
 
int i, N, M;
 
int rec(int t, int z, int b,int i)
{
    long res = dp[t][z][b];
    if (res == -1) {
        if (t == 0) {
            // the limit
            if ( (z == 1) && (b == 0) ) {
                res = 1;
            } else {
                res = 0;
            }
        } else {
            // xor number t to neither A or B:
            res = rec(t-1, z, b,i);
            // xor number t to A:
            if (t <= N) {
                res += rec(t-1, z ^ (t >> i), b ^ ( (t >> i) & 1 ),i );
            }
            // xor number q = p+1 to B:
            if (t <= M) {
                res += rec(t-1, z ^ (t >> i), b,i);
            }
        }
        res %= MOD;
        // save it
        dp[t][z][b] = res;
    }
    return (int)res;
}
 
int getNumber(int n, int m)
{
    long res = 0;
    for (int i = 0; i < MAX_BITS; i++) {
        // first difference will be in i-th bit
        //                             i
        //                  B  = abcdef1??????
        //                  A  = abcdef0??????
        //              A ^ B  = 0000001??????
        // (A >> i) ^ (B >> i) = 0000001
        memset(dp, -1, sizeof(dp));
        N=n; M=m; 
        res += rec( max(N,M), 0, 0,i);
    }
    return (int)(res % MOD);
}

int main(){
	int n,m,val;
	cin>>n;
	cin>>m;
	val = getNumber(n,m);
	cout<<"Returns: "<<val<<endl;
	return 0;
}