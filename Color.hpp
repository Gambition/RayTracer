#ifndef COLOR_HPP
#define COLOR_HPP

class Color{
    private:
        float r,g,b;
    
    public:
        Color(float r,float g,float b):
            r(r),g(g),b(b){}
        
        float getRed() {return this->r;}
        float getGreen() {return this->g;}
        float getBlue() {return this->b;}

        Color operator+(const Color& other){
            return Color(this->r + other.r,
                         this->g + other.g,
                         this->b + other.b);
        }
        
        Color operator-(const Color& other){
            return Color(this->r - other.r,
                         this->g - other.g,
                         this->b - other.b);
        }

        Color operator*(double scale){
            return Color(this->r * scale,
                         this->g * scale,
                         this->b * scale);
        }
        
        //TODO What is converstion from xyz???
};

#endif