#include "ditherthread.h"

#include <cmath>
#include <QColor>

// public

DitherThread::DitherThread(QImage image, QObject* parent)
   : QThread(parent),
     image_(image)
{
}

// protected

double DitherThread::colorDistance(QColor x, QColor y)
{
   return std::sqrt((y.red() - x.red()) * (y.red() - x.red())
                    + (y.green() - x.green()) * (y.green() - x.green())
                    + (y.blue() - x.blue()) * (y.blue() - x.blue()));
}

int DitherThread::range(int min, int x, int max)
{
   return std::min(std::max(min, x), max);
}

void DitherThread::run()
{
   QImage outputImage(image_.size(), QImage::Format_Indexed8);
   outputImage.setColor(0, qRgb(0, 0, 0));
   outputImage.setColor(1, qRgb(128, 0, 0));
   outputImage.setColor(2, qRgb(0, 128, 0));
   outputImage.setColor(3, qRgb(128, 128, 0));
   outputImage.setColor(4, qRgb(0, 0, 128));
   outputImage.setColor(5, qRgb(128, 0, 128));
   outputImage.setColor(6, qRgb(0, 128, 128));
   outputImage.setColor(7, qRgb(128, 128, 128));
   outputImage.setColor(8, qRgb(192, 192, 192));
   outputImage.setColor(9, qRgb(255, 0, 0));
   outputImage.setColor(10, qRgb(0, 255, 0));
   outputImage.setColor(11, qRgb(255, 255, 0));
   outputImage.setColor(12, qRgb(0, 0, 255));
   outputImage.setColor(13, qRgb(255, 0, 255));
   outputImage.setColor(14, qRgb(0, 255, 255));
   outputImage.setColor(15, qRgb(255, 255, 255));

   for (int i(image_.height() - 1); i >= 0 ; --i)
   {
      for (int j(0); j < image_.width(); ++j)
      {
         double minDistance(sqrt(255 * 255 + 255 * 255 + 255 * 255));
         int minIndex = 0;
         for (int k(0); k < 16; ++k)
         {
            if (colorDistance(image_.pixel(j, i), outputImage.color(k))
                < minDistance)
            {
               minDistance = colorDistance(image_.pixel(j, i),
                                           outputImage.color(k));
               minIndex = k;
            }
         }
         QColor newColor(outputImage.color(minIndex));
         QColor oldColor(image_.pixel(j, i));
         int errorRed(oldColor.red() - newColor.red());
         int errorGreen(oldColor.green() - newColor.green());
         int errorBlue(oldColor.blue() - newColor.blue());
         image_.setPixel(j, i, newColor.rgb());
         outputImage.setPixel(j, i, minIndex);
         if (j < image_.width() - 1)
         {
            QColor color(image_.pixel(j + 1, i));
            color.setRed(range(0, color.red() + 7.0 / 16 * errorRed, 255));
            color.setGreen(range(0, color.green() + 7.0 / 16 * errorGreen,
                                 255));
            color.setBlue(range(0, color.blue() + 7.0 / 16 * errorBlue, 255));
            image_.setPixel(j + 1, i, color.rgb());
         }
         if (j > 0 && i > 0)
         {
            QColor color(image_.pixel(j - 1, i - 1));
            color.setRed(range(0, color.red() + 3.0 / 16 * errorRed, 255));
            color.setGreen(range(0, color.green() + 3.0 / 16 * errorGreen,
                                 255));
            color.setBlue(range(0, color.blue() + 3.0 / 16 * errorBlue, 255));
            image_.setPixel(j - 1, i - 1, color.rgb());
         }
         if (i > 0)
         {
            QColor color(image_.pixel(j, i - 1));
            color.setRed(range(0, color.red() + 5.0 / 16 * errorRed, 255));
            color.setGreen(range(0, color.green() + 5.0 / 16 * errorGreen,
                                 255));
            color.setBlue(range(0, color.blue() + 5.0 / 16 * errorBlue, 255));
            image_.setPixel(j, i - 1, color.rgb());
         }
         if (j < image_.width() - 1 && i > 0)
         {
            QColor color(image_.pixel(j + 1, i - 1));
            color.setRed(range(0, color.red() + 1.0 / 16 * errorRed, 255));
            color.setGreen(range(0, color.green() + 1.0 / 16 * errorGreen,
                                 255));
            color.setBlue(range(0, color.blue() + 1.0 / 16 * errorBlue, 255));
            image_.setPixel(j + 1, i - 1, color.rgb());
         }
      }
      emit image(image_);
   }
   emit finalImage(outputImage);
}
