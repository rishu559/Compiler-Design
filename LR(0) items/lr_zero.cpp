
#include <bits/stdc++.h>
using namespace std;

map<string,vector<string>> mp,closure_box;
vector<vector<string>> lr0;
vector<string> vec;

bool isNonTerminal(string s){
    if(find(vec.begin(),vec.end(),s)!=vec.end()) return true;
    return false;
}

void makeAugmented(){
    mp["A"] = {"E"};
}

vector<string> findClosure(string s,set<string> found){
    if(closure_box.find(s)!=closure_box.end()) return closure_box[s];
    if(!isNonTerminal(s)) return {};
    vector<string> closure;
    for(string str:mp[s]){
        closure.push_back(s+"->."+str);
        string next_item = str.substr(0,1);
        if(isNonTerminal(next_item) && found.find(next_item)==found.end()){
            found.insert(next_item);
            vector<string> rec = findClosure(next_item,found);
            for(string str1:rec){
                closure.push_back(str1);
            }
        }
    }
    closure_box[s]=closure;
    return closure;
}

queue<vector<string>> line;

bool isAlreadyAnItem(vector<vector<string>> lr0,vector<string> item){
    sort(item.begin(),item.end());
    
    for(vector<string> vec:lr0){
        if(vec.size()!=item.size()) continue;
        sort(vec.begin(),vec.end());
        for(int i=0;i<vec.size();i++){
            if(vec[i]!=item[i]) break;
            if(i==vec.size()-1) return true;
        }
    }
    return false;
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

string start_symbol;
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
        st = rs(st,'.');
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
            mp[left].push_back(right);
        }
        getline(cin,st);
    }
}

void find_elaarzero(){
    if(lr0.size()==0){
        vector<string> first_item = findClosure("A",{"A"});
        line.push(first_item);
        lr0.push_back(first_item);
    }
    while(!line.empty()){
        vector<string> first_item = line.front();
        line.pop();
        map<string,vector<string>> transitions;
        for(string str:first_item){
            int find = str.find('.');
            if(find==str.size()-1){
                continue;
            }
            string ticket = str.substr(find+1,1);
            swap(str[find],str[find+1]);
            transitions[ticket].push_back(str);
            find = find+1;
            
            if(find!=str.size()){
                string afterdot = str.substr(find+1,1);
                vector<string> closure_of_afterdot = findClosure(afterdot,{afterdot});
                for(string str1:closure_of_afterdot){
                    transitions[ticket].push_back(str1);
                }
            }
        }
        for(auto i:transitions){
            if(!isAlreadyAnItem(lr0,i.second)){
                line.push(i.second);
                lr0.push_back(i.second);
            }
        }
    }
}

void printGrammar(){
    for(auto i:mp){
        for(string str:i.second){
            cout<<i.first<<"->."<<str<<"\n";
        }
    }
}

int main()
{
    mp["E"]={"T","E+T"};
    mp["T"]={"F","T*F"};
    mp["F"]={"(E)","d"};

    vec = {"A","E","T","F"};

    // Let augmented LR(0) item be A
    
    makeAugmented();
    cout<<"Augmented Grammar :\n";
    printGrammar();

    cout<<"\nSet of LR(0) items:\n\n";
    find_elaarzero();

    int i=0;
    for(vector<string> vec:lr0){
        cout<<"I"<<i++<<"\n";
        for(string str:vec){
            cout<<str<<"\n";
        }
        cout<<"\n";
    }
}