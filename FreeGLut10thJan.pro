TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -Wl,--stack,100000000
QMAKE_CXXFLAGS += -Wl,--heap,100000000
SOURCES += \
    main.cpp \
    FlightSimulator.cpp \
    QuadEnvironment.cpp \
    OpenGlFuncTools.cpp \
    Orbital.cpp \
    Plane.cpp \
    MoutainObjects.cpp \
    SeaSkyTerrain.cpp

LIBS+= -lglut
LIBS+= -lGLU
LIBS+= -lGL




SUBDIRS +=

HEADERS += \
    FlightSimulator.h \
    QuadEnvironment.h \
    OpenGlUtilities \
    OpenGlFuncTools.h \
    Orbital.h \
    Plane.h \
    MoutainObjects.h \
    SeaSkyTerrain.h \
    perlinnoise.h








