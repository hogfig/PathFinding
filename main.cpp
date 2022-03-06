#include<iostream>
#include<thread>
#include<chrono>
#include<cmath>
#include <vector>
#include "environment.h"
#include "user_input.h"

using namespace std;

float Calculate_globalG(Element e1,Element e2){
    //Euclidean distance
    return (float)(sqrt( pow(abs(e1.get_x()-e2.get_x()),2) + pow(abs(e1.get_y()-e2.get_y()),2)));
}

int Calculate_localG(Element e1,Element e2){
    return abs(e1.get_x()-e2.get_x())+abs(e1.get_y()-e2.get_y());
}

void Display_ShortestPath(Element*el, Environment*map){
    while(el->get_parent()->get_parent()->get_id() != -1){
        Element *next = el->get_parent(); 
        next->set_ElChar("\x1B[31m*\033[0m");
        map->AddElement(*next);
        el = next;
        map->Refresh();
    }
}

void A_star(Element h, Element t, Environment*map){
    int neighbors_coordinates[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
    int x_cord,y_cord;
    vector<Element> Neighbors;

    h.set_GlobalGoal(Calculate_globalG(h,t));
    h.set_LocalGoal(Calculate_localG(h,t));
    Element closest_el = h;
    closest_el.set_isVisited(true);
    map->AddElement(closest_el);

    Neighbors.push_back(closest_el);

    while(closest_el.get_LocalGoal()!=0){
        for(int i=0; i<8; i++){
            x_cord = closest_el.get_x() + neighbors_coordinates[i][0];
            y_cord = closest_el.get_y() + neighbors_coordinates[i][1];
            Element n_el = map->get_element(x_cord,y_cord);

            if(!n_el.get_ocupied() && !n_el.get_isVisited()){
                Element n = Element(x_cord,y_cord,3);
                n.set_GlobalGoal(Calculate_globalG(n,t));
                n.set_LocalGoal(Calculate_localG(n,t));
                n.set_parent(map->get_element_adress(closest_el.get_x(),closest_el.get_y()));
                
                if(n.get_LocalGoal() <= 0) {
                    n.set_id(1);
                }

                Neighbors.push_back(n);
                map->AddElement(n);
            
            }
        }

        if(Neighbors.size()>=1){
            closest_el.set_isVisited(true);
            map->AddElement(closest_el); // to update isVisitate state
            Neighbors.erase(Neighbors.begin());
            sort(Neighbors.begin(),Neighbors.end());
            closest_el = Neighbors[0]; //not good
        }
        map->Refresh();
    }

    Display_ShortestPath(&closest_el, map);
}

bool CheckInput_GRIDSIZE(string s, Environment env){
    int s_size = s.size();
    for (int i =0; i<s_size; i++){
        if(!((int)s[i]>=48 && (int)s[i]<=57)){
            return true;
        }
    }
    return false;
}

bool CheckInput_ELEMENT(string s,Environment env){
    bool isNumber, isRange;
    isNumber = CheckInput_GRIDSIZE(s,env); //returns false if string contains number
    if(!isNumber){
        int num = UserInput::str2int(s);
        int gs= env.get_UsrGridSize() ;
        if(num>env.get_UsrGridSize() || num<1){
            isRange = true;
        }else{
            isRange = false;
        } 
    }
    return isRange||isNumber;
}

int main(){
    int target_pos[2];
    int hunter_pos[2];
    Environment env; //init environment

    UserInput o1(&env); //init class for user input
    o1.set_errorMsg("ERROR: input a number in the allowed range!");
    o1.set_isCondition(&CheckInput_GRIDSIZE);
    UserInput o2(&env); //init class for user input
    o2.set_errorMsg("ERROR: input a number in the allowed range!");
    o2.set_isCondition(&CheckInput_ELEMENT);

    o1.set_msg("Choose the size of the field:\n(the number 'n' that you choose wil generate a nxn field, " +to_string(env.get_MinGridsize()) + "<n<="+ to_string(env.get_MaxGridsize())+" )");
    const unsigned short int USR_GRID_SIZE = o1.get_usrInput();
    env.set_GridSize(USR_GRID_SIZE);
    env.AddObstacles();

    o2.set_msg("Choose the x coordinate of the target:\n(the coordinates must be in the range of the chosen field 0<n<="+to_string(env.get_UsrGridSize()));
    target_pos[0] = o2.get_usrInput();

    o2.set_msg("Choose the y coordinate of the target:\n(the coordinates must be in the range of the chosen field 0<n<="+to_string(env.get_UsrGridSize()));
    target_pos[1] = o2.get_usrInput();
    o2.set_msg("Choose the x coordinate of the hunter:\n(the coordinates must be in the range of the chosen field 0<n<="+to_string(env.get_UsrGridSize()));
    hunter_pos[0] = o2.get_usrInput();
    o2.set_msg("Choose the y coordinate of the hunter:\n(the coordinates must be in the range of the chosen field 0<n<="+to_string(env.get_UsrGridSize()));
    hunter_pos[1] = o2.get_usrInput();

    //BLOCK WHEN TESTING/DEBUG
    // const unsigned short int USR_GRID_SIZE = 12;
    // env.set_GridSize(USR_GRID_SIZE);
    // env.AddObstacles();
    // target_pos[0]=1;
    // target_pos[1]=1;
    // hunter_pos[0] = 12;
    // hunter_pos[1] = 12;

    // //if you want different chars for hunter,target,... set them here
    Element root = Element(-1,-1,-1);
    Element target = Element(target_pos[0],target_pos[1],1);
    Element hunter = Element(hunter_pos[0],hunter_pos[1],2);
    hunter.set_parent(&root);
    
    Element*t = &target;
    Element*h = &hunter;
    Environment*e = &env;

    e->AddElement(target);
    e->AddElement(hunter);
    e->Show();
    
    A_star(hunter,target,e);

    return 0;
}