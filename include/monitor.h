#ifndef MONITOR_H
#define MONITOR_H
#include <iostream>
class  Monitor
{
public:
    float size_x, size_y, radiusofCurvature;
    float pixelsize_x, pixelsize_y;
    std::string modelname;
    /**
    This is a class which describes the Monitor used for calibration
     */
    Monitor();

    /** @overload
    @param a pixel resolution in width.
    @param b pixel resolution in height.
    @param c size of pixel in x direction in mm
    @param d size of pixel in y direction in mm
    */
    Monitor(int a, int b, double c, double d, int e);

    /** @overload
    @param monitorModel Model of Monitor used
    */
    Monitor(int monitorModel);
};

enum MonitorModel {
       SAMSUNG_FLAT     = 0x00000000, //!< the user can resize the window (no constraint) / also use to switch a fullscreen window to a normal size.
       SAMSUNG_CURVED   = 0x00000001, //!< Monitor which was used in first experiments

    };

#endif // MONITOR_H
