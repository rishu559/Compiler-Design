
string removespace(string s)
{
    //traversing the string
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            //using in-built function to erase element
            s.erase(s.begin() + i);
            i--;
        }
    }
    return s;
}

void input_grammar(){
    // int n;
    // cout<<"Enter the number of Non-Terminals : ";
    // cin>>n;
    // cout<<"Enter the Non-Terminal symbols : ";
    // int i=0;
    // while(n--){
    //     string st;
    //     cin>>st;
    //     non_terminals[st]=i++;
    // }
    
    // cout<<"Enter the number of Terminals : ";
    // cin>>n;
    // cout<<"Enter the Terminal symbols : ";
    // i=0;
    // while(n--){
    //     string st;
    //     cin>>st;
    //     terminals[st]=i++;
    // }
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
        st = removespace(st);
        int pos = st.find("->");
        
        string left = st.substr(0,pos);
        // cout<<left<<" ";
        // cout<<pos<<" ";
        st = st.substr(pos+2);
        // cout<<st<<" ";
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
