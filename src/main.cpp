#include "flycapture/FlyCapture2.h"
#include "camera.h"
#include "patterns.h"
#include "imagedisplaywindow.h"
#include "param_config.h"

// QT related includes
#include <QtGui/QGuiApplication>
#include <QDir>

// QT OpenGL related includes
#include <QOpenGLPaintDevice>
#include <QOpenGLTexture>

int main(int argc, char **argv)
{

    //1. Connect and adjust camera
    FlyCapture2::Camera camera;
    FlyCapture2::CameraInfo caminfo;
    //camera_connect(camera, caminfo);
    //camera_adjust(camera);
    //camera_disconnect(camera);

    //2. Create Phase and Gray code patterns
    //    vector<Mat> patterns;

    //    create_patterns_all(monitor_width, monitor_height, periods, patterns, 0, patterns);


    /// Show created patterns
//    namedWindow("Patterns", WINDOW_NORMAL);
//    cvSetWindowProperty("Patterns", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

//    for (int i = 0; i<static_cast<int>(patterns.size()); i++){

//        imshow("Patterns", patterns[i]);
//        waitKey(500);
//    }
//    destroyAllWindows();

    QSurfaceFormat format;
    format.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(format);

    QGuiApplication app(argc, argv);
    ImageDisplayWindow window;

    window.setFormat(format);
    window.showFullScreen();

    window.setAnimating(true);

    return app.exec();



    //3. Show and Capture Patterns



    //4. Unwrap Phase Maps


    //5. Create Point Correspondences


}

