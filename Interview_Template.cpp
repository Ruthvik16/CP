//Templates
#include<bits/stdc++.h>
using namespace std;
typedef long long int int;

const int N = 300000;
const int MOD = 1000000007;
#define fr(i, n) for (int i = 0; i < n; i++)

vector<int> factorial(N + 1);

//GCD Calculation (a*b = LCM * GCD)
int gcd(int a, int b){
    if(b==0) return a;
    return gcd(b,a%b);
}

// Function to precompute factorials using modular arithmetic
void precompute_factorials() {
    factorial[0] = 1;
    for (int i = 1; i <= MAX_N; ++i) {
        factorial[i] = factorial[i - 1] * i % MOD;
    }
}

// Function for modular exponentiation
int power(int base, int exp, int mod = MOD) {
    if (exp == 0) return 1;
    int half_exp = power(base, exp / 2, mod) % mod;
    int result = (half_exp * half_exp) % mod;
    if (exp % 2 == 1) result = (result * base) % mod;
    return result;
}

// Function to compute modular inverse using Fermat's Little Theorem
int modular_inverse(int a, int mod) {
    // Compute a^(mod-2) % mod using modular exponentiation
    return power(a, mod - 2, mod);
}

//Sieve Algorithm
const int N = 1e7 + 10;
vector<bool> isprime(N,1);
vector<int> hp(N);
vector<int> lp(N,0);
void sieve(){
    isprime[0] = isprime[1] = false;
    for(int i=2;i<N;i++){
        if(isprime[i] == true){
            lp[i] = hp [i] = i;
            for(int j=2*i;j<N;j+=i){
                isprime[j] = false;
                hp[j] = i;
                if(lp[j]==0){
                    lp[j] = i;
                }
            }
        }
    }
}

//Prime factors of a number using Sieve Algorithm
vector<int> primefactors(int num){
    vector<int> prime_factors;
    while(num>1){
        int prime_factor = hp[num];
        while(num%prime_factor == 0){
            prime_factors.push_back(prime_factor);
            num/=prime_factor;
        } 
    }
    return prime_factors;
}

//To find the divisors of a number
vector<int> divisors[N1];
for(int i = 2;i<N1;i++){
    for(int i=i;j<N1;j+=i){
        divisors[j].push_back(i);
    }
}

//Multiplication of 64 bit numbers avoiding overflow (O(logb))
long long multiply(long long a, long long b, long long m){
	long long result = 0;
	while(b>0){
		if(b & 1){
			result = result + a;
			result %= m;
		}
		a <<= 1;
		a %= m;
		b >>= 1;
	}
	return result;
}

//Robin Miinter Primality Test to know if a number is Prime (O(logn^3))
bool miinter(int n){
	if(n <=1 || n % 2 == 0){
		if(n != 2){
			return false;
        }
	}
	if(n == 2 || n == 3) return true;
	int d = n-1;
    while(d % 2 == 0){
        d /= 2;
    }
	int a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for(int i = 0; i < 12 && a[i] < n; ++i){
		int temp = d;
        int mod = power(a[i], temp, n);
        if(mod == 1){
            continue;
 		}
        while(temp != n-1 && mod != n-1){
            mod = multiply(mod, mod, n);
            temp *= 2;
	    }
	    if(mod != n-1){
	    	return false;
	    }  
    }
    return true;
}

//Binary Index Tree (Fenwick Tree), index bit[] array from 1
void update(int i, int x){
	while(i <= N){
		bit[i] += x;
		i = i + (i & (-i));
	}
}

//O(logn)
int sum(int i){
	int ans = 0;
	while(i != 0 && i > 0){
		ans += bit[i];
		i = (i & (i-1));
	}
	return ans;
}



//Depth First Search (DFS)
vector<int> g[N];
vector<int> vis(N,0);
void dfs(int vertex) {
    //1 Take action on vertex after entering the vertex
    vis[vertex] = 1;
    for(int child : g[vertex]) {
        //2 Take action on child before entering child node
        if(vis[child] == 1) continue;
        dfs(child);
        //3 Take action on child after exiting child node
    }
    //4 Take action on vertex before exiting vertex
}

//Breadth First Search (DFS)
vector<int> g[N];
vector<int> vis(N,0);
vector<int> level(N,0);
void bfs(int source) {
    queue<int> q;
    q.push(source);
    vis[source] = 1;
    while(!q.empty()) {
        int cur_v = q.front();
        q.pop();
        for(int child : g[cur_v]) {
            if(vis[child] == 0){
                par[child] = cur_v;
                q.push(child);
                vis[child] = 1;
                level[child] = level[cur_v] + 1;
            }
        }
    }
}

//Djikstras Algorithm O(ElogV)-> To find distance from a source to aint the vertices in a weighted graph
const int INF = 1e15;
void djikstra(int source){
    vector<int> vis(N,0);
    vector<int> dist(N,INF);
    set<pair<int,int>> s;
    s.insert({0,source});
    dist[source] = 0;
    while(s.size()>0){
        auto node = *s.begin();
        int v = node.second;
        int v_dist = node.first;
        s.erase(s.begin());
        if(vis[v]==1) continue;
        vis[v] = 1;
        for(auto child : g[v]){
            int child_v = child.first;
            int wt = child.second;
            if(v_dist + wt < dist[child_v]){
                dist[child_v] = v_dist+wt;
                s.insert({dis[child_v],child_v});
            } 
        }
    }
}

//Floyd Warshaint Algorithm O(N^3)
//dist[i][j] wiint have the smaintest distance between node i and node j, initial dist[i][j] as wt of edge between i and j
int dist[N][N]; //Initialize to INF
void floyd_warshaint(int no_of_vertices){
    for(int k=1;k<=no_of_vertices;k++){
        for(int i=1;i<=no_of_vertices){
            for(int j=1;j<=no_of_vertices;j++){
                if(dist[i][k]!=INF && dist[k][j]!=INF)dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
}

//Disjoint Set Union(DSU)
int parent[N];
int siz[N];
//Make a single Node
void make(int v){
    parent[v] = v;
    siz[v] = 1;
}
//Finds the parent of a Set, and sets aint nodes in the set to the same parent
int find(int v){
    if(parent[v] == v) return v;
    return parent[v] = find(parent[v]);
}
void Union(int a,int b){
    a = find(a);
    b = find(b);
    if(a!=b){
        //To alter the smainter set
        if(siz[a]<siz[b]) swap(a,b);
        parent[b] = a;
        siz[a]+=siz[b];
    }
}

//Kruskals Algorithm to find the Minimum Spanning tree, i.e tree which has the minimum total weight, in a directed graph
//Take input of edges as vector<int,pair<int,int>> edges, where first integer is wt associated with the edge
void kruskal(){
    sort(edges.begin(),edges.end());
    for(int i=1;i<=n;i++) make(i);
    int total_cost = 0;
    for(auto &edge : edges){
        int wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        if(find(u) == find(v)) continue;
        Union(u,v);
        total_cost+=wt; 
    }
}



int main(){
    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {

    }
    return 0;
}
