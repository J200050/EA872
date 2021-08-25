#include <iostream>
#include <memory>

namespace Dynamics {

/*criação de models*/

//model da dinamica do bloco
class massdynamics{
    private:
      
    public:

    float acceleration,position,velocity,mass;

    massdynamics();
    ~massdynamics();
    void set_dynamics(float accel,float pos,float vel,float m);
};
//model da dinamica da massa
class springdynamics{
    
    private:
  
    
    public:
    float springconstant;

    springdynamics();
    ~springdynamics();
   void set_dynamics(float k );
};

//model da dinamica do tempo no sistema
class timedynamics{
    
    private:
    
    
    public:
    float time, step;
    timedynamics();
    ~timedynamics();
   void set_dynamics(float t, float p );
};
/*criação de controllers*/

//controler que controla cada interação entre a massa e a mola no sitema
class interaction_spring_mass{
  
    private:
    
    massdynamics *massdy;
    springdynamics *springdy;
    timedynamics *timedy;

    public:
    interaction_spring_mass();
    ~interaction_spring_mass();
    void settings(massdynamics *m, springdynamics *s, timedynamics *t);
    void apply_step();
    
};

//construtures

massdynamics::massdynamics(){
    std::cout << "Mass created\n";
}

springdynamics::springdynamics()
{
    std::cout << " Spring created\n";
}

timedynamics::timedynamics(){
    std::cout << "Time base created\n";
}

interaction_spring_mass::interaction_spring_mass(){
    std::cout << "Interaction object created\n";
}

interaction_spring_mass::~interaction_spring_mass(){
    std::cout << "Interaction object destroyed\n";
}


// destrutores
massdynamics::~massdynamics(){
    std::cout << "Mass destroyed\n";
}

springdynamics::~springdynamics()
{
    std::cout << " Spring destroyed\n";
}

timedynamics::~timedynamics(){
    std::cout << "Time base destroyed\n";
}

//funções de set para cada modelo
void massdynamics::set_dynamics(float accel,float pos,float vel,float m){
    
    acceleration = accel;
    position = pos;
    velocity = vel;
    mass = m;
}

void springdynamics::set_dynamics(float k){
    springconstant = k;
}

void timedynamics::set_dynamics(float t,float p){
    time = t;
    step = p;
}


void interaction_spring_mass::apply_step(){
   
    massdy->acceleration = (-(springdy->springconstant)*(massdy->position))/(massdy->mass);
    massdy->velocity = (massdy->velocity) + (massdy->acceleration)*(timedy->step);
    massdy->position = (massdy->position) + (massdy->velocity)*(timedy->step);
    timedy->time = timedy->time + timedy->step;
    std::cout << " T: "<< timedy->time <<" Acell: " << massdy->acceleration << " Pos: "<< massdy->position<< " Vel: "<< massdy->velocity <<"\n";

}

 void interaction_spring_mass::settings(massdynamics *m, springdynamics *s, timedynamics *t){
    massdy = m;
    springdy = s;
    timedy = t;

 }



}



//fim da declaração de namespace e inicio do código em si


using namespace Dynamics;

int main()
{

// inicializando objetos
    massdynamics M1;
    springdynamics S1;
    timedynamics T;
    interaction_spring_mass C1;
// valores inicias dos objetos
    const float a0 = 0;
    const float x0 = 3;
    const float v0 = 0;
    const float m0 = 1;
    const float k0 = 1;
    const float t0 = 0;
    const float step = 0.01;
    
// setando os valores após inicialização dos objetos
    M1.set_dynamics(a0,x0,v0,m0);
    S1.set_dynamics(k0);
    T.set_dynamics(t0,step);
    C1.settings(&M1,&S1,&T);
    

    while(true){
        C1.apply_step();
    }

}