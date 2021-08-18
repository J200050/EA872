#include <iostream>
namespace SpaceFunc {

class coord {
    private:
        int  x,y;
    public: 
        coord();
        ~coord();
        void new_coord(int new_x, int new_y); 
};

class cube {
    private:
        int  x,y,z, volume;
    public: 
         cube();
        ~cube();
        void new_cube(int new_x, int new_y, int new_z); 
        void print_volume();
};

cube::cube(){
     std::cout << "Cubo criado\n";
}
cube::~cube(){
     std::cout << "objeto finalizado\n";
}

coord::coord()
{
    std::cout << "cordenada criada\n";

}

coord::~coord()
{
    std::cout << "cordenada finalizada\n";

}


void coord::new_coord(int new_x, int new_y){
    x = new_x;
    y = new_y;

}


void cube::new_cube(int new_x, int new_y,int new_z){
    x = new_x;
    y = new_y;
    z = new_z;

}
void cube::print_volume(){
   //using namespace cube;
    volume = x*y*z;
    std::cout <<" O volume do cubo eh de "<< volume <<"\n";

}

} 


using namespace SpaceFunc;

int main(){
    coord c1;
    cube c2;
    c1.new_coord(50,10);
    c2.new_cube(10,20,30);
    c2.print_volume();

    return 0;
}

