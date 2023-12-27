QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

COMPILER = ""
ARCH = ""

msvc {

 COMPILER = "MSVC2019"
 MSVC_VER = $$(VisualStudioVersion)
 equals(MSVC_VER, 16.0){
     COMPILER = "MSVC2019"
 }

    equals(QT_ARCH, "x86_64"){
        ARCH = "64bit"
    } else {
         ARCH = "32bit"
    }

}





# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



CONFIG(release, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_$${COMPILER}_$${ARCH}/release/ -lQtCommon2
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_$${COMPILER}_$${ARCH}/debug/ -lQtCommon2


INCLUDEPATH += $$PWD/../QtCommon2

HEADERS += \
    model/accessvarexpression.h \
    model/andoperator.h \
    model/assigninstruction.h \
    model/ast.h \
    model/debugfunction.h \
    model/declareinstruction.h \
    model/divideoperator.h \
    model/expression.h \
    model/floatconstant.h \
    model/forloop.h \
    model/function.h \
    model/greaterthanoperator.h \
    model/i32var.h \
    model/incrementinstruction.h \
    model/instruction.h \
    model/instructionblock.h \
    model/int32type.h \
    model/intconstant.h \
    model/lessthanoperator.h \
    model/minusoperator.h \
    model/multiplyoperator.h \
    model/notoperator.h \
    model/oroperator.h \
    model/parenthesisexpression.h \
    model/plusoperator.h \
    model/stringconstant.h \
    model/token.h \
    model/tokenlist.h \
    model/type.h \
    model/unaryminusoperator.h \
    model/var.h \
    model/whileloop.h \
    parser/parser.h

SOURCES += \
    main.cpp \
    model/accessvarexpression.cpp \
    model/andoperator.cpp \
    model/assigninstruction.cpp \
    model/ast.cpp \
    model/debugfunction.cpp \
    model/declareinstruction.cpp \
    model/divideoperator.cpp \
    model/expression.cpp \
    model/floatconstant.cpp \
    model/forloop.cpp \
    model/function.cpp \
    model/greaterthanoperator.cpp \
    model/i32var.cpp \
    model/incrementinstruction.cpp \
    model/instruction.cpp \
    model/instructionblock.cpp \
    model/int32type.cpp \
    model/intconstant.cpp \
    model/lessthanoperator.cpp \
    model/minusoperator.cpp \
    model/multiplyoperator.cpp \
    model/notoperator.cpp \
    model/oroperator.cpp \
    model/parenthesisexpression.cpp \
    model/plusoperator.cpp \
    model/stringconstant.cpp \
    model/token.cpp \
    model/tokenlist.cpp \
    model/type.cpp \
    model/unaryminusoperator.cpp \
    model/var.cpp \
    model/whileloop.cpp \
    parser/parser.cpp
