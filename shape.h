#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Color.hpp"
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

       /* bool hit(Ray ray);*/

};

class sphere : public shape{
    
    private:
        vec3 center;
        double radius;
 
    public:
        sphere(vec3 center,double radius, Color diffuse,Color specular,Color emission,
            double shininess):center(center),radius(radiud),diffuse(diffuse),
            specular(specular),emission(emission),shininess(shininess);

        
}

#endif