#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Raytracer.h"
#include "Scene.hpp"
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
    private:
        vec3 w;
        vec3 u;
        vec3 v;
        double fovx,fovy;
    
    public:
        Camera(){
            w = glm::normalize(scene->getCameraPos()-scene->getCameraLookAt());
            u = glm::normalize(glm::cross(w,scene->getCameraUp()));
            v = glm::cross(w,u);
            fovy = scene->getFovy()*M_PI/180.0;
            double z = tan(fovy/2);
            z = (1/z)*scene->getHeight()/2;
            fovx = 2*atan((scene->getWidth()/2)/z);

        }

        Ray generateRay(Sample pixel){            
            vec3 origin = scene->getCameraPos();
            int height = scene->getHeight();
            int width = scene->getWidth();
            double tempY = (pixel.getY()-width/2)/(width/2);
            double alpha = (tan(fovx/2))*tempY;
            double tempX = ((height/2)-pixel.getX())/(height/2);
            double beta = (tan(fovy/2))*tempX;
            vec3 direction = (float)alpha*(this->u)+(float)beta*(this->v)-w;
            direction = glm::normalize(direction);
            return Ray(origin,direction);
        }
};

#endif

