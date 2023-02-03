
#include <bits/stdc++.h>
using namespace std;

vector<vector<set<int>>> makenfa(set<int>& final_nfa){
    int number;
    cout<<"Enter number of states: ";
    cin>>number;
    vector<vector<set<int>>> nfa(number);

    cout<<"Type end to stop input: ";
    string str;
    cin>>str;
    while(str!="end"){
        int start;
        set<int> inputa,inputb;
        cout<<"From state: ";
        cin>>start;
        int n;
        cout<<"To states for input a (-1 to stop entering): ";
        cin>>n;
        while(n!=-1){
            inputa.insert(n);
            cin>>n;
        }
        cout<<"To states for input b (-1 to stop entering): ";
        cin>>n;
        while(n!=-1){
            inputb.insert(n);
            cin>>n;
        }
        set<int> s ;
        s.insert(start);
        nfa[start]={inputa,inputb};
        cin>>str;
    }
    cout<<"Enter final States (-1 to stop): ";
    int n;
    cin>>n;
    while(n!=-1){
        final_nfa.insert(n);
        cin>>n;
    }
    return nfa;
}

void printnfa(vector<vector<set<int>>> nfa){
    cout<<left << setw(10)<<"State"<<setw(10)<<"Input"<<setw(20)<<"Final States"<<setw(10)<<"Input"<<setw(20)<<"Final States"<<endl;
    int i=0;
    for(vector<set<int>> transition:nfa){
        cout<<left<<setw(10)<<i<<setw(10)<<"a";
        
        string s="{";
        for(int num:transition[0]) s+=(to_string(num)+" ");
        s+="}";
        cout<<setw(20)<<s;

        cout<<setw(10)<<"b";
        
        s="{";
        for(int num:transition[1]) s+=(to_string(num)+" ");
        s+="}";
        cout<<setw(20)<<s<<endl;
        
        i++;
    }
    
}

void printdfa(vector<vector<set<int>>> dfa,set<set<int>> final_states){
    cout<<left << setw(20)<<"State"<<setw(10)<<"Input"<<setw(20)<<"Final States"<<setw(10)<<"Input"<<setw(20)<<"Final States"<<endl;

    for(vector<set<int>> transition:dfa){
        string s="{";
        for(int num:transition[0]) s+=(to_string(num)+" ");
        s+="}";
        cout<<setw(20)<<s;
        cout<<setw(10)<<"a";

        s="{";
        for(int num:transition[1]) s+=(to_string(num)+" ");
        s+="}";
        cout<<setw(20)<<s;

        cout<<setw(10)<<"b";

        s="{";
        for(int num:transition[2]) s+=(to_string(num)+" ");
        s+="}";
        cout<<setw(20)<<s<<endl;
        
    }
    cout<<"Initial State = 0\n";
    cout<<"Final States are : {";
    for(set<int> s:final_states){
        cout<<"{";
        for(int i:s){
            cout<<i<<" ";
        }
        cout<<"}";
    }
    cout<<"}";
}

bool isfinal(set<int> a,set<int> b){
    for(int i:a){
        if(b.find(i)!=b.end()) return true;
    }
    return false;
}

vector<vector<set<int>>> makedfa(vector<vector<set<int>>> nfa,set<int> final_nfa,set<set<int>>& final_states){
    vector<vector<set<int>>> dfa;
    queue<set<int>> states;
    set<set<int>> uni_states;
   
    set<int> s ;
    s.insert(0);
    
    states.push(s);
    while(!states.empty()){
        
        set<int> curr = states.front();
        
        uni_states.insert(curr);
       
        set<int> inputa;
        for(int i:curr){
            inputa.insert(nfa[i][0].begin(),nfa[i][0].end());
        }
       
        set<int> inputb;
        for(int i:curr){
            inputb.insert(nfa[i][1].begin(),nfa[i][1].end());
        }
       
        dfa.push_back({curr,inputa,inputb});
        
        if(uni_states.find(inputa)==uni_states.end()){
            if(isfinal(final_nfa,inputa)) final_states.insert(inputa);
            states.push(inputa);
            uni_states.insert(inputa);
        }
       
        if(uni_states.find(inputb)==uni_states.end()){
            if(isfinal(final_nfa,inputb)) final_states.insert(inputb);
            states.push(inputb);
            uni_states.insert(inputb);
        }
        states.pop();
       
    }
    return dfa;
   
}

int main()
{
    // vector<vector<set<int>>> nfa =makenfa();
    set<set<int>> final_states;
    vector<vector<set<int>>> nfa = {{{0},{1}},{{1,2},{1}},{{2},{1,2}}};
    set<int> final_nfa={2};
    printnfa(nfa);
    vector<vector<set<int>>> dfa =makedfa(nfa,final_nfa,final_states);
    printdfa(dfa,final_states);
}
