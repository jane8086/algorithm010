#include <iostream>
#include <include/monitor.h>

using namespace std;

Monitor::Monitor(){

    size_x = 0;
    size_y = 0;
    pixelsize_x = 0;
    pixelsize_y = 0;
    radiusofCurvature = 0;
    modelname = "";


}

Monitor::Monitor( int a, int b,double c, double d, int e){

    size_x = a;
    size_y = b;
    pixelsize_x = c;
    pixelsize_y = d;
    radiusofCurvature = e;
    modelname = "OwnConfig";

}

Monitor::Monitor(int monitorModel){

    switch(monitorModel)
    {
    case 1:
        size_x = 1920;
        size_y = 1080;
        pixelsize_x = 0.2756;
        pixelsize_y = 0.2756;
        radiusofCurvature = 1800;
        modelname = "SamsungCurved";
        break;

    default:
        cout << "Using default monitor settings" << endl;
        size_x = 1920;
        size_y = 1080;
        pixelsize_x = 0.2;
        pixelsize_y = 0.2;
        radiusofCurvature = 1800;
        modelname = "default";
        break;
    }
}



