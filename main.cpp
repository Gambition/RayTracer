#include <stdlib.h>
#include <stdio.h>
#include "Scene.hpp"

int main(int argc, char*argv[])
{
    Scene* myScene = new Scene();
    Scene->readFile(argv[1]);
    Scene->Render();
}