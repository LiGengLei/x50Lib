#include <xCCore/xCCore.h>
#include <iostream>

/*
class cSize
{
public:
  cRectangle()
    : mLength(0.0)
    , Length(this, &cSize::setHeight, &cSize::getHeight)
    , Area(this,  &cSize::setWidth, &cSize::getWidth)
  {
  }

  virtual double _ret_rref setHeight(double _inp_ref val)
  {
    return mHeight = val;
  }

  virtual double _ret_rref setHeight() const
  {
    return mHeight;
  }

  virtual double _ret_rref setWidth(double _inp_ref val)
  {
    return mWidth = val;
  }

  virtual double _ret_rref setWidth() const
  {
    return mWidth;
  }

public:
  xcr::xproperty<cSize, double> Height;
  xcr::xproperty<cSize, double> Width;

protected:
  double mHeight;
  double mWidth;
};
*/

class cRectangle
{
public:
  cRectangle()
    : mSize(0.0)
    , Size(this, &cRectangle::setLength, &cRectangle::getLength)
    , Area(this, &cRectangle::getArea)
  {
  }

  virtual double _ret_rref setLength(double _inp_ref val)
  {
    return mSize = val;
  }

  virtual double _ret_rref getLength() const
  {
    return mSize;
  }

  virtual double _ret_copy getArea() const
  {
    return mSize * mSize;
  }

public:
  xcr::xproperty<cRectangle, double> Size;
  xcr::xrproperty<cRectangle, double> Area;

protected:
  double mSize;
};

int main()
{
  cRectangle test;
  std::cout << "size = " << test.Size << std::endl;
  std::cout << "area = " << test.Area << std::endl;
  test.Size = 1.5;
  std::cout << "size = " << test.Size << std::endl;
  std::cout << "area = " << test.Area << std::endl;
  return 0;
}
