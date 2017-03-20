#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <stack>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Transform.h"
#include <Math.h>

using namespace std;
using namespace glm;
class Sample;
class Ray;
class Scene;
class Shape;

class Camera;
class Color;
class Film;
class RayTracer;
class Intersect;


extern Scene* scene;

class Sample{
    private:
        int xPos,yPos;
    
    public:
        Sample(int x,int y){
            xPos = x;
            yPos = y;
        }
        int getX() {return this->xPos;}
        int getY() {return this->yPos;}

};

class Intersection{
    
    private:
        vec3 position;
        vec3 normal;
        Shape* shape;
        bool hit;

    public:
        Intersection(): position(vec3(0,0,0)),normal(vec3(0,0,0)),hit(false){}
        Intersection(vec3 pos,vec3 normal, Shape *shape):
            position(pos),normal(normal),shape(shape),hit(true){}

        vec3 getPos() {return position;}
        vec3 getNormal() {return normal;}
        Shape* getShape() {return shape;}
        bool isHit() {return hit;} 

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
    
        Color operator*(const Color &other) const{
            return Color(this->r * other.r,
                         this->g * other.g,
                         this->b * other.b);
        }

        Color operator*(double scale){
            return Color(this->r * scale,
                         this->g * scale,
                         this->b * scale);
        }
        
        //TODO What is converstion from xyz???
};

class Light{
    protected:
        Color color;
    
    public:
        Light(){
            color = Color(0,0,0);
        }

        Color getColor(){
            return this->color;
        }
        
        virtual vec3 getPos(){
            return vec3(0,0,0);
        }
        virtual double attenColor(vec3 pos){
            return (double)1;
        };
    
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

class Shape{
    protected:
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
        Color findColor(Intersection its);
        
        virtual Intersection isHit(Ray r)
        {
            return Intersection();
        };
        virtual vec3 getNormal(vec3 input)
        {
            return vec3(0,0,0);
        };
        
        
};



class Scene
{
    private:
        int width, height;
        vec3 cameraPos;
        vec3 cameraUp;
        vec3 cameraLookAt;
        int fovy;
        //Color attenuation;
        Color ambient;
        Color diffuse;
        Color emission;
        Color specular;
        double shininess;
        double attenuation[3];
        vector<vec3> vertices;
        string outputFile;
        int maxdepth;
       
        Camera *camera;
        Film *film;
        RayTracer* rt;

    public:
        vector<Light*> lights;
        
        vector<Shape*> shapes;
        
        Scene();
    
        int getWidth(){ return this->width;}
        
        int getHeight(){ return this->height;}

        int getFovy(){ return this->fovy; }
       
        vec3 getCameraPos(){ return this->cameraPos;}

        vec3 getCameraUp(){ return this->cameraUp;}

        vec3 getCameraLookAt(){ return this->cameraLookAt;}
        
        Color getAmbient(){ return this->ambient;}

        Color getiDiffuse(){ return this->diffuse;}

        Color getSpecular(){ return this->specular;}

        vector<Shape*> getShapes() { return this->shapes;} 

        int getMaxDepth() { return this->maxdepth;}

        bool generateSample(Sample* pixel);

        void rightmultiply(const mat4 & M, stack<mat4> &transfstack);
        
        void readFile(char* filename);

        void init();

        void Render();
};

class Camera{
    private:
        vec3 w;
        vec3 u;
        vec3 v;
        double fovx,fovy;
    
    public:
        Camera();

        Ray generateRay(Sample pixel);
};

class Film{
    private:
        std::vector< vector<Color> > pixels;
    public:
        Film();
        
        void commit(Sample& sample,Color& color);

        void writeImage(string path);

};



class RayTracer
{
     public:
     RayTracer(){}
     Color trace(Ray r, int depth);
};

#endif