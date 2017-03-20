#include <stdlib.h>
#include <stdio.h>
#include "Raytracer.h"
using namespace std;

Scene *scene;
int main(int argc, char*argv[])
{

    scene = new Scene();
    cout<<"Parsing files"<<endl;
    scene->readFile(argv[1]);
    cout<<"Finish parsing"<<endl;
    scene->init();
    scene->Render();
}