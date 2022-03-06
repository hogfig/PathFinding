#include <iostream>
#include <string>
#include <vector>
#include"element.h"
using namespace std;


int main(){
    int GRID_SIZE = 10;
    vector<vector< Element > > field;
    vector<vector< Element > > * field_ptr;

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
                field[i].push_back(el);    
            }
        }
    }
    int a=2;
    int*b=&a;

    field_ptr=&field;

    field[0][0].set_id(9);
    cout<< &(*field_ptr)[0][0] <<" "<< &field[0][0]<<endl;
    //cout<< b<<" "<< &a<<endl;

    return 0;
}