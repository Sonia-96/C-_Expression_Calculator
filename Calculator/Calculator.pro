DISTFILES += \
    ../MSDScript/Makefile \

HEADERS += \
    ../MSDScript/catch.h \
    ../MSDScript/env.h \
    ../MSDScript/expr.h \
    ../MSDScript/parser.h \
    ../MSDScript/pointer.h \
    ../MSDScript/val.h \
    msdwidget.h

SOURCES += \
    ../MSDScript/env.cpp \
    ../MSDScript/exec.cpp \
    ../MSDScript/expr.cpp \
    ../MSDScript/parser.cpp \
    ../MSDScript/val.cpp \
    main.cpp \
    msdwidget.cpp

QT += widgets
