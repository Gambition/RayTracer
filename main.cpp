#include <stdlib.h>
#include <stdio.h>
#include "Scene.hpp"

Scene *scene;
int main(int argc, char*argv[])
{
    scene = new Scene();
    Scene->readFile(argv[1]);
    Scene->Render();
}