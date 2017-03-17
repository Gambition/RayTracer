#include "Raytracer.h"

Raytracer:: Color trace(Ray r,int depth){
    typedef vector<Shape *>::iterator shape_itr;
    
    Color black = Color(0,0,0);
    
    //base case
    if(depth==0)
    {
        return black;
    }

    double closeHit = -1;
    Intersection closeIts;
    Shape*  hitShape = NULL:

    //loop throught all the shapes to determine whether
    //there is a hit. If there are multiple hits, keep updating
    //to find the closest hit.

    for (int i=0;i<scene->shapes.size();i++) {
        Intersection its = (*it)->isHit(r);
        if (its->isHit()) {
            dist = glm::distance(r.getPos(),its->getPos());
            if (closeHit < 0 || dist < closeHit) {
                closeHit = dist;
                closeIts = its;
                hitShape = shapes[i];
            }
        }
    }
        
    
    if (hitShape != NULL) {
        vec3 theNormal = hitShape->getNormal(closeIts);
        vec3 vpar = (theNormal * glm::normalize(r.getDir())) * theNormal;
        vec3 ref = glm::normalize(r.getDir() - 2*vpar);
        return hitShape->hit(closestPos) + hitShape->getSpecular() * trace(Ray(closeHit + 0.01 * ref, ref), level-1);
    }
        
    return black;
}
