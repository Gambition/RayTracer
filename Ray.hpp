#ifndef
#define RAY
class Ray{
    private:
        vec3 position;
        vec3 direciton;
        float t_min,t_max;
    
    public:
        Ray(const vec3 pos,const vec3 dir,float t_min, float t_max):
            position(pos),direction(dir),t_min(t_min),t_max(t_max){}
        vec3 getPos(){
            return this->position;
        }
        vec3 getDir(){
            return this->direciton;
        }
}

#endif

