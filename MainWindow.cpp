//----------------------------------------------------------------------------//
//                       *** ЛАБОРАТОРНАЯ РАБОТА № 5 ***                      //
//                                                                            //
// Файл MainWindow.cpp                                                        //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей Юрьевич                                              //
//                                                                            //
//                                                   Москва, НИИ ТП, 2023 год //
//----------------------------------------------------------------------------//


#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  setupUi(this);

  Graphic = new TGraphic(this);
  this->gridLayout->addWidget(Graphic);
}


MainWindow::~MainWindow()
{
  this->gridLayout->removeWidget(Graphic);
  delete Graphic;
}


void MainWindow::on_action_triggered()
{
  Graphic->ReadFile();
}
