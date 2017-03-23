
#include "Raytracer.h"
#include <Math.h>

Camera::Camera(){

    w = glm::normalize(scene->getCameraPos()-scene->getCameraLookAt());
    u = glm::normalize(glm::cross(w,scene->getCameraUp()));
    v = glm::cross(w,u);
    fovy = scene->getFovy()*M_PI/180.0;
  /*cout<< w[0]<<w[1]<<w[2]<<endl;
  cout<< u[0]<<u[1]<<u[2]<<endl;
  cout<< v[0]<<v[1]<<v[2]<<endl;*/
    double z = tan(fovy/2);

    z = (1/z)*scene->getHeight()/2;

    fovx = 2*atan((scene->getWidth()/2)/z);


}

Ray Camera::generateRay(Sample pixel){            
    vec3 origin = scene->getCameraPos();
    int height = scene->getHeight();
    int width = scene->getWidth();

    double alpha = -tan(fovx / 2) * (pixel.getY() - (width / 2)) / (width / 2);
    double beta =  tan(fovy / 2) * ((height / 2) - pixel.getX()) / (height / 2);
    //cout<<alpha<<" "<<beta<<endl;
    vec3 direction = (float)alpha*(this->u)+(float)beta*(this->v)-w;
    direction = glm::normalize(direction);
    return Ray(origin,direction);
}

