TEMPLATE = app
CONFIG -= qt

SOURCES += main.cpp \
    snake.cpp

LIBS += -L/usr/local/lib -lallegro_primitives -lallegro -lallegro_ttf

HEADERS += \
    snake.h
