//----------------------------------------------------------------------------//
//                       *** ЛАБОРАТОРНАЯ РАБОТА № 5 ***                      //
//                                                                            //
// Файл TelemetricFile.cpp                                                    //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей Юрьевич                                              //
//                                                                            //
//                                                   Москва, НИИ ТП, 2023 год //
//----------------------------------------------------------------------------//


#include "TelemetricFile.h"


TPoint::TPoint(QString line)
{
QStringList SL;
  SL = line.split('\t');

  mTime = QDateTime::currentDateTime();
  mTime.setTime(QTime::fromString(SL[0], "hh:mm:ss.zzz"));
  mTime.setTimeSpec(Qt::UTC);

  mValue = SL[3].toDouble();
}


TPoint::~TPoint()
{
  //Пустой деструктор
}


QString TPoint::toString()
{
  return ("Время " + mTime.toString("hh:mm:ss.zzz") + "  Значение " + QString::number(mValue));
}


TTelemetricFile::TTelemetricFile()
{
  DataClear();
  CloseFile();
}


TTelemetricFile::~TTelemetricFile()
{
  CloseFile();
  DataClear();
}


void TTelemetricFile::ReadFile(QString PathName)
{
  QString str;
  OpenFile(PathName);
  if (IsOpen == true)
  {
    DataClear();
    File.readLine();  //Чтение заголовка файла
    do
    {
      str = QString(File.readLine());

      if (str != "")
        Data.push_back(new TPoint(str));

    } while (str != "");
  }
  CloseFile();
}


TData TTelemetricFile::ReadFile2(QString PathName)
{
QString str;
TData Res;

  OpenFile(PathName);
  if (IsOpen == true)
  {
    File.readLine();  //Чтение заголовка файла
    do
    {
      str = QString(File.readLine());

      if (str != "")
        Res.push_back(new TPoint(str));

    } while (str != "");
  }
  CloseFile();

  return Res;
}


QStringList TTelemetricFile::Print()
{
QStringList Res;

  for(int i=0; i<Data.size(); i++)
    Res.push_back(Data[i]->toString());

  return Res;
}


void TTelemetricFile::OpenFile(QString FilePathName)
{
  CloseFile();
  File.setFileName(FilePathName);

  File.setPermissions(QFile::ReadOwner | QFile::WriteOwner |
                      QFile::ReadGroup | QFile::WriteGroup |
                      QFile::ReadOther | QFile::WriteOther);

  IsOpen = File.open(QIODevice::ReadOnly);
}


void TTelemetricFile::DataClear()
{
  for(int i=0; i<Data.size(); i++)
    delete Data[i];

  Data.clear();
}


void TTelemetricFile::CloseFile()
{
  File.close();
  IsOpen = false;
}

