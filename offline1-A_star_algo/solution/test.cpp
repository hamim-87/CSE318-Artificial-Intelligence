#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>


using namespace std;
using namespace __gnu_pbds;


#define ordered_set tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>
#define ll long long 
#define Faster ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
 
 
//constants:
const int   N                               = (int) 1e6+5;
const int   M                               = (int) 1e9+5;
const int   mod                             = (int) 998244353;




////////////_____ Segment Tree __________//////
struct item{
    int m,c;
};


//range [l,r] = sg.calc((l-1),r);
struct segment_tree{
    int size;
    //change
    vector<item> seg;
    //change
    item merge(item a, item b)
    {
        if(a.m<b.m) return a;
        else if(a.m>b.m) return b;
        else return {a.m, a.c+b.c};
    }
    //change
    item single_item(int v)
    {
    return {v,1};
    }
    //change
    item NUTRAL_ITEM()
    {
        return {INT_MAX,0};
    }
    void init(int n)
    {
        size = 1;
        while(size<n) size*=2;
        seg.resize(2*size,NUTRAL_ITEM());
    }
    void build(vector<int> &a,int x, int lx, int rx)
    {
        if(rx-lx == 1)
        {
            if(lx < a.size())
            {
                seg[x] = single_item(a[lx]);
            }
            return;
        }
        int m = (lx+rx)/2;
        build(a,2*x+1,lx,m);
        build(a,2*x+2,m,rx);
        seg[x] = merge(seg[2*x+1], seg[2*x+2]);
    }
    void build(vector<int> &a)
    {
        build(a,0,0,size);
    }
    void set(int i , int val, int x, int lx, int rx)
    {
        if(rx-lx == 1)
        {
            seg[x] = single_item(val);
            return;
        }
        int m = (lx+rx)/2;
        if(i<m)
        {
            set(i,val,2*x+1,lx,m);
        }
        else{
            set(i,val,2*x+2,m,rx);
        }
        seg[x] = merge(seg[2*x+1], seg[2*x+2]);
    }
    void set(int i, int val)
    {
        set(i,val,0,0,size);
    }
    item calc(int l, int r, int x, int lx, int rx)
    {
        if(lx >= r || rx <= l  )
        {
            return NUTRAL_ITEM();
        }
        if(lx>= l && rx<= r) return seg[x];
        int m = (lx+rx)/2;
        auto s1 = calc(l,r,2*x+1,lx,m);
        auto s2 = calc(l,r,2*x+2,m,rx);
        return merge(s1,s2);
    }
    item calc(int l, int r)
    {
        return calc(l,r,0,0,size);
    }
};


////////////_____COMBINATORICS________/////////
vector<ll> F,invF;
vector<ll> MInv;
void Modular_Inverse(int p){
    MInv.resize(N+1);
    MInv[0]=MInv[1]=1;
    for(int i=2;i<=N;i++){
        MInv[i]=(MInv[p%i]*(p-(p/i)))%p;
    }
    // Facts of those numbers should be counted as considering each i=MInv[i];
}
void PreCalFacts(){
    F.resize(N+1);
    invF.resize(N+1);
    F[0]=F[1]=1;
    for(int i=2;i<=N;i++){
        F[i]=(i*F[i-1])%mod;
    }
    Modular_Inverse(mod);
    invF[0]=invF[1]=1;
    for(int i=2;i<=N;i++){
        invF[i]=(MInv[i]*invF[i-1])%mod;
    }
}
ll nCr(int n,int r){
    if(r > n || n < 0 || r < 0)return 0;
    return F[n]*invF[r]%mod*invF[n-r]%mod;
}
////////////_____COMBINATORICS________////////


//number theory
ll binaryExp(ll  a, ll b){
    ll result = 1;
    while(b>0){
        if(b&1){
            result = ((result%mod)*(a%mod))%mod;
        }
        a= ((a%mod)*(a%mod))%mod;
        b>>=1;
    }
    return result;
}


void dfs(ll node, vector<vector<ll>> &adj, ll vis[], vector<ll> &ls) {
//void dfs(ll node, map<ll, vector<ll>> &adj, map<ll,ll> &vis, vector<ll> &ls) {
    vis[node] = 1;
    ls.push_back(node);
    for(auto it: adj[node]){
        if(!vis[it]) {
            dfs(it,adj,vis,ls);
        }
    }
}


int main()
{
     
}