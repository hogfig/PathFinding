#include<iostream>
#include<math.h>

using namespace std;

class UserInput{
    public:
        UserInput(Environment* env){
            environment = env;
            error_msg = " ";
            msg = " ";
            condition=true;
        }
        //SET
        void set_msg(string s){ msg = s;}
        void set_errorMsg(string s){ error_msg = s;} 
        void set_isCondition(bool(*foo)(string,Environment)){ 
            /*You pass your function that sets a condition based on the user input*/
            setCondition = foo;
        }

        //GET
        int get_usrInput(){
            do{
                cout<<msg<<endl;
                cin>>usrinput;
                condition = setCondition(usrinput,*environment);
                if(condition) cout<<endl<<error_msg<<endl;
            }while(condition);
            return str2int(usrinput);
        }
        //convert from string to int
        static int str2int(string s){
            int num=0;
            int power = s.size()-1;
            for(int i=0;i<s.size();i++){
                int t = char2int(s[i]);
                int n = char2int(s[i]) * pow(10,power);
                num+=n;
                power-=1;
            }
            return num;
        }
    private:
        Environment* environment;
        string msg;
        string error_msg;
        string usrinput;
        bool condition;
        bool (*setCondition)(string,Environment); //function pointer

        bool GridSizeCondition(string s, Environment env){
            int s_size = s.size();
            for (int i =0; i<s_size; i++){
                if(!((int)s[i]>=48 && (int)s[i]<=57)){
                    return true;
                }
            }
            return false;
        }

        //za prebacaj brojeva od 0-9
        static int char2int(char x){
            return (int)(0b0001111&(int)x);
        }
};

 