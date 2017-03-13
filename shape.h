#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Color.hpp"
#include "Ray.hpp"
#include "Intersection.h"
#include <Math.h>

class shape{
    private:
        Color diffuse;
        Color specular;
        Color emission;
        double shininess;
    
    public:

        Color getDiffuse();
        Color getSpecular();
        Color getEmission();
        double getShininess();
        Intersection isHit(Ray r);
        
};

class sphere : public shape{
    
    private:
        vec3 center;
        double radius;
 
    public:
        sphere(vec3 center,double radius, Color diffuse,Color specular,Color emission,
            double shininess):center(center),radius(radiud),diffuse(diffuse),
            specular(specular),emission(emission),shininess(shininess){}

        Intersection isHit(Ray r){
            double b = r.getPos()*(r.getDir()-center);
            double a = r.getDir()*r.getDir();
            double c = (r.getPos()-center)*(r.getPos()-center)-pow(radius,2);

            double delta = pow(b,2)-4*a*c;

            if(delta<0){
                return Intersection();
            }
            else if(delta==0){
                double root = (-b)/2*a;
            }
            else {
                double root1 = (-b+sqrt(delta))/(2*a);
                double root2 = (-b+sqrt(delta))/(2*a);
            }

            double t;
            if(root1>0 && root2>0)
            {
                if(root1<=root2){
                    t = root2;
                }
                else{
                    t = root1;
                }
            }
            else if(root1>0 && root2<0){
                t = root1;
            }
            else if(root2>0 && root1<0){
                t = root2;
            }
            else{
                return Intersection();
            }

            vec3 postion = r.getPos()+t*r.getDir();
            vec3 normal

            return Intersection(position,normal,this);
        }

};

class triangle : public shape{

    private:
        vec3 A;
        vec3 B;
        vec3 C;
    
    public:
        triangle(vec3 a, vec3 b, vec3 c,Color diffuse, Color specular, Color emission, 
                double shininess):A(a),B(b),C(c),diffuse(diffuse),
                specular(specular),emission(emission),shininess(shiniess){}
        
        Intersection isHit(Ray r){
            vec3 normal = glm::cross((C-A),(B-A));
            normal = glm::normalize(normal);
            double t = (normal*(A-r.getPos()))/(normal*r.getDir());

            if(t<0){
                return Intersection();
            }
            vec3 position = r.getPos()+t*r.getDir();
            if( ((glm::cross(B-A),(position-A))*normal >=0) &&
                ((glm::cross(C-B),(position-B))*normal >=0) &&
                ((glm::cross(A-C),(position-C))*normal >=0))
            {
                    return Intersection(position,normal,this);
            }
            else{
                return Interseciton();
            }
        }

};
