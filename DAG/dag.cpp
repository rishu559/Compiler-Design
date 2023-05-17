#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    string name;
    string op;
    vector<node*> children;
    
};
vector<string> tokensize(string str){
    vector<string> ans;
    string temp = "";
    int c=0;
    for(c=0;c<str.size();c++){
        char i = str[c];
        if(i=='=') break;
        temp +=i;
    }
    c++;
    ans.push_back(temp);
    temp="";
    for(;c<str.size();c++){
        char i=str[c];
        if(i=='+'||i=='-'||i=='/'||i=='*'){
            if(temp!=""){
                ans.push_back(temp);
                temp = "";
            }
            string operator1 = string(1,i);
            ans.push_back(operator1);
        }
        else temp+=i;
    }
    if(temp!="") ans.push_back(temp);
    return ans;
}
node* convertToDAG(vector<string> threeAd){
    unordered_map<string,node*> mp;
    node* root1;
    for(string s:threeAd) {
        vector<string> st = tokensize(s);
        // for(string s:st) cout<<s<<" ";
        node* root = new node();
        root1 = root;
        root->name = st[0];
        if(st.size()==4){
            root->op = st[2];

            if(mp.find(st[1])!=mp.end()){
                root->children.push_back(mp[st[1]]);
            }
            else{
                node* left = new node();
                left-> name = st[1];
                left->op = st[1]; 
                mp[st[1]] = left;
                root->children.push_back(left);
            }
            if(mp.find(st[3])!=mp.end()){
                root->children.push_back(mp[st[3]]);
            }
            else{
                node* right = new node();
                right-> name = st[3];
                right->op = st[3]; 
                mp[st[3]]=right;
                root->children.push_back(right);
            }
        }
        else if(st.size()==3){
            root->op = st[1];
            if(mp.find(st[3])!=mp.end()){
                root->children.push_back(mp[st[3]]);
            }
            else{
                node* left = new node();
                left-> name = st[3];
                left->op = st[3]; 
                mp[st[3]]=left;
                root->children.push_back(left);
            }
        }
        else root->op = st[1];
        mp[st[0]] = root;
    }
    return root1;
}
unordered_set<string> st;
void showGraph(node* root){
    if(st.find(root->name)!=st.end()) return;
    int n = root->children.size();
    if(n==0){
         return;
    }
    cout<<root->name<<"=";
    if(n==1){
        cout<<root->op<<" ";
        cout<<root->children[0]->name<<" ";
    }
    else if(n==2){
        cout<<root->children[0]->name<<" ";
        cout<<root->op<<" ";
        cout<<root->children[1]->name<<" ";
    }
    st.insert(root->name);
    cout<<"\n";
    for(node* temp : root->children){
        showGraph(temp);
    }  
}
int main(){
    vector<string> threeAd = {"t0=a+b","t1=t0+c","d=t0+t1"};
    node * root = convertToDAG(threeAd);
    showGraph(root);

    return 0;
}