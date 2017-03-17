#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

class Intersection{
    private:
        vec3 position;
        vec3 normal;
        Shape* shape;
        bool hit;

    public:
        Intersection(): pos(vec3(0,0,0,)),normal(vec3(0,0,0)),hit(false)){}
        Intersection(vec3 postion,vec3 normal, Shape *shape):
            position(position),normal(normal),shape(shape),hit(true){}

        vec3 getPos() {return pos;}
        vec3 getNormal() {return normal;}
        Shape* getShape() {return shape;}
        bool isHit() {return hit;} 

}