
#include "Color.hpp"
#include "Raytracer.h"
#include <Math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

class DirectionLight : public Light{

    private:
        vec3 position;
        
    public:
        DirectionLight(Color c, vec3 pos){
            color = c;
            position = pos;
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
        double* attenuation;
   
    public:
        PointLight(Color c, vec3 pos, double* atten){
            color = c;
            position = pos;
            attenuation = atten;
        }

        vec3 getPos(){ return this->position;}

        double attenColor(vec3 pos){
            double dist = glm::distance(this->position,pos);
            double atten = attenuation[0]+attenuation[1]*dist+
                           attenuation[2]*pow(dist,2);
            return 1/atten;
        }
};
