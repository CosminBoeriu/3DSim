#include "vector.h"

class Line{
private:
    std::array<Vector, 2>a;
public:
    Line(const Vector& v1, const Vector& v2): a(std::array<Vector, 2>{v1, v2}){}

};