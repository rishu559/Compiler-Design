#include <bits/stdc++.h>

using namespace std;

class node{
public:
	map<char,vector<node*>> input;
};

vector<node*> node_tracker;

int prec(char c){
	if(c=='*' || c=='+'){
		return 3;
	}else if(c=='.'){
		return 2;
	}else if(c=='|'){
		return 1;
	}else{
		return -1;
	}
}

string preprocess(string &s){
    string ns = "";
    for(int i=0;i<s.size();i++){
        char c = s[i];
        if(c=='+'){
            string str = "";
            if(s[i-1]==')'){
                for(int j=i-1;s[j]!='(';j--){
                    str = s[j]+str;
                }
                str = "("+str;
            }
            else{
                str +=s[i-1];
            }
            s = s.substr(0,i)+"."+str+"*"+s.substr(i+1);
            
        }
    }
    cout<<"PreProcessed RE:"<<s<<"\n";
    return s;
    
}

string post(string s) 
{ 
    stack<char> st; 
    st.push('N'); 
    int l = s.length(); 
    string ns; 
    for(int i = 0; i < l; i++) 
    {
        if((s[i] >= 'a' && s[i] <= 'z')||(s[i] >= 'A' && s[i] <= 'Z')){
	        ns+=s[i]; 
        }

        else if(s[i] == '('){          
	        st.push('('); 
        }
        else if(s[i] == ')') 
        { 
            while(st.top() != 'N' && st.top() != '(') 
            { 
                char c = st.top(); 
                st.pop(); 
               ns += c; 
            } 
            if(st.top() == '(') 
            { 
                char c = st.top(); 
                st.pop(); 
            } 
        } 
        else{ 
            while(st.top() != 'N' && prec(s[i]) <= prec(st.top())) 
            { 
                char c = st.top(); 
                st.pop(); 
                ns += c; 
            } 
            st.push(s[i]); 
        } 
  
    } 
    while(st.top() != 'N') 
    { 
        char c = st.top(); 
        st.pop(); 
        ns += c; 
    } 
return ns;
}

void printnode(vector<node*> node_tracker,vector<vector<node*>> st){
	cout<<"___________________________________________"<<endl;
	cout<<"| from state\t| input\t| tostates"<<endl;
	
	map<node*,int> mp;
	for(int i=0;i<node_tracker.size();i++){
	    mp[node_tracker[i]]=i;
	}
	int num =0;
	
	for(int i=0;i<node_tracker.size();i++){
		
		
		for(auto transition:node_tracker[i]->input){
		    cout<<"| "<<i<<"          \t|";
		    cout<<transition.first<<" \t|";
		    for(node* temp:transition.second){
		        cout<<mp[temp]<<" ";
		    }
		    cout<<"\n";
		}
	}
	cout<<"starting node is ";
	cout<<mp[st[0][0]]<<endl;
	cout<<"ending node is ";
	cout<<mp[st[0][1]]<<endl;
}



vector<node*> makenode(char in){
	node* a = new node;
	node* b = new node;
	node_tracker.push_back(a);
	node_tracker.push_back(b);

	a->input[in].push_back(b);

	return {a,b};
}

void andd(vector<vector<node*> > &st){

	node* first = st[st.size()-2][1];
	node* last = st[st.size()-1][0];
	
	first->input['e'].push_back(last);
	
	first = st[st.size()-2][0];
	last = st[st.size()-1][1];
	
	st.pop_back();
	st.pop_back();
	
	st.push_back({first,last});

	
}

void orr(vector<vector<node*> > &st){
	
	node* start = new node;
	node_tracker.push_back(start);
	start->input['e'].push_back(st[st.size()-2][0]);
	start->input['e'].push_back(st[st.size()-1][0]);
	
	node* end = new node;
	node_tracker.push_back(end);
	st[st.size()-1][1]->input['e'].push_back(end);
	st[st.size()-2][1]->input['e'].push_back(end);

	st.pop_back();
	st.pop_back();

    st.push_back({start,end});

}

void closure(vector<vector<node*> > &st){
	
	node* start = new node;
	node* end = new node;
	node_tracker.push_back(start);
	node_tracker.push_back(end);
	
	start->input['e'].push_back(st[st.size()-1][0]);
	start->input['e'].push_back(end);
	
	st[st.size()-1][1]->input['e'].push_back(st[st.size()-1][0]);
	st[st.size()-1][1]->input['e'].push_back(end);
	
	st.pop_back();
	st.push_back({start,end});
	
}

int main(){
	string in;
	cout<<"Enter a regular expression\n";
	cin>>in;
	string o;
	in = preprocess(in);
	o = post(in);
	cout<<"\npostfix expression is "<< o<<endl;
	vector<vector<node*>> st;

	for(int l =0 ;l<o.length();l++){
		if(o[l] !='|' && o[l]!='*' && o[l]!='.' && o[l]!='+'){
			vector<node*> temp = makenode(o[l]);
			st.push_back(temp);
		}
		else if(o[l]=='.'){
			andd(st);
		}
		else if(o[l]=='|'){
			orr(st);
		}
		else if(o[l]=='*'){
			closure(st);
		}
		else if(o[l]=='+'){
			vector<node*> temp = st[st.size()-1];
			closure(st);
			st.push_back(temp);
			andd(st);
		}
		
	}
	cout<<"\ntrainsition table for given regular expression is - \n";
	printnode(node_tracker,st);
	cout<<endl;
	
	return 0;
}
