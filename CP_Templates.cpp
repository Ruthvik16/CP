//Templates
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

const int N = 300000;
const int MOD = 1000000007;
#define fr(i, n) for (ll i = 0; i < n; i++)

vector<ll> factorial(N + 1);

// Function to precompute factorials using modular arithmetic
void precompute_factorials() {
    factorial[0] = 1;
    for (int i = 1; i <= MAX_N; ++i) {
        factorial[i] = factorial[i - 1] * i % MOD;
    }
}

// Function for modular exponentiation
ll power(ll base, ll exp, ll mod = MOD) {
    if (exp == 0) return 1;
    ll half_exp = power(base, exp / 2, mod) % mod;
    ll result = (half_exp * half_exp) % mod;
    if (exp % 2 == 1) result = (result * base) % mod;
    return result;
}

// Function to compute modular inverse using Fermat's Little Theorem
ll modular_inverse(ll a, ll mod) {
    // Compute a^(mod-2) % mod using modular exponentiation
    return power(a, mod - 2, mod);
}


//Depth First Search (DFS)
vector<ll> g[N];
vector<ll> vis(N,0);
void dfs(ll vertex) {
    //1 Take action on vertex after entering the vertex
    vis[vertex] = 1;
    for(ll child : g[vertex]) {
        //2 Take action on child before entering child node
        if(vis[child] == 1) continue;
        dfs(child);
        //3 Take action on child after exiting child node
    }
    //4 Take action on vertex before exiting vertex
}

//Breadth First Search (DFS)
vector<ll> g[N];
vector<ll> vis(N,0);
vector<ll> level(N,0);
void bfs(ll source) {
    queue<ll> q;
    q.push(source);
    vis[source] = 1;
    while(!q.empty()) {
        ll cur_v = q.front();
        q.pop();
        for(ll child : g[cur_v]) {
            if(vis[child] == 0){
                par[child] = cur_v;
                q.push(child);
                vis[child] = 1;
                level[child] = level[cur_v] + 1;
            }
        }
    }
}

//Djikstras Algorithm O(NlogN)-> To find distance from a source to all the vertices in a weighted graph
const int INF = 1e15;
void djikstra(ll source){
    vector<ll> vis(N,0);
    vector<ll> dist(N,INF);
    set<pair<ll,ll>> s;
    s.insert({0,source});
    dist[source] = 0;
    while(s.size()>0){
        auto node = s.begin();
        ll v = node.second;
        ll v_dist = node.first;
        s.erase(s.begin());
        if(vis[v]==1) continue;
        for(auto child : g[v]){
            ll child_v = child.first;
            ll wt = child.second;
            if(v_dist + wt < dist[child_v]){
                dist[child_v] = v_dist+wt;
                s.insert({dis[child_v],child_v});
            } 
        }
    }
}

//Floyd Warshall Algorithm O(N^3)
//dist[i][j] will have the smallest distance between node i and node j, initial dist[i][j] as wt of edge between i and j
ll dist[N][N]; //Initialize to INF
void floyd_warshall(ll no_of_vertices){
    for(ll k=1;k<=no_of_vertices;k++){
        for(ll i=1;i<=no_of_vertices){
            for(ll j=1;j<=no_of_vertices;j++){
                if(dist[i][k]!=INF && dist[k][j]!=INF)dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
}

//Disjoint Set Union(DSU)
ll parent[N];
ll size[N];
//Make a single Node
void make(ll v){
    parent[v] = v;
    size[v] = 1;
}
//Finds the parent of a Set, and sets all nodes in the set to the same parent
ll find(ll v){
    if(parent[v] == v) return v;
    return parent[v] = find(parent[v])
}
void Union(ll a,ll b){
    a = find(a);
    b = find(b);
    if(a!=b){
        //To alter the smaller set
        if(size[a]<size[b]) swap(a,b);
        parent[b] = a;
        size[a]+=size[b];
    }
}

//Kruskals Algorithm to find the Minimum Spanning tree, i.e tree which has the minimum total weight, in a directed graph
//Take input of edges as vector<ll,pair<ll,ll>> edges, where first integer is wt associated with the edge
void kruskal(){
    sort(edges.begin(),edges.end());
    for(int i=1;i<=n;i++) make(i);
    ll total_cost = 0;
    for(auto &edge : edges){
        ll wt = edge.first;
        ll u = edge.second.first;
        ll v = edge.second.second;
        if(find(u) == find(v)) continue;
        Union(u,v);
        total_cost+=wt; 
    }
}



int main(){
    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    ll t;
    cin >> t;
    while(t--) {

    }
    return 0;
}