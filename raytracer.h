#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include "Color.hpp"
#include "Ray.hpp"

class RayTracer
{
    public:
     RayTracer() { }
     Color trace(Ray r, int depth);

};