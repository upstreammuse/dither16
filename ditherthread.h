#ifndef DITHERTHREAD_H
#define DITHERTHREAD_H

#include <QColor>
#include <QImage>
#include <QObject>
#include <QThread>

class DitherThread : public QThread
{
      Q_OBJECT

   public:
      explicit DitherThread(QImage image, QObject* parent = 0);

   signals:
      void finalImage(QImage image);
      void image(QImage image);

   protected:
      double colorDistance(QColor x, QColor y);
      int range(int min, int x, int max);
      void run();

      QImage image_;
};

#endif
