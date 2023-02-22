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
    
    if(follow.find(s)!=follow.end() && s!="E") return follow[s];
    
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
                    if(st==term_NT[j]) continue;
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

vector<vector<string>> predictive_parser(map<string,int> non_terminals,map<string,int> terminals){
    
    vector<vector<string>> pre_par( 5, vector<string> (6,""));
    for(auto i:mp){
        string st = i.first;
        
        for(string prod:mp[st]){
            set<string> first;
            vector<string> vec = tokenize(prod);
            for(int j=0;j<vec.size();j++){
                set<string> localf = findFirst(vec[j]);
                if(localf.find("eps")==localf.end()){
                    first.insert(localf.begin(),localf.end());
                    break;
                }
                else if(j!=vec.size()-1){
                    localf.erase("eps");
                    first.insert(localf.begin(),localf.end());
                }
                else{
                    first.insert(localf.begin(),localf.end());
                }
            }
            
            for(string s:first){
                if(s=="eps"){
                    for(string str1 :follow[st]){
                        pre_par[non_terminals[st]][terminals[str1]] = "eps";
                    }
                }
                else{
                    pre_par[non_terminals[st]][terminals[s]] = prod;
                }
            }
        }
    }
    return pre_par;
}
map<string,int> non_terminals;
map<string,int> terminals;

string find_by_no(int n){
    for(auto i:non_terminals){
        if(i.second==n) return i.first;
    }
    return "";
}
int main()
{
    mp["E"]={"T.B"};
    mp["B"]={"+.T.B","eps"};
    mp["T"]={"F.C"};
    mp["C"]={"*.F.C","eps"};
    mp["F"]={"(.E.)","id"};
    
    
    non_terminals["E"]=0;
    non_terminals["B"]=1;
    non_terminals["T"]=2;
    non_terminals["C"]=3;
    non_terminals["F"]=4;
    
    terminals["id"]=0;
    terminals["+"]=1;
    terminals["*"]=2;
    terminals["("]=3;
    terminals[")"]=4;
    terminals["$"]=5;
    
    for(auto i:mp){
        // cout<<i.first<<" ";
        vec.push_back(i.first);
    }

    follow["E"] = {"$"};

    for(auto i:non_terminals){
        // cout<<i<<" ";
        set<string> im=find_follow(i.first);
    }
    
    // set<string> im=find_follow("F");
    // for(string s:im) cout<<s<<" ";
    
    // for(auto i : follow){
    //     cout<<i.first<<"->";
    //     for(string s : i.second){
    //         cout<<s<<" ";
    //     }
    //     cout<<"\n";
    // }

    vector<vector<string>> pre_par = predictive_parser(non_terminals,terminals);
    // cout<<"1";
    cout<<setw(10)<<"id"<<setw(10)<<"+"<<setw(10)<<"*"<<setw(10)<<"("<<setw(10)<<")"<<setw(10)<<"$\n";
    for(int i=0;i<5;i++){
        cout<<find_by_no(i);
        for(int j=0;j<6;j++){
            cout<<setw(10)<<pre_par[i][j];
        }
        cout<<"\n";
    }
}