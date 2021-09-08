#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace Dynamics {

/*criação de models*/

//model da dinamica do bloco
class massdynamics{
    private:
      
    public:

    float acceleration,position,velocity,mass;
    const char *mass_texture;

    massdynamics();
    ~massdynamics();
    void set_dynamics(float accel,float pos,float vel,float m);
    void set_texture( const char *file);
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
    const char *background_texture;
    timedynamics();
    ~timedynamics();
    void set_dynamics(float t, float p );
    void set_texture( const char *file);
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

/*criação de viewer*/

class viewer_spring_mass{
    private:
    massdynamics *massdy;
    springdynamics *springdy;
    timedynamics *timedy;


    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    

    SDL_Window* window = nullptr;    
    SDL_Renderer *renderer;

    SDL_Texture *texture;
    SDL_Texture *texture1;
   
    bool rodando;
    SDL_Rect target;

    SDL_Event evento; 

    public:
    viewer_spring_mass();
    ~viewer_spring_mass();
    
   
    int create_visual_config();
    void config_Texture();
    void settings(massdynamics *m, springdynamics *s, timedynamics *t);
    void apply_view();

};

//construtures

massdynamics::massdynamics(){
    std::cout << "Mass created\n";
}

springdynamics::springdynamics(){
    std::cout << " Spring created\n";
}

timedynamics::timedynamics(){
    std::cout << "Time base created\n";
}

interaction_spring_mass::interaction_spring_mass(){
    std::cout << "Interaction object created\n";
}

viewer_spring_mass::viewer_spring_mass(){
     std::cout << "viewer object created\n";
}


// destrutores
massdynamics::~massdynamics(){
    std::cout << "Mass destroyed\n";
}

springdynamics::~springdynamics(){
    std::cout << " Spring destroyed\n";
}

timedynamics::~timedynamics(){
    std::cout << "Time base destroyed\n";
}

interaction_spring_mass::~interaction_spring_mass(){
    std::cout << "Interaction object destroyed\n";
}

viewer_spring_mass::~viewer_spring_mass(){
     std::cout << "viewer object destroyed\n";
}

//funções de set para cada modelo
void massdynamics::set_dynamics(float accel,float pos,float vel,float m){
    
    acceleration = accel;
    position = pos;
    velocity = vel;
    mass = m;
}


void massdynamics::set_texture(const char *file){
    
    mass_texture= file;

}


void springdynamics::set_dynamics(float k){
    springconstant = k;
}



void timedynamics::set_dynamics(float t,float p){
    time = t;
    step = p;
}


void timedynamics::set_texture(const char *file){
    
    background_texture = file;

}


void interaction_spring_mass::apply_step(){
   
    massdy->acceleration = (-(springdy->springconstant)*(massdy->position))/(massdy->mass);
    massdy->velocity = (massdy->velocity) + (massdy->acceleration)*(timedy->step);
    massdy->position = (massdy->position) + (massdy->velocity)*(timedy->step);
    timedy->time = timedy->time + timedy->step;
    //std::cout << " T: "<< timedy->time <<" Acell: " << massdy->acceleration << " Pos: "<< massdy->position<< " Vel: "<< massdy->velocity <<"\n";

}

 void interaction_spring_mass::settings(massdynamics *m, springdynamics *s, timedynamics *t){
    massdy = m;
    springdy = s;
    timedy = t;

 }

 void viewer_spring_mass::settings(massdynamics *m, springdynamics *s, timedynamics *t){
    massdy = m;
    springdy = s;
    timedy = t;
 
}

void viewer_spring_mass::apply_view(){
    
    target.x = massdy->position;

    while (SDL_PollEvent(&evento)) {
      if (evento.type == SDL_QUIT) {
        rodando = false;
      }
      // Exemplos de outros eventos.
      // Que outros eventos poderiamos ter e que sao uteis?
      //if (evento.type == SDL_KEYDOWN) {
      //}
      //if (evento.type == SDL_MOUSEBUTTONDOWN) {
      //}
    }

    // Desenhar a cena
    SDL_RenderClear(renderer);
    
    SDL_RenderCopy(renderer, texture1, nullptr, nullptr);
    SDL_RenderCopy(renderer, texture, nullptr, &target);
    
    SDL_RenderPresent(renderer);

    // Delay para diminuir o framerate
    SDL_Delay(10);
    std::cout << " T: "<< timedy->time <<" Acell: " << massdy->acceleration << " Pos: "<< massdy->position<< " Vel: "<< massdy->velocity <<"\n";   
}


int viewer_spring_mass::create_visual_config(){
    if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
        std::cout << SDL_GetError();
        return 1;
    }

    window = SDL_CreateWindow("Demonstracao do SDL2",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (window==nullptr) { // Em caso de erro...
        std::cout << SDL_GetError();
        SDL_Quit();
        return 1;
    }




    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  
    if (renderer==nullptr) { // Em caso de erro...
        SDL_DestroyWindow(window);
        std::cout << SDL_GetError();
        SDL_Quit();
        return 1;
    }
  

  // Carregando texturas
  // personagem
    texture = IMG_LoadTexture(renderer,massdy->mass_texture);
  // fundo
    texture1 = IMG_LoadTexture(renderer, timedy->background_texture);



  // Quadrado onde a textura sera desenhada
  target.x = 0;
  target.y = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, &target.w, &target.h);

  // Controlador:
    rodando = true;

  // Variaveis para verificar eventos
  SDL_Event evento; // eventos discretos
  const Uint8* state = SDL_GetKeyboardState(nullptr); // estado do teclado

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
    viewer_spring_mass V1;

// valores inicias dos objetos
    const float a0 = 0;
    const float x0 = 200;
    const float v0 = 0;
    const float m0 = 1;
    const float k0 = 1;
    const float t0 = 0;
    const float step = 0.01;
    
// setando os valores após inicialização dos objetos
    M1.set_dynamics(a0,x0,v0,m0);
    M1.set_texture ("./capi.png");
    S1.set_dynamics(k0);

    T.set_dynamics(t0,step);
    T.set_texture("./park.jpeg");

    C1.settings(&M1,&S1,&T);
    V1.settings(&M1,&S1,&T);

    V1.create_visual_config();
    

    while(true){
        C1.apply_step();
        V1.apply_view();
    }

}