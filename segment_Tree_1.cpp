/**
 *    author:  nibbleCoder
 *    created: 15.11.2021 09:00:00
**/

#include<bits/stdc++.h>

using namespace std;

// **********************#define********************************

#define ll long long
#define ff first
#define ss second
#define nl "\n"
#define _p(str) cout << str << nl; 

// **********************typedef***************************************

typedef vector< ll > vll;
typedef pair< ll, ll > pll;

// *********************************for debugging*************************************

#define deb(...) cerr << "[" << #__VA_ARGS__ << "]: "; cerr << to_string(__VA_ARGS__) << endl
template <typename T, size_t N> int SIZE(const T (&t)[N]) { return N; } template<typename T> int SIZE(const T &t) { return t.size(); } string to_string(const string s, int x1 = 0, int x2 = 1e9) { return '"' + ((x1 < s.size()) ? s.substr(x1, x2 - x1 + 1) : "") + '"'; } string to_string(const char* s) { return to_string((string) s); } string to_string(const bool b) { return (b ? "true" : "false"); } string to_string(const char c) { return string({c}); } template<size_t N> string to_string(const bitset<N> &b, int x1 = 0, int x2 = 1e9) { string t = ""; for (int __iii__ = min(x1, SIZE(b)),  __jjj__ = min(x2, SIZE(b) - 1); __iii__ <= __jjj__; ++__iii__) { t += b[__iii__] + '0'; } return '"' + t + '"'; } template <typename A, typename... C> string to_string(const A (&v), int x1 = 0, int x2 = 1e9, C... coords); int l_v_l_v_l = 0, t_a_b_s = 0; template <typename A, typename B> string to_string(const pair<A, B> &p) { l_v_l_v_l++; string res = "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; l_v_l_v_l--; return res; } template <typename A, typename... C> string to_string(const A (&v), int x1, int x2, C... coords) { int rnk = rank<A>::value; string tab(t_a_b_s, ' '); string res = ""; bool first = true; if (l_v_l_v_l == 0) res += "\n"; res += tab + "["; x1 = min(x1, SIZE(v)), x2 = min(x2, SIZE(v)); auto l = begin(v); advance(l, x1); auto r = l; advance(r, (x2 - x1) + (x2 < SIZE(v))); for (auto e = l; e != r; e = next(e)) { if (!first) { res += ", "; } first = false; l_v_l_v_l++; if (e != l) { if (rnk > 1) { res += "\n"; t_a_b_s = l_v_l_v_l; }; } else { t_a_b_s = 0; } res += to_string(*e, coords...); l_v_l_v_l--; } res += "]"; if (l_v_l_v_l == 0) res += "\n"; return res; } void dbgm() {;} template<typename Heads, typename... Tails> void dbgm(Heads H, Tails... T) { cerr << to_string(H) << " | "; dbgm(T...); }
#define debm(...) cerr << "[" << #__VA_ARGS__ << "]: "; dbgm(__VA_ARGS__); cerr << endl


//---------------------------------------------------------------------------------------------

void FIO() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
#endif
}

//*****************************functions******************************************************
void google(ll t) {

#ifndef ONLINE_JUDGE
    cout << "Case #" << t << ": ";
#endif
}

class SegmentTree {
private:
      ll n;
      vll arr;
      vll tree;
      ll operation;
public:

   ll buildUtils( ll left_ans , ll right_ans ){

       // sum query
      if( operation == 0 )
          return left_ans + right_ans;
      
      
      // minm queries
      if( operation == 1 )
          return min( left_ans , right_ans );

      // maxm queries
      if( operation == 2 )
          return max( left_ans , right_ans );
      
      return 0;
   }

   void build(ll start, ll end, ll index){

       // if single element is reached
       if( start == end ){

          tree[ index ] = arr[ start ];
          return;
       }
      
       ll mid = start + ( end - start )/2;

       // start -> 0 , end -> 4 , mid -> 2 , index -> 0

       pll child = { 2*index + 1 , 2*index + 2 };

       // { 1, 2 }
       // compute for left subtree
       build( start, mid , child.ff ); 
       // compute for right subtree
       build( mid+1, end , child.ss );

       // merge the results
       tree[ index ] = buildUtils( tree[ child.ff ] , tree[ child.ss ] ); 

       return;
   }
   
   // leftIndex -> left index of the subarray we need to find sum of 
   // ll rightIndex -> right index of the subarray we need to find sum of  
   // ll leftSegmentIndex -> left index of the segment 
   // ll rightSegmentIndex -> right index of the segment 
   // ll index -> index of the segment tree

   // 1 3 -2 8 -7
   // leftIndex->2 , rightIndex->3 , leftSegmentIndex->0 , rightSegmentIndex->4 , index->0
   ll expressionUtils(bool left_exist, bool right_exist , ll left_ans, ll right_ans ){

      // sum query
      if( operation == 0 ){

          left_ans = !left_exist ? 0 : left_ans ;
          right_ans = !right_exist ? 0 : right_ans ;

          return left_ans + right_ans;
      }
      
      // minm queries
      if( operation == 1 ){

          left_ans = !left_exist ? LLONG_MAX : left_ans ;
          right_ans = !right_exist ? LLONG_MAX : right_ans ;

          return min( left_ans , right_ans );
      }

      // maxm queries
      if( operation == 2 ){

          left_ans = !left_exist ? LLONG_MIN : left_ans ;
          right_ans = !right_exist ? LLONG_MIN : right_ans ;

          return max( left_ans , right_ans );
      }

      return 0;
   }

   ll expression( ll leftIndex , ll rightIndex , ll leftSegmentIndex , ll rightSegmentIndex , ll index ){

       if( leftIndex == leftSegmentIndex and rightIndex == rightSegmentIndex )
          return tree[ index ];

       ll mid = leftSegmentIndex + ( rightSegmentIndex - leftSegmentIndex )/2; 

       ll left_ans, right_ans;
       bool left_exist = false, right_exist = false;

       pll child = { 2*index + 1, 2*index + 2 };
       
       if( leftIndex <= mid ){

            left_exist = true;
            left_ans = expression( leftIndex , min( mid , rightIndex ) , leftSegmentIndex , mid , child.ff );
       }

       if( rightIndex > mid ){

            right_exist = true;
            right_ans = expression( max( mid+1 , leftIndex ) , rightIndex , mid+1 , rightSegmentIndex , child.ss );
       }

       return expressionUtils( left_exist , right_exist , left_ans, right_ans );
   } 
   
   // 1 3 -2 8 -7
   // idx -> arr index ; leftSegmentIndex->0 , rightSegmentIndex->4 , index-> tree index
   void update( ll idx , ll diff , ll leftSegmentIndex , ll rightSegmentIndex , ll index ){
      
        ll mid  = leftSegmentIndex + ( rightSegmentIndex - leftSegmentIndex )/2;

        pll child = { 2*index + 1 , 2*index + 2 };

        if( leftSegmentIndex == rightSegmentIndex ){
           
           tree[ index ] += diff;
           return;
        }

        if( idx <= mid )
           update( idx , diff , leftSegmentIndex , mid , child.ff );
        
        else
           update( idx , diff , mid+1 , rightSegmentIndex , child.ss );

        tree[ index ] = buildUtils( tree[ child.ff ] , tree[ child.ss ] );
        return;
   }

   void solve( ll op ) {

        cin >> n;

        operation = op;

        arr = vll( n );

        for( auto &x:arr )
          cin >> x;

        tree = vll( 4*n );
        
        build(0 , n-1 , 0);

        debm( tree );

        ll queries;

        cin >> queries;

        ll k = queries;

        while( queries-- ){

            ll type , x, y;
            // type 0 -> sum , 1 -> update 
            cin >> type >> x >> y;

            google(k-queries);
            
            // here x -> left index , y -> right index of the subarray
            if( type == 0 ){

                if( x > y or x < 0 or y > (n-1) ){

                    _p("Out of Range!");
                    continue;
                }

                ll ans = expression( x , y , 0, n-1 , 0);
                _p( ans );
            }
            // here x -> index to be undated(0-indexed) , y -> value to which to be updated
            else if( type == 1 ){
                
                if( x < 0 or x > (n-1) ){

                    _p("Out of Range!");
                    continue;
                }

                update( x, y - arr[x] , 0, n-1 , 0);
                arr[ x ] = y;

                _p("Updated!");
            }
            
            else 
                _p("Invalid query!");
        }
    }
};

int main() {

    FIO();

    ll t, operation;
    //cin >> t;
    t = 1;

    cin >> operation;

    // operation -> 0 -> Sum queries
    // operation -> 1 -> min queries
    // operation -> 2 -> max queries

    SegmentTree solution;
    solution.solve(operation);
}