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

map<string,set<string>> first;

set<string> findFirst(string s){
    
    if(first.find(s)!=first.end()) return first[s];
    
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
    first[s]=res;
    return res;
}

vector<string> tokenize(string str){
    string s = "";
    vector<string> res;
    for(char c:str){
        if(c=='.'){
            res.push_back(s);
            s = "";
        }
        else s+=c;
    }
    res.push_back(s);
    return res;
}
map<string,set<string>> follow;

set<string> find_follow(string s){
    
    if(follow.find(s)!=follow.end()) return follow[s];
    
    for(auto m:mp){
        string st = m.first;
        for(string str:mp[st]){
            
            vector<string> term_NT = tokenize(str);
            int i=0;
            for(i=0;i<term_NT.size();i++){
                if(term_NT[i]==s)
                    break;
            }
            for(int j=i;j<term_NT.size();j++){
                bool has_epsilon = false;
                if(j==term_NT.size()-1){
                    set<string> follow_first = find_follow(st);
                    follow[s].insert(follow_first.begin(),follow_first.end());
                }
                else{
                    if(isNonTerminal(term_NT[j+1])){
                        set<string> first_next = findFirst(term_NT[j+1]);

                        if(first_next.find("eps")!=first_next.end()){
                            has_epsilon=true;
                            first_next.erase("eps");
                        }
                        follow[term_NT[i]].insert(first_next.begin(),first_next.end());
                    }
                    else{
                        follow[term_NT[i]].insert(term_NT[j+1]);
                    }
                }
                if(!has_epsilon) break;
            }
        }
    }
    return follow[s];
}

int main()
{
    mp["S"]={"B.A"};
    mp["A"]={"g","d","eps"};
    mp["B"]={"j"};
    
    for(auto i:mp){
        vec.push_back(i.first);
    }

    follow["S"] = {"$"};
    
    // set<string> res = find_follow("B");
    set<string> res = findFirst("A");

    for(string s:res){
        cout<<s<<"\n";
    }
}
