
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
        float incidentShade(vec3 i, vec3 normal)
        {
            vec3 shadowray = position;
            shadowray = glm::normalize(shadowray);
            float colour = glm::dot(shadowray,normal);
            if(colour<=0.0) return 0;
            return colour;
        }

        vec3 calculateDirn(vec3 mypos){
            return glm::normalize(this->position);
        }
        virtual vec3 getPos(){ return this->position;}
        
        bool blocked(vec3 input){
            vec3 direction  = glm::normalize(position);
            Ray r = Ray(input,direction);
            float its = scene->getRayTracer()->closestHit(r);
            if(its<0.0){
                return false;
            }
            else{
                return true;
            }

        }
        //no attenuation for directional light
        virtual double attenColor(vec3 pos){
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

        vec3 calculateDirn(vec3 mypos){
            return glm::normalize((this->position)-mypos);
        }

        float incidentShade(vec3 i, vec3 normal) {
            vec3 shadowray = position-i;
      
            shadowray = glm::normalize(shadowray);
            float colour = glm::dot(shadowray,normal);
           
            if (colour <= 0.0) return 0;
            return colour;
        } 
        
        bool blocked(vec3 input) {
	        vec3 direction = glm::normalize(position-input);
            
  	        Ray r = Ray(input+(float)0.3*direction, direction);
	        float its = scene->getRayTracer()->closestHit(r);
           // cout<<its<<endl;
            if(its<0.0)
            {
                return false;
            }
            float dist = glm::length(input-position);
            if(its<dist)
            {
                return true;
            }
            else{
                return false;
            }

         }

        virtual vec3 getPos(){ return this->position;}

        virtual double attenColor(vec3 pos){
            double dist = glm::distance(this->position,pos);
            double atten = attenuation[0]+attenuation[1]*dist+
                           attenuation[2]*pow(dist,2);
            return 1/atten;
        }
};
