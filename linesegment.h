#pragma once
#include "matrix.h"

class LineSegment{
private:
    std::array<Vector, 2>ends;
public:
    explicit LineSegment(const Vector& v1 = Vector(), const Vector& v2 = Vector()){
        ends[0] = v1;
        ends[1] = v2;
    }
    LineSegment(const Vector& v1, double alpha, double beta, double length){ // 0 <= alpha, beta <= 2 * PI
        /*Angle alpha determines the angle from OX to line segment projection on OXZ and beta determines angle from OXZ plane*/
        Vector rez(std::vector<double>{length, 0, 0, 1});
        ends[0] = v1;
        Vector midpoint = rotationMatrix::rotateAroundAxis(rez, alpha, 2);
        ends[1] = rotationMatrix::rotateAroundAxis(midpoint, beta, 1);
    }
    std::array<Vector, 2> get_ends(){
        return ends;
    }
};

class AxisRotation: public LineSegment{
    /**THIS CLASS IS SPECIFICALLY MADE FOR VECTORS WITH 4 DIMENSIONS**/
private:
    double alpha, beta; // alpha = angle between V, beta = angle between V' on XZ and Z
public:
    AxisRotation(const Vector& v1, const Vector& v2){
        Vector v = v2 + (v1 * -1);
        if(v[2] < 0)
            v = (v * -1);
        Vector projection = v;
        projection[1] = 0;
        alpha = v.calculate_angle(projection);
        beta = projection.calculate_angle(Vector(std::vector<double>{0, 0, v[2], 1}));
    }
    Vector rotateAroundAxis();
};