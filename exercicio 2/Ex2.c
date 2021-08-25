// Sistema massa mola em c (Apenas lógica)
#include <stdio.h>
int main()

{

float a,v,x,time;
const float deltaT = 0.01;
const float m = 1;
const float k = 1;

const float x0 = 3;
const float v0 = 0;
const float n = 1000;

x = x0;
v = v0;

for(int i=0;i<n; i++){
a = (-k*x)/m;
v = v + a*deltaT;
x = x + v*deltaT;
time = i*deltaT;

printf("a = %f,v = %f,x = %f,time = %f\n",a,v,x,time);
}
return 0;
}