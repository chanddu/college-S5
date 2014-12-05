#include<iostream>
#include<algorithm>

using namespace std;

static const int MOD      = 1000000007;
static const int MAX_BITS = 11;
static const int MAX_N    = 2000; 
long dp[MAX_N + 1][1 << MAX_BITS][2];

class WinterAndSnowmen{
	int recursiveSolution(int,int,int);
	public:
		int getNumber(int,int);
		int i, N, M;
};
 
int WinterAndSnowmen::recursiveSolution(int t, int z, int b)
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
            res = recursiveSolution(t-1, z, b);
            // xor number t to A:
            if (t <= N) {
                res += recursiveSolution(t-1, z ^ (t >> i), b ^ ( (t >> i) & 1 ) );
            }
            // xor number q = p+1 to B:
            if (t <= M) {
                res += recursiveSolution(t-1, z ^ (t >> i), b);
            }
        }
        res %= MOD;
        // save it
        dp[t][z][b] = res;
    }
    return (int)res;
}
 
int WinterAndSnowmen::getNumber(int N, int M)
{
    long res = 0;
    for (int i = 0; i < MAX_BITS; i++) {
        memset(dp, -1, sizeof(dp));
        this->N=N; this->M=M; this->i =i; 
        res += recursiveSolution( max(N,M), 0, 0);
    }
    return (int)(res % MOD);
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