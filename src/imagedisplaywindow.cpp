#include "openglwindow.h"
#include "param_config.h"
#include "patterns.h"
#include "imagedisplaywindow.h"

//OpenCV related includes
#include "opencv2/core/opengl.hpp"
#include "opencv2/highgui.hpp"

// QT related includes
#include <QtGui/QGuiApplication>
#include <QDir>

// QT OpenGL related includes
#include <QOpenGLPaintDevice>
#include <QOpenGLTexture>
#include <QPainter>
#include <QInputEvent>


ImageDisplayWindow::ImageDisplayWindow(): width(monitor_width), heigth(monitor_height), image_rate(0), image_number(0)
{

}

//Convert cv::Mat to QImage
void ImageDisplayWindow::generate_qimages_array()
{
  vector<Mat> patterns;
  create_patterns_all(monitor_width, monitor_height, periods, patterns, 0, patterns);
  QVector<QImage> q_img_array;

////   Convert by reading ".png" images
////   Check if image folder exist
//  if (!QDir("Folder").exists()){
//    QDir().mkdir("img");
//  }

//  for (unsigned long i=0; i<patterns.size();i++) {
//         ostringstream tt;
//         tt<<i;
//         String file_name = "img/pattern_"+tt.str()+".png";
//         cv::imwrite(file_name,patterns[i]);

//         QImage q_image = QImage(QString::fromStdString(file_name));
//         q_image.bits();
//         q_img_array.push_back(q_image);
//  }

//Convert by sharing the same Buffer
  for (unsigned long i=0; i<patterns.size(); i++) {
    Mat pattern = patterns[i];
    QVector<QRgb> colorTable;
    for (int i=0; i<256; i++)
        colorTable.push_back(qRgb(i,i,i));
    const uchar *qImageBuffer = (const uchar*)pattern.data;
    QImage q_image(qImageBuffer, pattern.cols, pattern.rows, static_cast<int>(pattern.step), QImage::Format_Grayscale8);
    q_image.setColorTable(colorTable);
    q_img_array.push_back(q_image);
  }


  m_q_img_array = q_img_array;
}

//Convert QImage to QPixmap
void ImageDisplayWindow::generate_pixmap_array()
{
  QVector<QPixmap> q_pixmap_array;

  for (int i=0; i<m_q_img_array.size();i++) {
     QImage q_image = m_q_img_array[i];
     q_image.bits();
     QPixmap q_pixmap = QPixmap::fromImage(q_image);
     q_pixmap_array.push_back(q_pixmap);
  }

  m_q_pixmap_array = q_pixmap_array;

}

void ImageDisplayWindow::initialize()
{
    generate_qimages_array();
    generate_pixmap_array();

    for (int i=0; i<m_q_img_array.size();i++) {
        QOpenGLTexture *texture;
        texture = new QOpenGLTexture(m_q_img_array[i]);
        texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        textures.push_back(texture);
    }
}

//  //Display patterns by drawing QPixmap
//void ImageDisplayWindow::render()
//{
//  if (!m_device_image)
//      m_device_image = new QOpenGLPaintDevice;
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//  m_device_image->setSize(size());
//  QPainter painter(m_device_image);


//  image_number = image_rate/10;
//  if(image_number >= m_q_pixmap_array.size()){
//    image_number = 0;
//    image_rate = 0;
//  }
//  painter.drawPixmap(0,0,m_q_pixmap_array[image_number]);

//  ++image_rate;
//}


void ImageDisplayWindow::render(){
    glViewport(0,0,width,heigth);
    glClearColor(0.4f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);

    // To slow down the display rate of the image sequence


    if (is_rendering)
    {
        image_number = image_rate/display_rate;
        if(image_number >= m_q_img_array.size()){
            image_number = 0;
            image_rate = 0;
        }
    }


    // Render with texture
    textures[image_number]->bind();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
      glVertex2f(-1.0f, -1.0f);
      glTexCoord2f(1,0);
      glVertex2f(1.0f, -1.0f);
      glTexCoord2f(1,1);
      glVertex2f(1.0f, 1.0f);
      glTexCoord2f(0,1);
      glVertex2f(-1.0f, 1.0f);
    glEnd();

    if (is_rendering)
    {
        ++image_rate;
    }


    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_2D);
}






