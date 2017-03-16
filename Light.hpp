#ifndef 
#define LIGHT

#include "Color.hpp"
class Light{
    private:
        Color color;
    public:
        Light(){}
        Color getColor(){
            return this->color;
        }
};

class DirecitonLight : public Light{

    private:
        vec3 position;
        
    public:
        DirecitonLight(Color c, vec3 pos){
            this->color = c;
            this->position = pos;
        }

        vec3 getPos(){ return this->position;}
          
};

class PointLight : public Light{
    
    private:
        vec3 position;
        double attenuation[3];
   
    public:
        PointLight(Color c, vec3 pos, double[] atten){
            this->color = c;
            this->position = pos;
            this->attenuation = atten;
        }

        vec3 getPos(){ return this->position;}

        Color attenColor(){
            //TODO
            //How to calculate d in attenuation????
        }
};

#endif