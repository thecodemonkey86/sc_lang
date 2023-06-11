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
    model/expression.h \
    model/parenthesisexpression.h \
    model/stringconstant.h \
    model/token.h \
    model/tokenlist.h \
    parser/parser.h

SOURCES += \
    main.cpp \
    model/expression.cpp \
    model/parenthesisexpression.cpp \
    model/stringconstant.cpp \
    model/token.cpp \
    model/tokenlist.cpp \
    parser/parser.cpp
