#ifndef 
#define FILM

class Film{
    private:
        pixels;
    public:
        Film()
        {
            pixels = vector<vector<Color>>(scene->getHeight,
                    vector<Color>(scene->getWidth(),Color(0,0,0)));
        }
        void commit(Sample& sample,Color& color)
        {
             
        }


};