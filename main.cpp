
#include <QCoreApplication>
#include <QTimer>

#include <parser/parser.h>
#include "util/file/fileutil.h"
#include <exception/qtexception.h>
#include "model/type.h"
#include <csignal>
#include <model/ast.h>
using QtCommon2::FileUtil;
using QtCommon2::QtException;

void signalhandler(int sig)
{
    if (sig == SIGINT)
    {
        printf("will quit by SIGINT\n");
        qApp->quit();
    }
    else if (sig == SIGTERM)
    {
        printf("will quit by SIGTERM\n");
        qApp->quit();
    }
    else if (sig == SIGILL)
    {
        printf("will quit by SIGILL\n");
        qApp->quit();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    signal(SIGINT,signalhandler);
    signal(SIGTERM,signalhandler);
    signal(SIGILL,signalhandler);
    auto args = a.arguments();
    if(args.size()<2)
    {
        qDebug()<<"missing args";
        return 1;
    }

    try {
        Type::initPrimitiveTypes();
        Parser p;
        AST *ast = p.parse(FileUtil::readAllUtf8(args[1]));
        ast->run();
        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
    } catch (const QtException &e) {
         qDebug()<<e.getLogString();
    }

    return a.exec();
}
