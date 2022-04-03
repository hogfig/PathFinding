#include<iostream>
#include<thread>
#include<chrono>
#include<cmath>
#include <vector>
#include "element.h"
using namespace std;

class Environment{
    /*
        sets the environment where the elemts will be displayed
    */
    private:
        unsigned short int GRID_SIZE;
        unsigned short int USER_GRID_SIZE;
        uint8_t min_gridsize;
        uint8_t max_gridsize;
        vector<vector< Element > > field;
        vector<vector< Element > > *field_prt;
        int padding;
        float obstacle_thresh;
        
        void PopulateField(){
            //populate field
            for(int i=0; i<GRID_SIZE; i++){
                field.push_back(std::vector<Element>());
                for(int j=0; j<GRID_SIZE; j++){
                    //draw contour of field
                    if(i==0||i==GRID_SIZE-1||j==0||j==GRID_SIZE-1){
                        Element el = Element(j,i,5);
                        el.set_ocupied(true);
                        field[i].push_back(el);
                    }else{
                        Element el = Element(j,GRID_SIZE-i-1,6);
                        el.set_GlobalGoal(INFINITY);
                        el.set_LocalGoal(INFINITY);
                        field[i].push_back(el);    
                    }
                }
            }
            field_prt = &field;
        }
        float RandomNumber(){
            return (float) rand()/RAND_MAX ;
        }
    public:
        Environment(){
            min_gridsize=10;
            max_gridsize=100;
            padding=2;
            obstacle_thresh=0.7;
            GRID_SIZE = 1;
        }
        ~Environment(){}
        void Show(){
            //display field
            for(int i=0;i<GRID_SIZE;i++){
                for(int j=0;j<GRID_SIZE;j++){
                    cout << field[i][j].get_ElChar()<< ' ';
                }
                cout<<endl;
            }
        }
        
        void AddElement(Element el){
            //Adds differend char to field based on Element id
            field[GRID_SIZE-el.get_y()-1][el.get_x()] = el;
        }

        void AddObstacles(){
            if(GRID_SIZE==1){               
                cout<<"ERROR:Grid size not defined\n";
            }else{
                //for each element generate number, if biger than threshold make an obstacle
                for(int i=0;i<GRID_SIZE;i++){
                    for(int j=0;j<GRID_SIZE;j++){
                        float r = RandomNumber();
                        if(r>obstacle_thresh && field[i][j].get_id()==6){
                            Element e = Element(GRID_SIZE-i-1,j,4);
                            field[i][j] = e;
                        }
                    }
                }
            } 
        }

        void RemoveElement(Element el){
            Element free_el = Element(el.get_x(),el.get_y(),6);
            field[GRID_SIZE-el.get_y()][el.get_x()] = free_el;
        }

        void Refresh(int refresh_rate=500){
            this_thread::sleep_for(chrono::milliseconds(refresh_rate));
            //check if windows machine?
            #ifdef _WIN32
                system("CLS");
            #else
                system("clear");
            #endif
            this->Show();
        }

        //GET
        int get_UsrGridSize(){ return USER_GRID_SIZE;}
        int get_MinGridsize(){return min_gridsize;}
        int get_MaxGridsize(){return max_gridsize;}
        //Element get_element(int x, int y){return field[GRID_SIZE-y-1][x];}
        Element* get_element(int x, int y){ return &(*field_prt)[GRID_SIZE-y-1][x];}
        //SET
        void set_MinGridsize(uint8_t size){ min_gridsize=size;}
        void set_ObstacleThresh(float n){ obstacle_thresh=n;}
        void set_MaxGridsize(uint8_t size){ max_gridsize=size;}
        void set_GridSize(int size){
            //set GRID_SIZE in the allowed range
            if(size< min_gridsize){
                USER_GRID_SIZE = min_gridsize;
                GRID_SIZE=min_gridsize+padding;
            }else if(size>max_gridsize){
                USER_GRID_SIZE=max_gridsize;
                GRID_SIZE=max_gridsize+padding;
            }else{
                GRID_SIZE=size+padding;
                USER_GRID_SIZE = size;
            }
            PopulateField();
        }
};