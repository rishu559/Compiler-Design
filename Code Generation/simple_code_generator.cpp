#include<bits/stdc++.h>
using namespace std;

void generate_code(pair<string,vector<string>> opti_code){
    vector<string> registers;
    int reg_count=0;
    // for(int i=0;i<opti_code.size();i++){
        pair<string,vector<string>> p = opti_code;
        cout<<"MOV "<<"R1 "<<p.second[p.second.size()-1]<<"\n";
        registers.push_back(p.second[p.second.size()-1]);
        reg_count++;
        for(int i=p.second.size()-2;i>=1;i-=2){

            string operator1;
            if(p.second[i]=="+"){
                operator1 = "ADD";
            }
            else if(p.second[i]=="*"){
                operator1 = "MUL";
            }
            else if(p.second[i]=="-"){
                operator1 = "SUB";
            }

            reg_count++;
            registers.push_back(p.second[i-1]);
            cout<<"MOV "<<"R"<<reg_count<<" "<<p.second[i-1]<<"\n";

            registers.push_back(" ");
            reg_count++;
            cout<<operator1<<" R"<<reg_count<<" R"<<reg_count-1<<" R"<<reg_count-2<<"\n";

        }   
}

// pair<string,vector<string>> makeSingleStmt(map<string,string> mp){
//     string line;
//     ifstream myfile ("example.txt");
//     if (myfile.is_open())
//     {
//         while ( getline (myfile,line) )
//         {
//         cout << line << '\n';
//         }
//         myfile.close();
//     }
// }

int main(){
    generate_code({"id1",{"id2","+","id3","*","id4"}});
}