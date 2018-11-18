#include "flycapture/FlyCapture2.h"
#include "camera.h"

int main(void)
{

    //1. Connect and adjust camera
    FlyCapture2::Camera camera;
    FlyCapture2::CameraInfo caminfo;
    camera_connect(camera, caminfo);
    camera_adjust(camera);

    //2. Create Phase and Gray code patterns



    //3. Show and Capture Patterns



    //4. Unwrap Phase Maps


    //5. Create Point Correspondences


}

