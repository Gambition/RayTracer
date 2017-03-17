#ifndef FILM_HPP
#define FILM_HPP

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Raytracer.h"
#include "FreeImage.h"


using namespace std;
class Film{
    private:
        std::vector< vector<Color> > pixels;
    public:
        Film()
        {
            pixels = vector< vector<Color> > (scene->getHeight,
                    vector<Color>(scene->getWidth(),Color(0,0,0)));    
        }
        
        void commit(Sample& sample,Color& color)
        {
            pixels[sample.getX()][sample.getY()] = 
             pixels[sample.getX()][sample.getY()]+color;   
        }


        void writeImage(string path)
        {
            int bpp = 24;
            FreeImage_Initialise();

            FIBITMAP* img = FreeImgae_Allocate(scene->getWidth,
                                                scene->getHeight,bpp);

            RGBQUAD value;
            for(int j=0;j<480;j++)
            {
                vector<Color> temp = pixels[j];
                for(int i=0;i<640;i++)
                {
                    //value.rgbRed = temp[i].getRed();
                    value.rgbRed = 255;
                    value.rgbGreen = temp[i].getGreen();
                    value.rgbBlue = temp[i].getRed();
                  
                    FreeImage_SetPixelColor(img,i,j, &value);
                }
            }
            string output = path+".png";
            FreeImage_Save(FIF_PNG,img, output.c_str(),0);
        }

        //FreeImage_DeInitialise();

};

#endif
