#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define LETTER_SIZE 26
#define ff first
#define ss second 

struct TrieNode{
    
    bool isEnd;
    struct TrieNode *child[LETTER_SIZE];

    TrieNode(){

       for (int i = 0; i < LETTER_SIZE; ++i)
             child[i] = NULL;
       isEnd = false;
    }
};

static bool processed = false;

class Operations{

   TrieNode* root = new TrieNode();

   public:
     void insert_word(string str){

         cout<<"Inserting "<<str<<" in DB\n";

         TrieNode* curr = root;

         for (int i = 0; i < str.length() ; ++i){
             
             int index = str[i] - 'a';

             if( curr -> child[index] == NULL)
                   curr -> child[index] = new TrieNode();

             curr = curr -> child[index];
         }
         
         if(curr->isEnd){

             cout<<"Word already in use!\n";
             return;
         }

         curr->isEnd = true;
         cout<<"Successfully inserted word - "<<str<<"\n";
     }

     bool isEmpty(TrieNode* curr){

         for (int i = 0; i < LETTER_SIZE; ++i){
             
             if(curr->child[i]!=NULL) return false;
         }

         return true;
     }

     TrieNode* delete_key_util(TrieNode* curr, string str, int idx){

         if(curr==NULL){
             
             cout<<"Word "<<str<<" does not exist\n";

             processed = true;
             return NULL;
         }

         if( idx==str.length() ){

             curr -> isEnd = false;

             if( isEmpty(curr)==true ){

                 delete(curr);
                 curr = NULL;
             
             }else{
                
                cout<<"Successfully deleted "<<str<<" from DB\n";
                processed = true;
             }

             return curr;
         }

         int index = str[idx] - 'a';

         curr->child[index] = delete_key_util( curr->child[index] , str, idx+1 );
 
         if( isEmpty(curr)==true and curr->isEnd==false and idx!=0){
              
              delete(curr);
              curr = NULL;
         }
         return curr;
     }

     void delete_word(string str){

         processed = false;
         cout<<"Deleting "<<str<<" from DB\n";

         //3 cases possible
         // 1-> geeks exist and geek need to be deleted
         // 2-> bat need to be deleted and bat exist
         // 3-> zoo need to be deleted with no matching prefix

         // root, word, 0

         root = delete_key_util(root , str, 0);

         if(!processed)
             cout<<"Successfully deleted "<<str<<"\n";
     }

     bool search_word(string str){
         
         cout<<"Searching "<<str<<" from DB\n";

         TrieNode* curr = root;

         for (int i = 0; i < str.length() ; ++i){
             
             int index = str[i] - 'a';

             if( curr -> child[index] == NULL){

                cout<<"Word "<<str<<" does not exist\n";
                return false;
             }

             curr = curr -> child[index];
         }
         
         cout<<"Word "<<str<<" exist\n";
         return true;
     }

     void prefix_searching(string str){
         
         cout<<"Loading...\n";

         vector< string >V;
         queue< pair< TrieNode* ,string> >Q; 

         TrieNode* curr = root;

         for (int i = 0; i < str.length(); ++i){

              int index = str[i] - 'a';

              if(curr->child[index]==NULL){

                   cout<<"No matches\n";
                   return;
              }
              
              curr = curr->child[ index];
         }

         Q.push({ curr , str });

         while(!Q.empty()){
             
             pair<TrieNode*, string> curr_node = Q.front();
             Q.pop();

             if( curr_node.ff -> isEnd )
                  V.push_back( curr_node.ss );

             for(int i=0; i<LETTER_SIZE ; i++){

                  if( curr_node.ff -> child[i] ) 
                       Q.push({ curr_node.ff -> child[i], curr_node.ss + (char)('a'+i) });
             }
         }

         cout<<"\nSuggested names are :\n";

         for( auto x:V )
            cout<<x<<" ";

         cout<<"\n";
     }

     void solve(){
         
         cout<<"Select 1,2,3,4,5 based on the Operations to be performed\n";

         cout<<"1 -> insert \n";
         cout<<"2 -> delete \n";
         cout<<"3 -> search \n";
         cout<<"4 -> prefix_searching\n";
         cout<<"5 -> exit \n";

         while(1){

             cout<<"\n";

             int op;
             string str;

             cin>>op;

             if(op==5){

                 cout<<"Exiting...";
                 break;
             }

             cin>>str;
             
             //converting the strings to lower case before execution
             transform( str.begin(), str.end(), str.begin(), ::tolower );

             switch(op){

                 case 1:
                    insert_word(str);
                    break;

                 case 2:
                    delete_word(str);
                    break;

                 case 3:
                    search_word(str);
                    break;

                 case 4:
                     prefix_searching(str);
                     break;
             }
         }
     }
};

int main(){

   ios_base::sync_with_stdio(0);
   cin.tie(0);
   cout.tie(0);

   cout<<"Here's the implementation of the auto-complete feature of trie Data Structure\n";

   Operations solution;
   solution.solve();

   return 0;
}
