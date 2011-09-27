#ifndef DITHERER_H
#define DITHERER_H

#include <QImage>
#include <QLabel>
#include "ditherthread.h"

class Ditherer : public QLabel
{
      Q_OBJECT

   public:
      explicit Ditherer(QImage image, QWidget* parent = 0);
      ~Ditherer();
      void start();

   signals:
      void ditheredImage(QImage image);

   protected:
      DitherThread* thread_;

   protected slots:
      void finalImage(QImage image);
      void image(QImage image);
};

#endif
