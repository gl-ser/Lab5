//----------------------------------------------------------------------------//
//                       *** ЛАБОРАТОРНАЯ РАБОТА № 5 ***                      //
//                                                                            //
// Файл Graphic.h                                                             //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей Юрьевич                                              //
//                                                                            //
//                                                   Москва, НИИ ТП, 2023 год //
//----------------------------------------------------------------------------//


#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QApplication>
#include <QFrame>
#include <QFileDialog>
#include <QPainter>
#include <algorithm>

#include "TelemetricFile.h"


class TGraphic : public QFrame
{
  Q_OBJECT
  signals:

  private:
    double ScreenMinX, ScreenMaxX, ScreenMinY, ScreenMaxY;
    double MinX, MaxX, MinY, MaxY;

    TData Data;
    TTelemetricFile *TF;

    //Очистка внутреннего массива
    void DataClear(void);

    //Переводит дату и время из формата QDateTime в формат TDateTime
    // TDateTime содержит количество суток, прошедших от 00:00 30.12.1899 г
    // Подаваемое на вход время должно быть больше 01.01.1970 г
    double QDateTimeToTDateTime(QDateTime Value);

    //Переводит дату и время из формата QDateTime в строку типа QString, создавая вышеупомянутую строку
    // по заданной пользователем маске
    // Подаваемое на вход время должно быть больше 01.01.1970 г
    // Примеры масок:
    // - "dd.MM.yyyy  HH:mm:ss.zzz";
    // - "dd.MM.yyyy  HH:mm:ss";
    // - "dd.MM.yyyy"
    QString QDateTimeToQString(QDateTime Value, QString Mask);

    //Переводит одну координату X из отрезка [A; B] в координату из отрезка [Alpha; Betta]
    // По сути производится растяжение или сжатие одномерного пространства
    // "B" должен быть строго больше "A"
    double Strain(double X, double A, double B, double Alpha, double Betta);

    //Переводит функциональные координаты в экранные координаты
    // На вход подаются:
    // - абсцисса X функциональных координат;
    // - ордината Y функциональных координат.
    // На выходе можно получить:
    // - абсцисса ScreenX экранных координат;
    // - ордината ScreenY экранных координат
    void XYToScreenXY(double X, double Y, double* ScreenX, double* ScreenY);

  protected:
    void paintEvent(QPaintEvent *event);

  public:
    TGraphic(void)=delete;
    TGraphic(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    virtual ~TGraphic(void);

    //Чтение содержимого телеметрического файла в память
    // Вызывает диалог открытия файла
    void ReadFile(void);
};


#endif
