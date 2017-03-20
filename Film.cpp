

#include "Raytracer.h"
#include "FreeImage.h"

        Film::Film()
        {
            pixels = vector< vector<Color> > (scene->getHeight(),
                    vector<Color>(scene->getWidth(),Color(0,0,0)));    
        }
        
        void Film::commit(Sample& sample,Color& color)
        {
            pixels[sample.getX()][sample.getY()] = 
             pixels[sample.getX()][sample.getY()]+color;   
        }


        void Film::writeImage(string path)
        {
            int bpp = 24;
            FreeImage_Initialise();

            FIBITMAP* img = FreeImage_Allocate(scene->getWidth(),
                                                scene->getHeight(),bpp);

            RGBQUAD value;
            for(int j=0;j<480;j++)
            {
                vector<Color> temp = pixels[j];
                for(int i=0;i<640;i++)
                {
                    //value.rgbRed = temp[i].getRed();
                    value.rgbRed = temp[i].getBlue();
                    value.rgbGreen = temp[i].getGreen();
                    value.rgbBlue = temp[i].getRed();
                  
                    FreeImage_SetPixelColor(img,i,j, &value);
                }
            }
            string output = path;
            FreeImage_Save(FIF_PNG,img, output.c_str(),0);
        }

