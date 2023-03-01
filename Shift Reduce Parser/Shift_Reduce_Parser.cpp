
#include <bits/stdc++.h>

using namespace std;
map<string,set<string>> mp;
string start_symbol;
map<string,int> terminals,non_terminals;

string isProd(string s){
    for(auto i:mp){
        if(i.second.find(s)!=i.second.end()){
            return i.first;
        }
    }
    return "";
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

string rs(string s,char symbol)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == symbol)
        {
            s.erase(s.begin() + i);
            i--;
        }
    }
    return s;
}

void input_grammar(){
   
    cout<<"Enter the start symbol : ";
    getline(cin,start_symbol);
    
    /*
        E-> T.B 
        B-> +.T.B|eps 
        T-> F.C 
        C ->*.F.C |eps 
        F->(.E.)|id
    */
    cout<<"Enter the productions (end to stop) : ";
    string st;
    getline(cin,st);
    while(st!="end"){
        st = rs(st,' ');
        int pos = st.find("->");
        
        string left = st.substr(0,pos);
        st = st.substr(pos+2);
        while(st.size()!=0){
            pos = st.find("|");
            string right;
            if(pos==-1){
                right = st;
                st = "";
            }
            else{
                right = st.substr(0,pos);
                st = st.substr(pos+1);
            }
            mp[left].insert(right);
        }
        getline(cin,st);
    }
}

vector<string> vec;

void utility(string stack,string &action){
    bool found = false;

    vector<string> stack_token = tokenize(stack);

    string prod ="";
    for(int i=stack_token.size()-1;i>=1;i--){
        if(prod=="")
        prod = stack_token[i]+prod;
        else 
        prod = stack_token[i]+"."+prod;
        
        string left = isProd(prod);
        if(left!=""){
            vec.clear();
            vec.push_back(left);
            vec.push_back(prod);
            action = "REDUCE TO "+left+" -> "+prod;
            found=true;
        }
        else {
            if(!found)
            action = "SHIFT";
        }
    }
}

void srp(string input){
    input = input+".$";

    vector<string> input_token = tokenize(input);

    string stack = "$";
    string action = "SHIFT";
    cout<<left<<setw(20)<<"Stack"<<setw(20)<<"Input"<<setw(20)<<"Action"<<"\n\n";
    // cout<<setw(20)<<stack<<setw(20)<<input<<setw(20)<<action<<"\n";
    cout<<left<<setw(20)<<rs(stack,'.')<<setw(20)<<rs(input,'.')<<setw(20)<<rs(action,'.')<<"\n";
    
    int num = 0;

    while(true){
        if(action=="SHIFT"){
            if(input=="$" && action=="SHIFT"){
                // cout<<setw(20)<<stack<<setw(20)<<input<<setw(20)<<"Reject"<<"\n";
                cout<<setw(20)<<rs(stack,'.')<<setw(20)<<rs(input,'.')<<setw(20)<<"Reject"<<"\n";
                break;
            }
            stack = stack+"."+input_token[num++];
            input=input.substr(input_token[num-1].size()+1);
            vec.clear();
            utility(stack,action);
            
        }
        else if(action[0]=='R'){
            stack = stack.substr(0,stack.size()-vec[1].size());
            stack = stack+vec[0];
            vec.clear();
            
            if(stack=="$."+start_symbol && input=="$"){
                action = "Accept";
                // cout<<setw(20)<<stack<<setw(20)<<input<<setw(20)<<action<<"\n";
                cout<<left<<setw(20)<<rs(stack,'.')<<setw(20)<<rs(input,'.')<<setw(20)<<rs(action,'.')<<"\n";
                break;
            }
            
            utility(stack,action);
        }
        
        // cout<<setw(20)<<stack<<setw(20)<<input<<setw(20)<<action<<"\n";
        cout<<left<<setw(20)<<rs(stack,'.')<<setw(20)<<rs(input,'.')<<setw(20)<<rs(action,'.')<<"\n";
    }
}

int main()
{
    mp["S"]={"(.L.)","a"};
    mp["L"]={"L.,.S","S"};
    
    start_symbol = "S";

    // input_grammar();
    
    string input= "(.a.,.(.a.,.a.)";
    // cout<<"Enter input string :";
    // cin>>input;

    srp(input);
    return 0;
}
