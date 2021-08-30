#include <bits/stdc++.h>
using namespace std;

#define ll long long

class Operations{
    public:
    	//utils functions
    	ll midValue( ll firstIndex, ll lastIndex){

    		 return firstIndex + ( lastIndex - firstIndex )/2;
    	}

    	ll parent( ll index ){

    		 return floor((index-1)/2);
    	}

    	ll leftChild( ll index ){

    		return 2*index + 1;
    	}

    	ll rightChild( ll index ){

    		return 2*index + 2;
    	}

        ll noOfLevels( ll n ){

            ll log = log2(n);
            return pow( 2, log )==n ? log : log+1;
        }

        ll noOfDigits( ll n ){

        	 return log10(n)+1;
        }
    	// note the parameters
    	// ss -> starting index of the current node
    	// se -> last index of the current node
    	// qs -> starting index of the demanding range
    	// q2 -> ending index of the demanding range
    	// index -> index of the Tree node

        // O(n) time
    	ll create( vector<ll> &Tree, vector<ll> arr, ll ss, ll se, ll index){

            // base condition
    		if( ss==se ){
                
                Tree[index] = arr[ ss ];
                return Tree[ index ];
    		}

            // functions
            ll mid = midValue( ss , se );

            ll ls = create( Tree, arr, ss, mid, leftChild( index ) );
            ll rs = create( Tree, arr, mid+1, se, rightChild(index) );

            Tree[index] = ls + rs;

            return Tree[index];
    	}
        
        //preProcessing
        vector<ll> preProcessing( vector<ll> arr, int n){

        	cout<<"Preprocessing...\n";
            
            ll x = noOfLevels(n);
            ll size = 2*pow(2,x)-1;

        	vector<ll>Tree( size);

            create( Tree, arr, 0, n-1, 0 );
            
            cout<<"Processed...\n"; 

            return Tree;
        }

        void Print( vector<ll> Tree ){

        	ll t = 1, index = 0;
        	ll levels = noOfLevels( Tree.size() );

        	ll ffSpace = pow( 2, levels-1 ) ,ssSpace;

        	for(auto x:Tree){

        		 for( ll i=0 ; i<ffSpace ; i++ ) cout<<" ";

        		 cout<<x;

        		 index++;

        		 if(index==t) { 
        		 
        		 	 index = 0;
        		 	 t *= 2;

                     ssSpace = ffSpace -1;
        		 	 ffSpace /= 2;

        		 	 cout << "\n";
        		 	 continue;
        		 }

        		 for( ll i=0 ; i<(ssSpace-1) ; i++ ) cout<<" ";
        	}
        }

        ll getSum(ll ss, ll se, ll qs, ll qe, ll index, vector<ll> Tree){

            // complete overlap
        	if( ss==qs && se==qe )
        		 return Tree[index];
            
            ll mid = midValue( ss, se ),ls=0,rs=0;

            // find mutual overlap
            // we are making sure that there would be no cases where no overlap is possible
            if( qs <= mid )
            	ls = getSum( ss, mid, qs, mid, leftChild( index), Tree );

            if( qe > mid )
            	rs = getSum( mid+1, se, mid+1, qe, rightChild( index), Tree );

            return ls + rs;
        }

        void updateValue(ll ss, ll se, ll i, ll diff, ll index, vector<ll> &Tree){
            
            Tree[index] += diff;

            if( ss==se && ss==i )
            	return;

            ll mid = midValue( ss, se );

            if(i<=mid)
            	updateValue( ss, mid, i, diff, leftChild(index), Tree );
            else 
            	updateValue( mid+1, se, i, diff, rightChild(index), Tree );
        }

        //real functions
		void solve(){
            
            ll n;
            cin>>n;

			vector<ll>arr(n);

			for(ll i=0; i<n; i++) 
				 cin >> arr[i];

			vector<ll> Tree = preProcessing(arr,n);

            Print(Tree);

            // cout<<" For getting sum of a given range .. press 1 followed by 2 numbers representing the left and right indexes\n";
            // cout<<" For updating an element press 2 followed by 2 numbers representing the index of the element and the update value\n";
            // cout<<" Press 3 to exit\n";

            while(1){

            	 cout<<"\n";

                 ll op, ls,rs, i, x;
            	 cin>>op;

            	 if(op==3){

            	 	  cout<<"Exiting...\n";
            	 	  break;
            	 }

            	 switch(op){

            	 	case 1:
                        cin >> ls >> rs;
                        cout<<"Sum processing...\n";
                        
                        cout << getSum(0, n-1, ls, rs, 0, Tree) <<"\n"; 
                        break; 

                    case 2:
                        cin >> i >> x;

                        ll diff = x - arr[i];

                        cout<<"Value updating...\n";
                        arr[i] = x;
                        
                        updateValue(0, n-1, i, diff, 0, Tree );
                        
                        cout<<"Successfully updated...\n";
                        break;

            	 }
            }
		}
};

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // cout<<"Learn about Segment Tree DS!!\nIt is used to solve range query problems with operations ::\n";
    // cout<<"1) Update an element of the array at index i to x i.e. A[i]=x\n";
    // cout<<"2) Range query operations such as finding the sum of a particular Segment of the array\n";

    // cout<<"Using Segment tree we can solve both operations in O(log n) time efficiently\n";
    // cout<<"However, it takes a preprocessing time O(n) and auxilary space O(n)\n";

    // cout<<"Like heap data structure, it is also an array representaion of tree\n";

    Operations solution;

    solution.solve();

	return 0;
}