#include <FreeImage.h>
#ifndef 
#define FILM

class Film{
    private:
        pixels = vector<vector<Color>>;
    public:
        Film()
        {
            pixels = vector<vector<Color>>(scene->getHeight,
                    vector<Color>(scene->getWidth(),Color(0,0,0)));
        }
        void commit(Sample& sample,Color& color)
        {
             
        }

        void writeImage()
        {
            int bpp = 24;
            FreeImage_Initialise();
            FIBITMAP* img = FreeImgae_Allocate(scene->getWidth,
                                                scene->getHeight,bpp);
            
            RGBQUAD value;
            for(int j=0;j<scene->getHeight;j++)
            {
                vector<Color>* temp = pixels[j];
                for(int i=0;i<scene->getWidth();i++)
                {
                    value.rgbRed = temp[i]->getRed;
                    value.rgbGreen = temp[i]->getGreen;
                    value.rgbBlue = temp[i]->getRed;
                    FreeImage_SetPixelColor(*img,i,j,value);
                }
            }
        
            FreeImage_Save(FIF_PNG,img,"testImg".c_str(),0);
        }

};