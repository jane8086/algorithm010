#ifndef IMAGEDISPLAYWINDOW_H
#define IMAGEDISPLAYWINDOW_H

#include "openglwindow.h"

//Rewrite class OpenGLWindow's functions
class ImageDisplayWindow : public OpenGLWindow
{
public:
    ImageDisplayWindow();

    void initialize() override;
    void render() override;
    void generate_qimages_array();
    void generate_pixmap_array();

    QVector<QImage> m_q_img_array;
    QVector<QPixmap> m_q_pixmap_array;
    int width;
    int heigth;

private:
    QOpenGLPaintDevice *m_device_image;
    int image_rate;
    int image_number;
    QVector<QOpenGLTexture *> textures;
};


#endif // IMAGEDISPLAYWINDOW_H
