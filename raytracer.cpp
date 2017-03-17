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

    Color RayTracer::trace(Ray r, int level)
    {
        Color black = Color(0, 0, 0);
        
        if (level == 0) return black;
        
        shape_itr it = scene->getShapes()->begin();
        shape_itr end = scene->getShapes()->end();
        
        vec3 pos;
        double dist;
        double closestDist = -1;
        vec3 closestPos;
        Shape *closestShape = NULL;
        
        for ( ; it != end; it ++) {
            pos = (*it)->intersect(r);
            if (pos != NULL) {
                dist = (r.getPos() - pos).length();
                if (closestDist < 0 || dist < closestDist) {
                    closestDist = dist;
                    closestPos = pos;
                    closestShape = *it;
                }
            }
        }
        
        if (closestShape != NULL) {
            vec3 theNormal = closestShape->calculateNormal(closestPos);
            vec3 vpar = (theNormal * r.getDir().normalize()) * theNormal;
            vec3 ref = (r.getDir() - 2*vpar).normalize();
            return closestShape->hit(closestPos) + closestShape->getSpecular() * trace(Ray(closestPos + 0.01 * ref, ref), level-1);
        }
        
        return black;
    }


}
