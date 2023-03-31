#include<bits/stdc++.h>
using namespace std;

bool isOperator(char c){
    if(c=='-'||c=='+'||c=='/'||c=='*'||c=='='){
        return true;
    }
    else return false;
}
void makeThreeAddressCode(string &str,vector<string> &vec){
    string s1 = "";
    bool flag1 = true;
    bool flag2 = false;
    char op;
    string s2="";
    for(int i=str.size()-1;i>=0;i--){
        if(flag1 && isOperator(str[i])){
            flag1 = false;
            flag2 = false;
            op = str[i];
            if(i!=0 && isOperator(str[i-1])){
                break;
            }
            else{
                flag2 = true;
            }
        }
        else if(flag1){
            s1=str[i]+s1;
        }
        else if(flag2){
            if(isOperator(str[i])) break;
            s2 =str[i]+s2;
        }
    }
    if(flag1) return;
    vec.push_back(s2+" "+op+" "+s1);
    int size = s1.size()+1+s2.size();
    str = str.substr(0,str.size()-size);
    str = str + "t" + to_string(vec.size());
    makeThreeAddressCode(str,vec);
}
void removeSpaces(string &str)
{
    int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i]; 
                                  
    str[count] = '\0';
}

int main(){
    string str;
    cout<<"Enter the expression\n";
    getline(cin,str);
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace),
        str.end());
    // removeSpaces(str);
    // cout<<str;
    vector<string> vec;
    
    makeThreeAddressCode(str,vec);
    
    cout<<"Intermediate Code:\n";
    for(int i=0;i<vec.size()-1;i++){
        cout<<"t"<<to_string(i+1)<<" = "<<vec[i]<<"\n";
    }
    cout<<vec[vec.size()-1];
}