#ifndef DEFINES_H
#define DEFINES_H

#define MINI(a, b)  (((a) < (b)) ? (a) : (b))
#define MAXI(a, b)  (((a) > (b)) ? (a) : (b))
#define ABS(a)	   (((a) < 0) ? -(a) : (a))
#define SIGN(a)	   (((a) < 0) ? -1.0 : 1.0)
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#define EPSILON 0.00001
#define LOG100(val) (50.0/log(10.0)*log((float)val + 1.0))
#define EXP100(val) (exp(log(10.0)/50.0*(float)(val))-1.0)

#define FRAME_DURATION 15

#define XML_GLM_VERSION "1.0"

#define TEXTURE_REQUIRED_MAXIMUM 2048
#define CATALOG_TEXTURE_HEIGHT 128
#define SELECTBUFSIZE 512
#define SOURCE_UNIT 10.0
#define CIRCLE_SIZE 8.0
#define CIRCLE_SQUARE_DIST(x,y) ( (x*x + y*y) / (SOURCE_UNIT * SOURCE_UNIT * CIRCLE_SIZE * CIRCLE_SIZE) )
#define DEFAULT_LIMBO_SIZE 1.5
#define MIN_LIMBO_SIZE 1.1
#define MAX_LIMBO_SIZE 3.0
#define DEFAULT_ICON_SIZE 1.0
#define MIN_ICON_SIZE 0.5
#define MAX_ICON_SIZE 2.0
#define MIN_DEPTH_LAYER 0.0
#define MAX_DEPTH_LAYER 30.0
#define MIN_SCALE 0.1
#define MAX_SCALE 200.0
#define DEPTH_EPSILON 0.01
#define BORDER_SIZE 0.4
#define CENTER_SIZE 1.2
#define PROPERTY_DECIMALS 8

#define COLOR_SOURCE 230, 230, 0
#define COLOR_SOURCE_STATIC 230, 40, 40
#define COLOR_SELECTION 0, 180, 50
#define COLOR_SELECTION_AREA 40, 190, 80
#define COLOR_BGROUND 52, 52, 52
#define COLOR_CIRCLE 210, 30, 210
#define COLOR_CIRCLE_MOVE 230, 30, 230
#define COLOR_DRAWINGS 150, 150, 150
#define COLOR_LIMBO 35, 35, 35
#define COLOR_LIMBO_CIRCLE 210, 160, 210
#define COLOR_FADING 25, 25, 25
#define COLOR_FRAME 210, 30, 210
#define COLOR_FRAME_MOVE 230, 30, 230
#define COLOR_CURSOR 13, 148, 224


#include <QtCore>
#include <QtDebug>
#include <QValidator>
#include <QDir>


class folderValidator : public QValidator
{
  public:
    folderValidator(QObject *parent) : QValidator(parent) { }

    QValidator::State validate ( QString & input, int & pos ) const {
      QDir d(input);
      if( d.exists() )
          return QValidator::Acceptable;
      if( d.isAbsolute() )
          return QValidator::Intermediate;
      return QValidator::Invalid;
    }
};

class nameValidator : public QValidator
{
  public:
    nameValidator(QObject *parent) : QValidator(parent) { }

    QValidator::State validate ( QString & input, int & pos ) const {
      if( input.isEmpty() )
          return QValidator::Invalid;
      if( input.length() < 2 )
          return QValidator::Intermediate;
      return QValidator::Acceptable;
    }
};

class AllocationException : public QtConcurrent::Exception {
public:
    virtual QString message() { return "Out of memory"; }
    void raise() const { throw *this; }
    Exception *clone() const { return new AllocationException(*this); }
};

#define CHECK_PTR_EXCEPTION(ptr) if(!(ptr)) AllocationException().raise();

#endif // DEFINES_H
