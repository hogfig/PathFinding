#include <string>

class Element{
    private:
        int x;
        int y;
        int id; 
                //id: 1=target, 2=hunter, 3=search bubble, 4=obstacle, 5=border, 6=free
        Element*parent;
        bool isVisited;
        bool ocupied; //ocupied -> is the element an obstacle
        float GlobalGoal;
        int LocalGoal;
        std::string ElChar;
        std::string color;
        std::string sufix;

    void init_Color(){
            switch(id){
                case 1:
                    color = "\x1B[31m";
                break;
                case 2:
                    color = "\x1B[34m";
                break;
                case 3:
                    color = "\x1B[33m";
                break;
                case 4:
                    color = "";
                break;
                case 5:
                    color = "\x1B[35m";
                break;
                case 6:
                    color = "";
                break;
            }
        }

        void init_ElChar(){
             // init char depending on id 
            switch(id){
                case 1:
                    ElChar = color.append("T")+sufix;
                break;
                case 2:
                    ElChar = color.append("H")+sufix;
                break;
                case 3:
                    ElChar = color.append("*")+sufix;
                break;
                case 4:
                    ElChar = color.append("#")+sufix;
                break;
                case 5:
                    ElChar = color.append(".")+sufix;
                break;
                case 6:
                    ElChar = color.append(" ")+sufix;
                break;
            }
        }
        
    public:
        Element(int _x, int _y, int _id){
            x=_x;
            y=_y;
            id=_id;
            isVisited = false;
            sufix = "\033[0m";
            
            if(id == 4){
                ocupied = true;
            }else{
                ocupied = false;
            }
            init_Color();
            init_ElChar();
        }
        ~Element(){

        }
        //GET
        int get_x(){return x;}
        int get_y(){return y;}
        int get_id(){return id;}
        Element *get_parent(){return parent;}
        bool get_isVisited(){return isVisited;}
        bool get_ocupied(){return ocupied;}
        float get_GlobalGoal(){return GlobalGoal;}
        int get_LocalGoal(){return LocalGoal;}
        std::string get_ElChar(){return ElChar;}
        //SET
        void set_x(int _x){ x=_x;}
        void set_y(int _y){ y=_y;}
        void set_id(int _id){ id=_id;init_Color();init_ElChar();}
        void set_parent(Element*_parent){ parent=_parent;}
        void set_isVisited(bool _isVisited){ isVisited=_isVisited;}
        void set_ocupied(bool _ocupied){ ocupied=_ocupied;}
        void set_GlobalGoal(float _GlobalGoal){ GlobalGoal=_GlobalGoal;}
        void set_LocalGoal(int _LocalGoal){ LocalGoal=_LocalGoal;}
        void set_ElChar(std::string ch){ ElChar = ch;}
        
        bool operator < (const Element& str) const{
            return (GlobalGoal < str.GlobalGoal);
        }
};