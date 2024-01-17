QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ../backend/arithmetics.c \
    ../backend/calculations.c \
    ../backend/check_brackets.c \
    ../backend/check_functions.c \
    ../backend/get_result.c \
    ../backend/operations_handler.c \
    ../backend/parser.c \
    ../backend/simple_checkers.c \
    ../backend/stack_functions.c \
    ../backend/validator.c \
    ../backend/credit_calc.c \
    qcustomplot.cpp

HEADERS += \
    ../s21_smartcalc.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
