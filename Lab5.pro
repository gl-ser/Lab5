#----------------------------------------------------------------------------#
#                       *** ЛАБОРАТОРНАЯ РАБОТА № 5 ***                      #
#                                                                            #
# Проект для Qt 5                                                            #
#                                                                            #
# Автор ГЛУЩЕНКО Сергей Юрьевич                                              #
#                                                                            #
#                                                   Москва, НИИ ТП, 2023 год #
#----------------------------------------------------------------------------#

QT += core widgets

TARGET = Lab5
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $$PWD/APP  #Размещение исполняемого файла

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    TelemetricFile.cpp \
    Graphic.cpp

HEADERS += \
        MainWindow.h \
    TelemetricFile.h \
    Graphic.h

FORMS += \
        MainWindow.ui

RESOURCES += \
    Icons.qrc
