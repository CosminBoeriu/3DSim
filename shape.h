#pragma once
#include "linesegment.h"

class Shape{
protected:
    std::vector<Vector>initialVec;
    std::vector<std::vector<int>>connections;
    std::vector<std::vector<int>>faces;
    std::vector<Vector>transformedVec;
    Vector center;
public:
    Shape(const std::vector<Vector>& iv, const std::vector<std::vector<int>>& conn, const std::vector<std::vector<int>>& fcs): initialVec(iv), connections(conn), faces(fcs){
        center = Vector(4);
        for(int i = 0; i < initialVec.size(); i++)
            center = center + initialVec[i];
        center = center * (1.0f / initialVec.size());
        ///ONLY FOR 4DIMENSION VECTORS
    }
    [[nodiscard]] virtual std::unique_ptr<Shape> clone() const = 0;
    void rotate_shape_around_axis(const rotationAxis& ra, double angle){
        for(int i = 0; i < initialVec.size(); i++)
            transformedVec[i] = ra.rotateAroundAxis(initialVec[i], angle);
    }
    void move_shape(const Vector& v){
        for(int i = 0; i < transformedVec.size(); i++)
            transformedVec[i] = transformedVec[i] + v;
    }
};
