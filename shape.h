

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
                if(!(scene->lights[i]->blocked(its.getPos()))){
                  
                vec3 eyeDirn = glm::normalize(scene->getCameraPos()-its.getPos());
                
                vec3 lightDirn = scene->lights[i]->calculateDirn(its.getPos());
            
                vec3 half0 = glm::normalize(eyeDirn+lightDirn);
              
                Color lambert = diffuse*(scene->lights[i])->incidentShade(its.getPos(),its.getNormal());
                tempColor = tempColor + lambert;
                
                float nDotH = glm::dot(its.getNormal(), half0);
                
                Color phong  = specular * pow(nDotH, shininess);
               
                tempColor = tempColor+phong;
                //multiply by attenuation
                tempColor = tempColor * scene->lights[i]->attenColor(its.getPos());

                }
            }
            Color finalColor = tempColor + this->ambient+ this->emission;
            return finalColor;

        }


class Sphere : public Shape{
    
    private:
        vec3 center;
        double radius;
        mat4 transformation;
        mat4 inverseM;
 
    public:
        Sphere(vec3 c,double r, Color d,Color am,Color s,Color e,
            double shine,mat4 m)
            {
                center = c;
                radius = r;
                diffuse = d;
                ambient = am;
                specular = s;
                emission = e;
                shininess = shine;
                transformation = m;
                inverseM = glm::inverse(transformation);
            }

        vec3 getNormal(vec3 input){
            vec3 normal = vec3(inverseM * vec4(input,1))-this->center;
            normal = vec3(glm::transpose(inverseM)*(vec4(normal,0)));
            normal = glm::normalize(normal);
            return normal;
        }
       
        //calculate the intersection point of ray-sphere
        Intersection isHit(Ray r){

            Ray tr = r.transform(inverseM);
            
            float b = glm::dot((float)2*tr.getDir(),(tr.getPos()-center));
            float a = glm::dot(tr.getDir(),tr.getDir());
            float c = glm::dot((tr.getPos()-center),(tr.getPos()-center))-(float)pow(radius,2);

            float delta = pow(b,2.0)-4*a*c;
            
           // float root;
            //float root1,root2;
            if (delta < 0.0) { return Intersection() ;}
    
            float s1 = (-b + sqrt(delta))/2*a;
            float s2 = (-b - sqrt(delta))/2*a;
           
            float t;
    
            if (s1 > 0 && s2 > 0) {
                if (s1 < s2 || s1 == s2) { t = s1; } 
                else { t = s2; }
            }
            else if (s1 > 0) { t = s1; }
            else if (s2 > 0) { t = s2; }
            else { return Intersection(); }
         
            vec3 position = tr.getPos()+t*tr.getDir();
            
            position = vec3(transformation*vec4(position,1));
           
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
        Triangle(vec3 a, vec3 b, vec3 c,Color d,Color am, Color s, Color e, 
                double shine)
                {
                    A = a;
                    B = b;
                    C = c;

                    diffuse = d;
                    ambient = am;
                    specular = s;
                    emission = e;
                    shininess = shine;
                }
        
        //calculate the intersection point of ray-triangle
        vec3 getNormal(vec3 input){
            return glm::normalize(glm::cross((B-A),(C-A)));
        }

        Intersection isHit(Ray r){
     
            vec3 normal = glm::cross((B-A),(C-A));
            normal = glm::normalize(normal);
            float t = glm::dot(normal,(r.getPos()-A))/glm::dot(normal,r.getDir());
            t = -1.0*t;
            if(t<0){
                return Intersection();
            }
       
            vec3 position = r.getPos()+t*r.getDir();
        
            if( ((glm::dot(glm::cross((B-A),(position-A)), normal)) >=0) &&
                ((glm::dot(glm::cross((C-B),(position-B)), normal)) >=0) &&
                ((glm::dot(glm::cross((A-C),(position-C)), normal)) >=0))
            {
                    
                    return Intersection(position,normal,this);
            }
            else{
                return Intersection();
            }
        }

};

