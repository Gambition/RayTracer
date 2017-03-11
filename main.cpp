#include "Film.hpp"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char*argv[])
{
    Film* film = new Film();
    film->writeImage();
    /*Scene* scene= new Scene(argv[1]);
    scene->readFile();
    scene->render();*/
}