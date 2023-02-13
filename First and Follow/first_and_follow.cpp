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
    
    for(auto i:mp){
        vec.push_back(i.first);
    }
    
    set<string> res;
    if(s=="eps") return {"eps"};
    else if(!isNonTerminal(s)) return {s};
    else{
        for(string str:mp[s]){
            int pos = str.find('.');
            string temp = str.substr(0,pos);
            str = str.substr(pos+1);
            while(isNonTerminal(temp)) {
                set<string> first = findFirst(temp);
                if(first.find("eps")!=first.end()) {
                    pos = str.find('.');
                    temp = str.substr(0,pos);
                    str = str.substr(pos+1);
                }
                else temp = "something";
                res.insert(first.begin(),first.end());
            }
            if(temp!="something") res.insert(temp);
        }
    }
    return res;
}

int main()
{
    mp["A"]={"d.f","B.C.e","f.g.t","f.e.t"};
    mp["B"]={"g","eps"};
    mp["C"]={"j","eps"};

    set<string> res = findFirst("A");
    for(string s:res){
        cout<<s<<"\n";
    }
}