/*Let's get high :D*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
#define MOD                 1000000007LL
#define EPS                 1e-9
#define io                  ios_base::sync_with_stdio(false);cin.tie(NULL);
#define M_PI                3.14159265358979323846

template <typename T> T gcd(T a, T b){return (b==0)?a:gcd(b,a%b);}
template <typename T> T lcm(T a, T b){return a*(b/gcd(a,b));}
template <typename T> T mod_exp(T b, T p, T m){T x = 1;while(p){if(p&1)x=(x*b)%m;b=(b*b)%m;p=p>>1;}return x;}
template <typename T> T invFermat(T a, T p){return mod_exp(a, p-2, p);}
template <typename T> T exp(T b, T p){T x = 1;while(p){if(p&1)x=(x*b);b=(b*b);p=p>>1;}return x;}

const int MAXN =  2e4+5;
int n;
int parent[MAXN];
int size[MAXN];

void init(){
    for(int i = 1;i <= n; i++){
        parent[i] = i;
        size[i] = 1;
    }
}

int root(int i){
    while(i != parent[i]){
        parent[i] = parent[parent[i]];
        i = parent[i];
    }
    return i;
}

bool find(int a, int b){
    return root(a) == root(b);
}

void union1(int a, int b){
    int root_a = root(a);
    int root_b = root(b);
    
    if(root_a == root_b)
        return;
    
    if(size[root_a] < size[root_b]){
        parent[root_a] = root_b;
        size[root_b] += size[root_a];
    }else{
        parent[root_b] = root_a;
        size[root_a] += size[root_b];
    }
}

int main(){
    io;
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        vector<pair<int, int> > edges;
        init();
        for(int i= 0;i < n-1; i++){
            int a, b;
            cin >> a >> b;
            edges.push_back({a, b});
        }
        unordered_set<int> removed_edges;
        vector<int> queries;
        int q;
        cin >> q;
        while(q--){
            char c;
            cin >> c;
            if(c == 'R'){
                int e;
                cin >> e;
                e--;
                removed_edges.insert(e);
                queries.push_back(e);
            }else
                queries.push_back(-1);
        }
        ll ans = (n*(n-1))/2;
        for(int i = 0;i < n-1; i++){
            if(removed_edges.find(i) == removed_edges.end()){
                // this edge is present
                int a = edges[i].first;
                int b = edges[i].second;
                int root_a = root(a);
                int root_b = root(b);
                int maxx = max(size[root_a], size[root_b]);
                ans -= maxx;
                union1(a, b);
            }
        }
        vector<int> answers;
        for(int i = queries.size()-1; i >= 0; i--){
            if(queries[i] == -1){
                // Q type query
                answers.push_back(ans);
            }else{
                int idx = queries[i];
                int a = edges[idx].first;
                int b = edges[idx].second;
                int root_a = root(a);
                int root_b = root(b);
                ans -= size[root_a]*size[root_b];
                union1(a, b);
            }
        }
        for(int i = answers.size()-1;i >= 0; i--)
            cout << answers[i] << endl;
        cout << endl;
    }
    return 0;
}