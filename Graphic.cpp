//----------------------------------------------------------------------------//
//                       *** ЛАБОРАТОРНАЯ РАБОТА № 5 ***                      //
//                                                                            //
// Файл Graphic.cpp                                                           //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей Юрьевич                                              //
//                                                                            //
//                                                   Москва, НИИ ТП, 2023 год //
//----------------------------------------------------------------------------//


#include "Graphic.h"
#include <QDebug>


TGraphic::TGraphic(QWidget *parent, Qt::WindowFlags f) : QFrame(parent, f)
{
  this->setFrameShape(Shape::Box);
  this->setFrameShadow(Shadow::Raised);

  TF = new TTelemetricFile();
  DataClear();
}


TGraphic::~TGraphic()
{
  delete TF;
  DataClear();
}


void TGraphic::ReadFile()
{
QString FilePathName;  //Путь и имя к текстовому файлу

  FilePathName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Читать файл"),
                                              qApp->applicationDirPath(), QString::fromUtf8("*.txt"));
  if (FilePathName != "")
  {
    /*#ifdef __unix__
    FilePathName = FilePathName + ".txt";
    #endif*/

    DataClear();

    Data = TF->ReadFile2(FilePathName);
  }
}


void TGraphic::DataClear()
{
  for(unsigned int i=0; i<Data.size(); i++)
    delete Data[i];

  Data.clear();
}


double TGraphic::QDateTimeToTDateTime(QDateTime Value)
{
QDateTime dt;
double res;
  dt = (QDateTime::fromString("01.01.1970 00:00:00", "dd.MM.yyyy HH:mm:ss"));
  dt.setTimeSpec(Qt::UTC);
  Value.setTimeSpec(Qt::UTC);

  if (Value.toMSecsSinceEpoch() >= dt.toMSecsSinceEpoch())
  {
    res = (static_cast<double>(Value.toMSecsSinceEpoch()))/1000.0/86400.0+25569.0;
  }
  else
  {
    res = (static_cast<double>(dt.toMSecsSinceEpoch()))/1000.0/86400.0+25569.0;
  }
  return res;
}


QString TGraphic::QDateTimeToQString(QDateTime Value, QString Mask)
{
QString res;
  res = Value.toString(Mask);
  return res;
}


double TGraphic::Strain(double X, double A, double B, double Alpha, double Betta)
{
  return ((X-A)/(B-A))*(Betta - Alpha) + Alpha;
}


void TGraphic::XYToScreenXY(double X, double Y, double *ScreenX, double *ScreenY)
{
  *ScreenX = Strain(X, MinX, MaxX, ScreenMinX, ScreenMaxX);
  *ScreenY = Strain(Y, MinY, MaxY, ScreenMinY, ScreenMaxY);
}


void TGraphic::paintEvent(QPaintEvent *event)
{
  if (Data.size() > 2)
  {
    QFrame::paintEvent(event);
    QPainter Painter(this);
    double ScrX=0.0, ScrY=0.0, PredX=0.0, /*PredY=0.0,*/ PredX2=0.0, PredY2=0.0;
    QPointF PF;
    QFont Font;

    Font.setPointSize(8);
    Painter.setFont(Font);

    ScreenMinX = Font.pointSize() + 50.0;
    ScreenMinY = 20.0;
    ScreenMaxX = width()-20.0;
    ScreenMaxY = height()-50.0;

    Painter.fillRect(static_cast<int>(ScreenMinX)-5, static_cast<int>(ScreenMinY)-5,
                     static_cast<int>(ScreenMaxX)-45, static_cast<int>(ScreenMaxY), Qt::white);

    MinX = 0.0;
    MaxX = (QDateTimeToTDateTime(Data[Data.size()-1]->mTime) - QDateTimeToTDateTime(Data[0]->mTime))*86400.0*1000.0;
    MinY = 1000000000.0;
    MaxY = -1000000000.0;

    for(unsigned int i=0; i<Data.size(); i++)
    {
      MinY = std::min(MinY, (-1)*Data[i]->mValue);
      MaxY = std::max(MaxY, (-1)*Data[i]->mValue);
    }

    for(unsigned int i=0; i<Data.size(); i++)
    {
      PredX2 = ScrX;
      PredY2 = ScrY;

      XYToScreenXY((QDateTimeToTDateTime(Data[i]->mTime) - QDateTimeToTDateTime(Data[0]->mTime))*86400.0*1000.0,
                   (-1)*Data[i]->mValue, &ScrX, &ScrY);

      PF.setX(ScrX);
      PF.setY(ScrY);
      Painter.drawEllipse(PF, 3, 3);  //Узловые точки
      //Painter.drawEllipse(static_cast<int>(ScrX), static_cast<int>(ScrY), 5, 5);  //Узловые точки

      Painter.drawLine(static_cast<int>(ScreenMinX)-10, static_cast<int>(ScrY),
                       static_cast<int>(ScreenMinX)-15, static_cast<int>(ScrY));  //Горизонтальные засечки на оси OY

      Painter.drawText(0+Font.pointSize()/2, static_cast<int>(ScrY+Font.pointSize()/2), QString::number(Data[i]->mValue));

      Painter.drawLine(static_cast<int>(ScrX), static_cast<int>(ScreenMaxY-5+20.0),
                       static_cast<int>(ScrX), static_cast<int>(ScreenMaxY+20.0));  //Вертикальные засечки на оси OX

      if (i == 0)
      {
        PredX = ScrX;
        //PredY = ScrY;

        //Painter.drawText(0+Font.pointSize()/2, static_cast<int>(ScrY+Font.pointSize()/2), QString::number(Data[i]->mValue));

        Painter.drawText(static_cast<int>(ScrX)-4*Font.pointSize(), static_cast<int>(height()-Font.pointSize()),
                         QDateTimeToQString(Data[i]->mTime, "HH:mm:ss.zzz"));
      }

      /*if ((ScrY-PredY) > Font.pointSize())
      {
        Painter.drawText(0+Font.pointSize()/2, static_cast<int>(ScrY+Font.pointSize()/2), QString::number(Data[i]->mValue));
      }*/

      if (i < Data.size()-1)
      {
        if ((ScrX-PredX) > 10*Font.pointSize())
        {
          PredX = ScrX;
          //PredY = ScrY;

          Painter.drawText(static_cast<int>(ScrX)-4*Font.pointSize(), static_cast<int>(height()-Font.pointSize()),
                           QDateTimeToQString(Data[i]->mTime, "HH:mm:ss.zzz"));
        }
      }

      if (i > 0)
      {
        Painter.drawLine(static_cast<int>(PredX2), static_cast<int>(PredY2), static_cast<int>(ScrX), static_cast<int>(ScrY));
      }
    }
  }
}
