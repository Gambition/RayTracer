#ifndef 
#define SCENE
#include "Light.h"
#include "Camera.h"
#include "Film.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
class scene{
    private:
        int width, height;
        vec3 cameraPos;
        vec3 cameraUp;
        vec3 cameraLookAt;
        int fovy;
        Color ambient;
        double diffuse[3];
        double specular[3];
        vector<Light*> lights;
        vector<Shape*> shapes;
        
    public:
    
        Scene(char* filename);
    
        int getWidth(){ return this->width;}
        
        int getHeight(){ return this->getHeight;}

        int getFovy(){ return this->fovy; }
       
        vec3 getCameraPos(){ return this->cameraPos;}

        vec3 getCameraUp(){ return this->cameraUp;}

        vec3 getCameraLookAt(){ return this->cameraLookAt;}
        
        Color getAmbient(){ return this->ambient;}

        double[] getiDiffuse(){ return this->diffuse;}

        double[] getSpecular(){ return this->specular;}

        vector<Light*> getLights() { return this->lights;}

        vector<Shape*> getShapes() { return this->shapes;} 

        void readFile(char* filename){
            string str, cmd;
            ifstream in;
            in.open(filename);
            if (in.is_open()){
                getline(in,str);
                while(in){
                    if((str.find_first_not_of("\t\r\n")!=
                        string::npos)&&(str[0]!='#')){
                            stringstream s(str);
                            s>>cmd;
                        }

                    //read in the size of the image
                    if(cmd=="size") {
                        s>> this->width;
                        s>> this->height;
                    }

                    //read in camera values
                    else if(cmd == "camera"){
                        for(int i=0;i<3;i++)
                        {
                            s>>cameraPos[i];
                        }
                        for(int i=0;i<3;i++)
                        {
                            s>>cameraUp[i];
                        }
                        for(int i=0;i<3;i++)
                        {
                            s>>cameraLookAt[i];
                        }
                        s>>this->fovy;
                    }

                    else if(cmd == "ambient"){
                        int red,green,blue;
                        s>>red;
                        s>>green;
                        s>>blue;
                        ambient(red,green,blue);
                    }
                    else if(cmd == "directional"){
                        //TODO
                    }
                    else if(cmd == "point"){
                        //TODO
                    }
                    else if(cmd == "diffuse"){
                        for(int i=0;i<3;i++){
                            s>>this->diffuse[i];
                        }
                    }
                    else if(cmd == "specular"){
                        for(int i=0;i<3;i++){
                            s>>this->specular[i];
                        }
                    }
                    
                }
            }

        }

        void Render(){

        }
}