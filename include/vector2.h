

#ifndef VECTOR2_H
#define VECTOR2_H
#include <iostream>
class vector2
{
public:
    float x;
    float y;
    vector2();
    vector2(const float& a,const float& b);
    vector2 operator+	(const vector2& b) const;	//vector addition
    vector2& operator+=	(const vector2& b);
    vector2 operator-	(const vector2& b) const;	//vector subtraction
    vector2& operator-=	(const vector2& b);
    vector2 operator*	(const float& b) const;	//vector scalar multiplication
    vector2& operator*=	(const float& b);
    vector2 operator/	(const float& b) const;	//vector scalar division
    vector2& operator/=	(const float& b);
    float operator*		(const vector2& b) const;	//dot product
    void normalize();
    void normalize(const float& dist);
    vector2 normalized() const;
    vector2 normalized(const float& dist) const;
    float length() const;
};
vector2 operator* (const float& b, const vector2& c);
std::ostream& operator<<(std::ostream& out, const vector2& c);

vector2 lerp(double t,const vector2& vec1,const vector2& vec2);
vector2 qerp(double t,const vector2& vec0,const vector2& vec1,const vector2& vec2,const vector2& vec3);
#endif // VECTOR2_H
