//----------------------------------------------------------------------------//
//                    *** ЛАБОРАТОРНАЯ РАБОТА №№ 3,4,5 ***                    //
//                                                                            //
// Файл TelemetricFile.h                                                      //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей Юрьевич                                              //
//                                                                            //
//                                                   Москва, НИИ ТП, 2023 год //
//----------------------------------------------------------------------------//


#ifndef TELEMETRICFILE_H
#define TELEMETRICFILE_H

#include <QFile>
#include <QList>
#include <QString>
#include <QDateTime>


//Одна строка записи телеметрического файла
class TPoint
{
  public:
    double mValue;    //Значение
    QDateTime mTime;  //Время

    TPoint(void) = delete;
    TPoint(QString line);
    virtual ~TPoint(void);

    //Отображение состояния
    QString toString(void);
};


//Результат чтения телеметрического файла
typedef QList<TPoint*> TData;


class TTelemetricFile
{
  private:
    TData Data;  //Содержимое телеметрического файла (заполняется методом ReadFile)
    QFile File;
    bool IsOpen;

    //Очистка внутреннего массива
    void DataClear(void);

    //Закрывает ранее открытый файл
    void CloseFile(void);

    //Открывает произвольный файл на чтение
    // На вход подаются:
    //   - путь и имя файла
    void OpenFile(QString FilePathName);

  public:
    TTelemetricFile(void);
    virtual ~TTelemetricFile(void);

    //Чтение содержимого телеметрического файла в память
    // На вход подается путь и имя файла
    void ReadFile(QString PathName);

    //Чтение содержимого телеметрического файла в выходной список
    // На вход подается путь и имя файла
    TData ReadFile2(QString PathName);

    //Вывод данных телеметрического файла после чтения методом ReadFile
    QStringList Print(void);
};


#endif
