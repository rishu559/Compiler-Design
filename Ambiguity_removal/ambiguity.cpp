#include <bits/stdc++.h>

using namespace std;

map<string,vector<string>> mp;
vector<string> vec;

bool isPrefix(string s1,string s2){
    for(int i=0;i<s1.size();i++){
        if(s1[i]!=s2[i]) return false;
    }
    return true;
}

string makeNode(){
    string s= "A"+to_string(vec.size());
    vec.push_back(s);
    return s;
}

void remove_direct_recursion(string s){
    vector<string> alpha,beta;
    for (string str : mp[s]){
        if(isPrefix(s,str)){
            alpha.push_back(str.substr(s.size()+1));
        }
        else beta.push_back(str);
    }
    
    if(alpha.size()==0) return;
    mp[s].clear();
    
    string newNode = makeNode();
    for(string str:beta){
        mp[s].push_back(str+"."+newNode);
    }
    for(string str:alpha){
        mp[newNode].push_back(str+"."+newNode);
    }
    mp[newNode].push_back("eps");
}

void remove_indirect_recursion() {
    
    for(auto i:mp){
        vec.push_back(i.first);
    }
    
    for(int i=0;i<vec.size();i++){
        
        for(int j=0;j<i;j++){
            vector<string> gamma;
            for(int m=0;m<mp[vec[i]].size();m++){
                if(isPrefix(vec[j],mp[vec[i]][m])){
                    gamma.push_back(mp[vec[i]][m].substr(vec[j].size()));
                    mp[vec[i]].erase(mp[vec[i]].begin()+m);
                }
            }
            
            for(string str: gamma){
                for(string delta: mp[vec[j]]){
                    if(str.size()!=0)
                        mp[vec[i]].push_back(delta+str);
                    else mp[vec[i]].push_back(delta);
                }
            }
        }
        
        remove_direct_recursion(vec[i]);
    }
}

void print(){
    for(auto i:mp){
        cout<<i.first<<" -> ";
        vector<string> s = i.second;
        for(int j=0;j<s.size();j++){
            cout<<s[j];
            if(j!=s.size()-1)
            cout<<" | ";
            
        }
        cout<<endl;
    }
}

bool isSame(string s1,string s2){
    for(int i=0;i<s1.size();i++){
        if(s1[i]==s2[i]&&s1[i]=='.') return true;
        else if(s1[i]!=s2[i]) return false;
    }
    return false;
}

string longestCommonPrefix(vector<string> ar)
{
    int n = ar.size();

    if (n == 0)
        return "";

    if (n == 1)
        return ar[0];

    sort(ar.begin(),ar.end());

    int en = min(ar[0].size(),
                 ar[n - 1].size());

    string first = ar[0], last = ar[n - 1];
    int i = 0;
    while (i < en && first[i] == last[i])
        i++;
 
    string pre = first.substr(0, i);
    return pre;
}


bool fact_helper(string s){

    vector<vector<string>> temp(10);
    sort(mp[s].begin(),mp[s].end());
    int k=0;
    temp[k].push_back(mp[s][0]);

    for(int i=1;i<mp[s].size();i++){
        if(isSame(mp[s][i],mp[s][i-1])){
            temp[k].push_back(mp[s][i]);
        }
        else{
            k++;
            temp[k].push_back(mp[s][i]);
        }
    }
    
    for(vector<string> str:temp){
        if(str.size()==0) continue;
        for(string s1:str){
            cout<<s1<<" ";
        }
        cout<<"\n";
    }
    bool hasPrefix = false;
    
    mp[s].clear();
    for(vector<string> str:temp){
        if(str.size()==0) break;
        if(str.size()==1){
            mp[s].push_back(str[0]);
        }
        else{
            hasPrefix=true;
            string prefix = longestCommonPrefix(str);
            string newNode = makeNode();
            
            bool nodot = false;
           
            if(prefix[prefix.size()-1]!='.'){
                mp[s].push_back(prefix+"."+newNode);
                nodot = true;
            }
            else mp[s].push_back(prefix+newNode);
            for(string s1:str){
                if(s1==prefix){
                    mp[newNode].push_back("eps");
//                     nodot = true;
                }
                else{
                    if(nodot)
                        mp[newNode].push_back(s1.substr(prefix.size()+1));
                    else mp[newNode].push_back(s1.substr(prefix.size()));
                 }
            }
            for(string str1:mp["A1"]) cout<<str1<<" ";
        }
    }
    return hasPrefix;
}

void leftfactoring(){
    for(auto i:mp){
        vec.push_back(i.first);
    }
    
    for(int i=0;i<vec.size();){
    
        bool hasPrefix = fact_helper(vec[i]);
        if(!hasPrefix) i++;

    }
}

int main()
{
    mp["A"]={"c.f","c.f.g.t","f.g.t","f.e.t"};
    // mp["B"]={"C.b"};
    // mp["C"]={"A","B","f"};
    print();
    leftfactoring();
    // cout<<"hello";
    // fact_helper("A");
    print();
    // fact_helper("A");
}
