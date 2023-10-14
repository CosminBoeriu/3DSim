#pragma once
#include "matrix.h"

class LineSegment{
protected:
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

class rotationAxis: public LineSegment{
    /**THIS CLASS IS SPECIFICALLY MADE FOR VECTORS WITH 4 DIMENSIONS**/
private:
    double alpha, beta; // alpha = angle between V, beta = angle between V' on XZ and Z
public:
    explicit rotationAxis(const Vector& v1, const Vector& v2 = Vector(4)){
        Vector v = v2 + (v1 * -1);
        ends[0] = Vector(4);
        ends[1] = v;
        if(v[2] < 0)
            ends[1] = (v * -1);
        Vector projection = ends[1];
        projection[1] = 0;
        alpha = ends[1].calculate_angle(projection);
        beta = projection.calculate_angle(Vector(std::vector<double>{0, 0, ends[1][2], 1}));
    }
    Vector rotateAroundAxis(const Vector& v, double angle) const{
        Vector rez = v + ends[1] * -1;
        rez = rotationMatrix::rotateAroundAxis(rez, alpha, 0);
        rez = rotationMatrix::rotateAroundAxis(rez, beta, 1);
        rez = rotationMatrix::rotateAroundAxis(rez, angle, 2);
        rez = rotationMatrix::rotateAroundAxis(rez, -beta, 1);
        rez = rotationMatrix::rotateAroundAxis(rez, -alpha, 0);
        rez = rez + ends[1];
        return rez;
    };
};