#include <bits/stdc++.h>
using namespace std;

#include "Astarv1.hpp"
 
 
//constants:
const int   N                               = (int) 1e6+5;
const int   M                               = (int) 1e9+5;
const int   mod                             = (int) 998244353;


int main()
{
   
     
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif


    int k;
    cin>>k;
    Board* board = new Board(k);
    cin>>*board;

    string ht;cin>>ht;

    AStar* aStar = new AStar(board,ht);
    aStar->search();

    
}