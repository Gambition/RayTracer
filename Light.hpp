#ifndef 
#define LIGHT

#include "Color.hpp"
#include <Math.h>

class Light{
    private:
        Color color;
    public:
        Light(){}
        Color getColor(){
            return this->color;
        }
        
        double attenColor(vec3 pos){}
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
        
        //no attenuation for directional light
        double attenColor(vec3 pos){
            return 1;
        }
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

        double attenColor(vec3 pos){
            double dist = glm::distance(this->position,pos);
            double atten = attenuation[0]+attenuation[1]*dist+
                           attenuation[2]*pow(dist,2);
            return 1/atten;
        }
};

#endif