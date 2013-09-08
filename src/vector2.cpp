#include "vector2.h"
#include <math.h>
#include <iostream>
vector2::vector2()
{
    x = y = 0.0f;
}
vector2::vector2(const float& a,const float& b)
{
    x=a;
    y=b;
}
vector2 vector2::operator+ (const vector2& b) const
{
    vector2 temp;
    temp.x=x+b.x;
    temp.y=y+b.y;
    return temp;
}
vector2& vector2::operator+= (const vector2& b)
{
    if(this!=&b)
    {
        x=x+b.x;
        y=y+b.y;
    }
    return *this;
}
vector2 vector2::operator-(const vector2& b) const
{
    vector2 temp;
    temp.x=x-b.x;
    temp.y=y-b.y;
    return temp;
}
vector2& vector2::operator-=(const vector2& b)
{
    if(this!=&b)
    {
        x=x-b.x;
        y=y-b.y;
    }
    return *this;
}
float vector2::operator* (const vector2& b) const
{
    return (x*b.x+y*b.y);
}
vector2 vector2::operator* (const float& b) const
{
    vector2 temp;
    temp.x=x*b;
    temp.y=y*b;
    return temp;
}
vector2& vector2::operator*= (const float& b)
{
    x=x*b;
    y=y*b;
    return *this;
}
vector2 vector2::operator/ (const float& b) const
{
    vector2 temp=vector2(0.0f,0.0f);
    if(b>0)
    {
        temp.x=x/b;
        temp.y=y/b;
    }
    return temp;
}
vector2& vector2::operator/= (const float& b)
{
    if(b>0)
    {
        x=x/b;
        y=y/b;
    }
    return *this;
}
void vector2::normalize()
{
    float dist = sqrt(x*x+y*y);
    x/=dist;
    y/=dist;
}
void vector2::normalize(const float& dist)
{
    x/=dist;
    y/=dist;
}
vector2 vector2::normalized() const
{
    float dist = sqrt(x*x+y*y);
    return vector2(x/dist,y/dist);
}
vector2 vector2::normalized(const float& dist) const
{
    return vector2(x/dist,y/dist);
}
float vector2::length() const
{
    return sqrt(x*x+y*y);
}

std::ostream& operator<<(std::ostream& out, const vector2& c)
{
    out << '(' << c.x << ',' << c.y << ')' ;
    return out;
}
vector2 operator* (const float& b, const vector2& c)
{
    vector2 temp;
    temp.x=c.x*b;
    temp.y=c.y*b;
    return temp;
}
vector2 lerp(double t,const vector2& vec1,const vector2& vec2)
{
    return (vec2-vec1)*t+vec1;
}
vector2 qerp(double t,const vector2& vec0,const vector2& vec1,const vector2& vec2,const vector2& vec3)
{
    double t2=t*t;
    vector2 a0=vec3-vec2-vec0+vec1;
    vector2 a1=vec0-vec1-a0;
    vector2 a2=vec2-vec0;
    return a0*t*t2+a1*t2+a2*t+vec1;
}
