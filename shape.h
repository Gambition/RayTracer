

#include "Raytracer.h"
#include <Math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

   Color Shape::findColor(Intersection its){
            
            if(its.isHit()==false){
                return Color(0,0,0);
            }
        
            Color tempColor = Color(0,0,0);
            for(int i=0;i<scene->lights.size();i++)
            {
                vec3 eyeDirn = glm::normalize(scene->getCameraPos()-its.getPos());
                vec3 lightDirn = glm::normalize(scene->lights[i]->getPos());
                vec3 half0 = glm::normalize(eyeDirn+lightDirn);
                
                //lambert 
                float nDotL = dot(its.getNormal(),lightDirn);
                Color lambert = diffuse*(scene->lights[i]->getColor())*glm::max(nDotL,(float)0.0);
                tempColor = tempColor+lambert;
                
                //phong
                float nDotH = dot(its.getNormal(), half0) ; 
                Color phong = specular *(scene->lights[i]->getColor()) * pow (glm::max(nDotH,(float)0.0),shininess) ; 
                tempColor = tempColor+phong;

                //multiply by attenuation
                tempColor = tempColor * scene->lights[i]->attenColor(its.getPos());
            }
            Color finalColor = tempColor + scene->getAmbient()+ this->emission;
            return finalColor;

        }


class Sphere : public Shape{
    
    private:
        vec3 center;
        double radius;
        mat4 transformation;
        mat4 inverseM;
 
    public:
        Sphere(vec3 c,double r, Color d,Color s,Color e,
            double shine,mat4 m)
            {
                center = c;
                radius = r;
                diffuse = d;
                emission = e;
                shininess = shine;
                transformation = m;
                inverseM = glm::inverse(transformation);
            }

        vec3 getNormal(vec3 input){
            vec3 normal = vec3(inverseM * vec4(input,0))-this->center;
            normal = vec3(glm::transpose(inverseM)*(vec4(normal,0)));
            normal = glm::normalize(normal);
            return normal;
        }
        //calculate the intersection point of ray-sphere
        Intersection isHit(Ray r){
            float b = glm::dot(r.getPos(),(r.getDir()-center));
            float a = glm::dot(r.getDir(),r.getDir());
            float c = glm::dot((r.getPos()-center),(r.getPos()-center))-(float)pow(radius,2);

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
            position = vec3(transformation*vec4(position,0));
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
        Triangle(vec3 a, vec3 b, vec3 c,Color d, Color s, Color e, 
                double shine)
                {
                    A = a;
                    B = b;
                    C = c;
                    diffuse = d;
                    specular = s;
                    emission = e;
                    shininess = shine;
                }
        
        //calculate the intersection point of ray-triangle
        vec3 getNormal(vec3 input){
            return glm::normalize(glm::cross((C-A),(B-A)));
        }

        Intersection isHit(Ray r){
            vec3 normal = glm::cross((C-A),(B-A));
            normal = glm::normalize(normal);
            float t = glm::dot(normal,(A-r.getPos()))/glm::dot(normal,r.getDir());

            if(t<0){
                return Intersection();
            }
            vec3 position = r.getPos()+t*r.getDir();
            if( (glm::dot(glm::cross((B-A),(position-A)), normal) >=0) &&
                (glm::dot(glm::cross((C-B),(position-B)), normal) >=0) &&
                (glm::dot(glm::cross((A-C),(position-C)), normal) >=0))
            {
                    return Intersection(position,normal,this);
            }
            else{
                return Intersection();
            }
        }

};

