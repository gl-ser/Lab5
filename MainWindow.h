//----------------------------------------------------------------------------//
//                       *** ЛАБОРАТОРНАЯ РАБОТА № 5 ***                      //
//                                                                            //
// Файл MainWindow.h                                                          //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей Юрьевич                                              //
//                                                                            //
//                                                   Москва, НИИ ТП, 2023 год //
//----------------------------------------------------------------------------//


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "Graphic.h"


class MainWindow : public QMainWindow, private Ui::MainWindow
{
  Q_OBJECT

  private slots:
    void on_action_triggered();

  private:
    TGraphic *Graphic;

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow(void);
};


#endif
