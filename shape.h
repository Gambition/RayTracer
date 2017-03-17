#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Color.hpp"
#include "Ray.hpp"
#include "Intersection.h"
#include <Math.h>

class Shape{
    private:
        Color diffuse;
        Color specular;
        Color emission;
        double shininess;
    
    public:

        Color getDiffuse();
        Color getSpecular();
        Color getEmission();

        //calculate the color for intersection position
        Color findColor(Intersection its){
            
            if(its.isHit()==false){
                return Color(0,0,0);
            }
        
            Color tempColor = Color(0,0,0);
            for(int i=0;i<scene->lights.size();i++)
            {
                vec3 eyeDirn = glm::normalize(scene->getCameraPos-its->getPos());
                vec3 lightDirn = scene->getPos();
                vec3 half0 = glm::normalize(eyeDirn+lightDirn);
                
                //lambert 
                float nDotL = dot(its->getNormal(),lightDirn);
                Color lambert = diffuse*(lights[i]->getColor())*max(nDotL,0.0);
                tempColor+=lambert;
                
                //phong
                float nDotH = dot(its->getNormal, half0) ; 
                vec4 phong = specular *(lights[i]->getColor()) * pow (max(nDotH, 0.0),shininess) ; 
                tempColor+=phong;

                //multiply by attenuation
                tempColor = tempColor * lights[i]->attenColor(its->getPos())
            }
            Color finalColor = tempColor + scene->getAmbient()+ this->emission;
            return finalColor;

        }
        double getShininess();
        Intersection isHit(Ray r);
        vec3 getNormal(vec3 input);
        
        
};

class Sphere : public Shape{
    
    private:
        vec3 center;
        double radius;
        mat4 tranformation;
        mat4 inverseM;
 
    public:
        sphere(vec3 center,double radius, Color diffuse,Color specular,Color emission,
            double shininess,mat4 m):center(center),radius(radiud),diffuse(diffuse),
            specular(specular),emission(emission),shininess(shininess), tranformation(m)
            {
                inverseM = glm::inverse(tranformation);
            }

        vec3 getNormal(vec3 input){
            vec3 normal = vec3(inverse*position)-this->center;
            normal = vec3(glm::transpose(inverseM)*(vec4(normal,0)),3);
            normal = glm::normalize(normal);

        }
        //calculate the intersection point of ray-sphere
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
            position = vec3(tranformation*position);
            vec3 normal = this->getNormal(position);

            return Intersection(position,normal,this);
        }

};

class Triangle : public Shape{

    private:
        vec3 A;
        vec3 B;
        vec3 C;
    
    public:
        triangle(vec3 a, vec3 b, vec3 c,Color diffuse, Color specular, Color emission, 
                double shininess):A(a),B(b),C(c),diffuse(diffuse),
                specular(specular),emission(emission),shininess(shiniess){}
        
        //calculate the intersection point of ray-triangle
        vec3 getNormal(vec3 input){
            return glm::normalize(glm::cross((C-A),(B-A)));
        }
        Intersection isHit(Ray r){
            vec3 normal = glm::cross((C-A),(B-A);
            normal = glm::normalize(normal);
            double t = (normal*(A-r.getPos()))/(normal*r.getDir());

            if(t<0){
                return Intersection();
            }
            vec3 position = r.getPos()+t*r.getDir();
            if( ((glm::cross((B-A),(position-A))*normal >=0) &&
                ((glm::cross((C-B),(position-B))*normal >=0) &&
                ((glm::cross((A-C),(position-C))*normal >=0))
            {
                    return Intersection(position,normal,this);
            }
            else{
                return Interseciton();
            }
        }

};

#endif
