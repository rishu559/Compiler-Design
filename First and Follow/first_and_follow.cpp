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

bool isNonTerminal(string s){
    if(find(vec.begin(),vec.end(),s)!=vec.end()) return true;
    return false;
}

set<string> findFirst(string s){
    
    set<string> res;
    if(s=="eps") return {"eps"};
    else if(!isNonTerminal(s)) return {s};
    else{
        set<string> res1;
        for(string str:mp[s]){
            int pos = str.find('.');
            string temp = str.substr(0,pos);
            if(pos==-1) str = "";
            else str = str.substr(pos+1);
            
            // cout<<temp<<" "<<str;
            // return {};
            while(isNonTerminal(temp)) {
                set<string> first = findFirst(temp);
                if(first.find("eps")!=first.end() && str.size()!=0) {
                    pos = str.find('.');
                    temp = str.substr(0,pos);
                    if(pos==-1) str = "";
                    else str = str.substr(pos+1);
                }
                else temp = "something";
                res1.insert(first.begin(),first.end());
            }
            
            if(temp=="eps") res1.insert("eps");
            else if(temp!="something" ){
                res1.insert(temp);
                res1.erase("eps");
            }
            res.insert(res1.begin(),res1.end());
        }
    }
    return res;
}

int main()
{
    mp["A"]={"C.d"};
    mp["B"]={"g","d","eps"};
    mp["C"]={"j","eps"};
    
    for(auto i:mp){
        vec.push_back(i.first);
    }

    set<string> res = findFirst("A");
    for(string s:res){
        cout<<s<<"\n";
    }
}
