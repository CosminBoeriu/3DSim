#pragma once
#include "linesegment.h"

class Shape{
protected:
    std::vector<Vector>initialVec;
    std::vector<std::vector<int>>connections;
    std::vector<std::vector<int>>trig;
    std::vector<Vector>transformedVec;
    rotationAxis axisRot;
    double rotationSpeed = 0.01, angle = 0;
    Vector center, offset;
    int edges;
public:
    Shape(const std::vector<Vector>& iv, const std::vector<std::vector<int>>& conn, const std::vector<std::vector<int>>& fcs, int x): initialVec(iv), connections(conn), trig(fcs), edges(x){
        center = Vector(4);
        offset = Vector(4);
        for(int i = 0; i < initialVec.size(); i++) {
            center = center + initialVec[i];
            transformedVec.push_back(initialVec[i]);
        }
        center = center * (1.0f / initialVec.size());
        axisRot = rotationAxis(initialVec[0], center);
        ///ONLY FOR 4DIMENSION VECTORS
    }
    [[nodiscard]] virtual std::unique_ptr<Shape> clone() const = 0;
    void calculate_transformed(){
        angle = angle + rotationSpeed;
        for(int i = 0; i < initialVec.size(); i++)
            transformedVec[i] = axisRot.rotateAroundAxis(initialVec[i], angle) + offset;
    }
    void move_shape(const Vector& v){
        offset = offset + v;
    }
    void set_rotation_axis(const rotationAxis& ra){
        axisRot = ra;
    }
    void set_rotation_speed(double speed){
        rotationSpeed = speed;
    }
    [[nodiscard]] std::vector<Vector> get_transformed_coordinates() const{
        return this->transformedVec;
    }
    virtual void update(){
        calculate_transformed();
    }
};

class Tetrahedron: public Shape{
public:
    Tetrahedron(): Shape(std::vector<Vector>{Vector({2000, 2000, 2000, 1}), Vector({2000, 2000, 3000, 1}), Vector({3000, 2000, 4000, 1}), Vector({4000, 3000, 4000, 1})},
                         std::vector<std::vector<int>>{{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}},
                         std::vector<std::vector<int>>{{0, 1, 2}, {0, 1, 3}, {0, 2, 3}, {1, 2, 3}}, 6){

    };
    [[nodiscard]] virtual std::unique_ptr<Shape> clone() const override{
        return std::make_unique<Tetrahedron>(*this);
    };
};
