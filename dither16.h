#ifndef DITHER16_H
#define DITHER16_H

#include <QImage>

class Dither16 : public QObject
{
      Q_OBJECT

   public:
      Dither16(bool autoquit, QString filename, bool overwrite,
               QObject* parent = 0);

   public slots:
      void ditheredImage(QImage image);

   signals:
      void quit();

   protected:
      bool autoquit_;
      QString filename_;
      bool overwrite_;
};

#endif
