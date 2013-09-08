#include "complex.h"
#include <math.h>
#include <iostream>
Complex::Complex()
{
    x = y = 0.0f;
}
Complex::Complex(const double& a,const double& b)
{
    x=a;
    y=b;
}
Complex Complex::operator* (const Complex& b) const
{
    Complex temp=*this;
    temp*=b;
    return temp; 
}
Complex& Complex::operator*= (const Complex& b)
{ //(x+yi)(bx+byi)=x bx-y by + i(y bx + x by)
    double tmp=x*b.x-y*b.y;
    y=y*b.x+x*b.y;
    x=tmp;
    return *this;
}
Complex Complex::operator/(const Complex& b) const
{
    Complex temp=*this;
    temp/=b;
    return temp; 
}
Complex& Complex::operator/=(const Complex& b)
{// (x+yi)/(bx+byi)=(x+yi)(bx-byi)/(bx bx + by by)=1/length2() * (x bx + y by + i(y bx - x by))
    double mult=1.0/b.length2();
    double tmp=(x*b.x+y*b.y)*mult;
    y=(y*b.x-x*b.y)*mult;
    x=tmp;
    return *this;
}
Complex Complex::operator+ (const Complex& b) const
{
    Complex temp=*this;
    temp+=b;
    return temp; 
}
Complex& Complex::operator+= (const Complex& b)
{
    x=x+b.x;
    y=y+b.y;
    return *this;
}
Complex Complex::operator-(const Complex& b) const
{
    Complex temp=*this;
    temp-=b;
    return temp; 
}
Complex& Complex::operator-=(const Complex& b)
{
    x=x-b.x;
    y=y-b.y;
    return *this;
}


//Complex <-> Scalar operators
Complex Complex::operator+ (const double& b) const
{
    Complex temp=*this;
    temp+=b;
    return temp;
}
Complex& Complex::operator+= (const double& b)
{
    x=x+b;
    y=y;
    return *this;
}
Complex Complex::operator- (const double& b) const
{
    Complex temp=*this;
    temp-=b;
    return temp;
}
Complex& Complex::operator-= (const double& b)
{
    x=x-b;
    y=y;   
    return *this;
}

Complex Complex::operator* (const double& b) const
{
    Complex temp=*this;
    temp*=b;
    return temp;
}
Complex& Complex::operator*= (const double& b)
{
    x=x*b;
    y=y*b;
    return *this;
}
Complex Complex::operator/ (const double& b) const
{
    Complex temp=*this;
    temp/=b;
    return temp;
}
Complex& Complex::operator/= (const double& b)
{
    x=x/b;
    y=y/b;   
    return *this;
}
double Complex::length() const
{
    return sqrt(x*x+y*y);
}
double Complex::length2() const
{
    return x*x+y*y;
}

std::ostream& operator<<(std::ostream& out, const Complex& c)
{
	out << '(' << c.x << ',' << c.y << ')' ;

    return out;
}
Complex operator* (const double& b, const Complex& c)
{
    Complex temp;
    temp.x=c.x*b;
    temp.y=c.y*b;
    return temp;
}

Complex operator/ (const double& b, const Complex& c)
{
    Complex temp;
    temp=(Complex(b,0)/c);
    return temp;
}
Complex operator+ (const double& b, const Complex& c)
{
    Complex temp;
    temp.x=c.x+b;
    temp.y=c.y;
    return temp;
}
Complex operator- (const double& b, const Complex& c)
{
    Complex temp;
    temp.x=b-c.x;
    temp.y=-c.y;
    return temp;
}
