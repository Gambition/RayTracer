

#include "Raytracer.h"
#include <Math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Sphere : public Shape{
    
    private:
        vec3 center;
        double radius;
        mat4 tranformation;
        mat4 inverseM;
 
    public:
        Sphere(vec3 center,double radius, Color diffuse,Color specular,Color emission,
            double shininess,mat4 m):center(center),radius(radius),diffuse(diffuse),
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
            float b = r.getPos()*(r.getDir()-center);
            float a = r.getDir()*r.getDir();
            float c = (r.getPos()-center)*(r.getPos()-center)-pow(radius,2);

            float delta = pow(b,2)-4*a*c;
            float root;
            float root1,root2;
            
            if(delta<0){
                return Intersection();
            }
            else if(delta==0){
                root = (-b)/2*a;
            }
            else {
                root1 = (-b+sqrt(delta))/(2*a);
                root2 = (-b+sqrt(delta))/(2*a);
            }

            float t;
            
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

            vec3 position = r.getPos()+t*r.getDir();
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

