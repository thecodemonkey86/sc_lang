
#include <QCoreApplication>

#include <parser/parser.h>
#include "util/file/fileutil.h"

using QtCommon2::FileUtil;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    auto args = a.arguments();
    if(args.size()<2)
    {
        qDebug()<<"missing args";
        return 1;
    }

    Parser::parse(FileUtil::readAllUtf8(args[1]));
    return a.exec();
}
