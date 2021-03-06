/* POJ 3017 Cut the Sequence
 * 单调队列减少决策数量
 * */
#include <cstdio>
#include <string>
#include <set>
using namespace std;

typedef long long int64;

const int MAXN = 100005;

int64 a[MAXN];
int64 f[MAXN];
int d[MAXN];
int q[MAXN];

template <class T>
void check_min(T &a, const T b) {
	if (a > b) a = b;
}

int main() {
	int n;
	int64 m;
	while (EOF != scanf("%d%lld", &n, &m)) {
		a[0] = 0;
		bool can = true;
		for (int i = 1, t; i <= n; ++i) {
			scanf("%d", &t);
			a[i] = t;
			if (t > m) can = false;
		}
		if (!can) {
			puts("-1");
			continue;
		}
		int fr = 0, re = 0, low = 0;
		f[0] = 0;
		int64 sum = 0;
		multiset<int64> ms;
		for (int i = 1; i <= n; ++i) {
			sum += a[i];
			while (sum > m) {
				sum -= a[++low];
			}
			while (fr < re && q[fr] < low) {
				ms.erase(f[d[fr]] + a[q[fr]]);
				++fr;
			}
			while (fr < re && a[q[re-1]] <= a[i]) {
				ms.erase(f[d[re-1]] + a[q[re-1]]);
				--re;
			}
			if (fr < re) {
				d[re] = q[re-1];
			} else {
				d[re] = low;
			}
			q[re++] = i;
			ms.insert(f[d[re-1]] + a[q[re-1]]);
			if (d[fr] < low) {
				ms.erase(f[d[fr]] + a[q[fr]]);
				d[fr] = low;
				ms.insert(f[d[fr]] + a[q[fr]]);
			}
			/*
			f[i] = f[d[fr]] + a[q[fr]];
			for (int j = erasefr + 1; j < re; ++j) {
				check_min(f[i], f[d[j]] + a[q[j]]);
			}
			*/
			f[i] = *ms.begin();
		}
		printf("%lld\n", f[n]);
	}
	return 0;
}
