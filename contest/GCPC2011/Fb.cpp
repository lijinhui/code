/* Diary
 * */
#include <cstdio>
#include <cstring>

char tab[26];
char str[1005];
int cnt[26];
int vlist[26];
int vlist_size, max_cnt;

int main() {
	int runs;
	scanf("%d\n", &runs);
	while (runs--) {
		while (NULL == gets(str));
		while (strlen(str) == 0) ;
		int ls = 0;
		memset(cnt, 0, sizeof(cnt));
		while (str[ls]) {
			if (str[ls] == ' ') {
				++ls;
				continue;
			}
			cnt[str[ls++] - 'A']++;
		}
		max_cnt = 0, vlist_size = 0;
		for (int i = 0; i < 26; ++i) {
			if (cnt[i] > 0) {
				if (cnt[i] == max_cnt) {
					vlist[vlist_size++] = i;
				} else if (cnt[i] > max_cnt) {
					max_cnt = cnt[i];
					vlist_size = 0;
					vlist[vlist_size++] = i;
				}
			}
		}
		if (max_cnt == 0) {
			puts("NOT POSSIBLE");
			continue;
		}
		int ans = -1;
		for (int i = 0, j; i < vlist_size; ++i) {
			int d = (vlist[i] - ('E' - 'A') + 26) % 26;
			memset(tab, 0, sizeof(tab));
			for (j = 0; j < ls; ++j) {
				if (str[j] == ' ') continue;
				int c = str[j] - 'A';
				int ct = (c - d + 26) % 26;
				if (tab[ct] == 0) {
					tab[ct] = c;
				} else if (tab[ct] != c) {
					break;
				}
			}
			if (j == ls) {
				if (ans == -1) {
					ans = d;
				} else {
					ans = -1;
					break;
				}
			}
		}
		if (ans == -1) {
			puts("NOT POSSIBLE");
		} else {
			printf("%d ", ans);
			for (int i = 0; i < ls; ++i) {
				if (str[i] == ' ') putchar(' ');
				else putchar('A' + (str[i] - 'A' - ans + 26) % 26);
			}
			puts("");
		}
	}
	return 0;
}
