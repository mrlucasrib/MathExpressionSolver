TEMPLATE = app
CONFIG += console
#CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../MathExpressionSolverLib/release/ -lMathExpressionSolverLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../MathExpressionSolverLib/debug/ -lMathExpressionSolverLib
else:unix: LIBS += -L$$OUT_PWD/../MathExpressionSolverLib/ -lMathExpressionSolverLib

INCLUDEPATH += $$PWD/../MathExpressionSolverLib
DEPENDPATH += $$PWD/../MathExpressionSolverLib
