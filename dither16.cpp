#include <QApplication>
#include <QFileDialog>
#include "dither16.h"
#include "ditherer.h"

// public

Dither16::Dither16(bool autoquit, QString filename, bool overwrite,
                   QObject* parent)
   : QObject(parent),
     autoquit_(autoquit),
     filename_(filename),
     overwrite_(overwrite)
{
}

// public slots

void Dither16::ditheredImage(QImage image)
{
   image.save(overwrite_ ? filename_ : QFileDialog::getSaveFileName());
   if (autoquit_)
   {
      emit quit();
   }
}

int main(int argc, char** argv)
{
   QApplication app(argc, argv);

   QStringList args(QApplication::arguments());
   bool autoquit(false);
   QString filename;
   bool overwrite(false);
   for (int i(1); i < args.size(); ++i)
   {
      if (args.at(i) == "-a")
      {
         autoquit = true;
      }
      if (args.at(i) == "-o")
      {
         overwrite = true;
      }
      else if (QFile(args.at(i)).exists())
      {
         filename = args.at(i);
      }
   }

   Dither16 dither16(autoquit, filename, overwrite);
   Ditherer ditherer(QImage(
              !filename.isEmpty() ? filename : QFileDialog::getOpenFileName()));
   QObject::connect(&ditherer, SIGNAL(ditheredImage(QImage)),
                    &dither16, SLOT(ditheredImage(QImage)));
   QObject::connect(&dither16, SIGNAL(quit()), &app, SLOT(quit()));
   ditherer.show();
   ditherer.start();

   return app.exec();
}
