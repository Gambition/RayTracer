#include "Raytracer.h"

Color RayTracer::trace(Ray r,int depth){
   
    Color black = Color(0,0,0);
    
    //base case
    if(depth==0)
    {
        return black;
    }

    double closeHit = -1;
    Intersection closeIts;
    Shape* hitShape = NULL;

    //loop throught all the shapes to determine whether
    //there is a hit. If there are multiple hits, keep updating
    //to find the closest hit.
    //cout<<scene->shapes.size()<<endl;
    for (int i=0;i<scene->shapes.size();i++) {
 
        Intersection its = scene->shapes[i]->isHit(r);
   
        if (its.isHit()) {    
         
            float dist = glm::distance(r.getPos(),its.getPos());
            if (closeHit < 0 || dist < closeHit) {
                closeHit = dist;
                closeIts = its;
                hitShape = scene->shapes[i];
            }
        }
    }
  
    
    if (hitShape != NULL) {
       
        vec3 theNormal = hitShape->getNormal(closeIts.getPos());
       
        vec3 vpar = glm::dot(theNormal,glm::normalize(r.getDir()))*theNormal;
        vec3 reflected = glm::normalize(r.getDir() - (float)1.5*vpar);

        return hitShape->findColor(closeIts) + 
                hitShape->getSpecular() * trace(Ray(closeIts.getPos()+
                (float)1*reflected, reflected), depth-1);
    }
        
    return black;
}


float RayTracer::closestHit(Ray r) {
  float closeHit = -1;
  
  for (int i=0;i<scene->shapes.size();i++) {
 
        Intersection its = scene->shapes[i]->isHit(r);
        if (its.isHit()) {    
            float dist = glm::distance(r.getPos(),its.getPos());
            if (closeHit< 0 || dist < closeHit) {
                closeHit = dist;
            }
        }
    }
    return closeHit;
}
