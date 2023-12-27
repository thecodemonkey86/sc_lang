#pragma once
#include <QString>
#include <QObject>
class Int32Type;

class Type : public QObject
{
public:
     static Type* int32Type;
private:
    QString name;
    bool primitive;
    bool isPlaceholder;
    static QHash<QString,Type*> declaredTypes;
    static QHash<QString,Type*> typePlaceholders;

    static Type* getTypePlaceholder(const QString & name);
public:
    Type(QObject * parent, const QString & name,bool primitive);
    Type(QObject * parent, const QString & name);
    bool getPrimitive() const;
    static Type* typeForName(const QString &name);
    bool getIsPlaceholder() const;
    void setIsPlaceholder(bool newIsPlaceholder);
    QString getName() const;

    static void initPrimitiveTypes();

    virtual Type * getPlusOperatorType(Type * other);
    bool isInt32Type() const;
};

