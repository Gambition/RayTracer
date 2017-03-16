#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "sample.h"
#include "Ray.hpp"
#include <math.h>

class camera{
    private:
        vec3 w;
        vec3 u;
        vec3 v;
        double fovx,fovy;
    
    public:
        camera(vec3 pos,vec3 up,vec3 lookat,
                double sceneFovy,int height,int width){
            w = glm::normalize(pos-lookat);
            u = glm::normalize(glm::cross(w,up));
            v = glm::cross(w,u);
            fovy = sceneFovy*M_PI/180.0;
            double z = tan(fovy/2);
            z = (1/z)*height/2;
            fovx = 2*atan((width/2)/z);
        }

        Ray generateRay(sample pixel){
            
            vec3 origin = scene->getCameraPos();
            int height = scene->getHeight();
            int width = scene->getWidth();
            double tempY = (pixel.y-width/2)/(width/2);
            double alpha = (tan(fovx/2))*tempY;
            double tempX = ((height/2)-pixel->x)/(height/2);
            double beta = (tan(fovy/2))*tempX;
            vec3 direciton = alpha*(this->u)+beta*(this->v)-w;
            direction = glm::normalize(direction);
            return Ray(origin,direction);
        }
};

