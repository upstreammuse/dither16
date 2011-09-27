#include "ditherer.h"

// public

Ditherer::Ditherer(QImage image, QWidget* parent)
   : QLabel(parent),
     thread_(new DitherThread(image, this))
{
   setPixmap(QPixmap::fromImage(image));
   connect(thread_, SIGNAL(finalImage(QImage)), this, SLOT(finalImage(QImage)));
   connect(thread_, SIGNAL(image(QImage)), this, SLOT(image(QImage)));
}

Ditherer::~Ditherer()
{
   thread_->wait();
}

void Ditherer::start()
{
   thread_->start();
}

// protected slots

void Ditherer::finalImage(QImage image)
{
   setPixmap(QPixmap::fromImage(image));
   emit ditheredImage(image);
}

void Ditherer::image(QImage image)
{
   setPixmap(QPixmap::fromImage(image));
}
