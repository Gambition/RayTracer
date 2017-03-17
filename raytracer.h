#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.hpp"

using namespace glm;
class Sample;
class Color;
class Light;
class Shape;
class Intersection;
class Ray;
class RayTracer;

extern Scene* scene;

class Sample{
    private:
        float x,y;
    
    public:
        float getX() {return this->x;}
        float getY() {return this->y;}

};

class Color{
    private:
        float r,g,b;
    
    public:
        Color(){
            r=0.0;
            g=0.0;
            b=0.0;
        }
        Color(float r,float g,float b):
            r(r),g(g),b(b){}
        
        float getRed() {return this->r;}
        float getGreen() {return this->g;}
        float getBlue() {return this->b;}

        Color operator+(const Color& other){
            return Color(this->r + other.r,
                         this->g + other.g,
                         this->b + other.b);
        }
        
        Color operator-(const Color& other){
            return Color(this->r - other.r,
                         this->g - other.g,
                         this->b - other.b);
        }

        Color operator*(double scale){
            return Color(this->r * scale,
                         this->g * scale,
                         this->b * scale);
        }
        
        //TODO What is converstion from xyz???
};

class Light{
    private:
        Color color;
    
    public:
        Light(){
            color = Color(0,0,0);
        }

        Color getColor(){
            return this->color;
        }
    
        virtual double attenColor(vec3 pos){}
};

class Shape{
    private:
        Color diffuse;
        Color specular;
        Color emission;
        double shininess;
    
    public:
        Shape(){}
        Color getDiffuse() {return diffuse;}
        Color getSpecular() {return specular;}
        Color getEmission() {return emission;}
        double getShininess() {return shininess;}

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
                float nDotL = dot(its.getNormal(),lightDirn);
                Color lambert = diffuse*(scene->lights[i]->getColor())*max(nDotL,0.0);
                tempColor = tempColor+lambert;
                
                //phong
                float nDotH = dot(its.getNormal(), half0) ; 
                Color phong = specular *(scene->lights[i]->getColor()) * pow (max(nDotH, 0.0),shininess) ; 
                tempColor = tempColor+phong;

                //multiply by attenuation
                tempColor = tempColor * scene->lights[i]->attenColor(its.getPos())
            }
            Color finalColor = tempColor + scene->getAmbient()+ this->emission;
            return finalColor;

        }

        virtual Intersection isHit(Ray r);
        virtual vec3 getNormal(vec3 input);
        
        
};

class Intersection{
    
    private:
        vec3 position;
        vec3 normal;
        Shape* shape;
        bool hit;

    public:
        Intersection(): position(vec3(0,0,0)),normal(vec3(0,0,0)),hit(false){}
        Intersection(vec3 postion,vec3 normal, Shape *shape):
            position(position),normal(normal),shape(shape),hit(true){}

        vec3 getPos() {return position;}
        vec3 getNormal() {return normal;}
        Shape* getShape() {return shape;}
        bool isHit() {return hit;} 

};

class Ray{
    private:
        vec3 position;
        vec3 direction;
        float t_min,t_max;
    
    public:
        Ray(const vec3 pos,const vec3 dir,float t_min, float t_max):
            position(pos),direction(dir),t_min(t_min),t_max(t_max){}
        
        Ray(const vec3 pos,const vec3 dir):
            position(pos),direction(dir){}
        
        vec3 getPos(){
            return this->position;
        }
        
        vec3 getDir(){
            return this->direction;
        }
};

class RayTracer
{
     public:
     RayTracer() { }
     Color trace(Ray r, int depth){}
};

#endif