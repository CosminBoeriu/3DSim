#include "shape.h"

class Camera{
protected:
    double alpha, beta; /// ALPHA = rotation around OX, BETA = rotation around OY
    std::vector<Vector>base;  //
    Vector offset = Vector(4);
public:
    Camera(): alpha(0), beta(0){
        base.push_back(Vector(std::vector<double>{1, 0, 0, 1}));
        base.push_back(Vector(std::vector<double>{0, 1, 0, 1}));
        base.push_back(Vector(std::vector<double>{0, 0, 1, 1}));
    }
    Vector calculate_new_coordinates(const Vector& v){
        Vector rez(4); rez[3] = 1;
        std::vector<Vector>copy = base;
        double det = Matrix::determinant(copy);
        copy[0] = v; double detx = Matrix::determinant(copy);
        copy[0] = base[0]; copy[1] = v; double dety = Matrix::determinant(copy);
        copy[1] = base[1]; copy[2] = v; double detz = Matrix::determinant(copy);
        if(std::abs(detx) > epsilon)
            rez[0] = det / detx;
        else
            rez[0] = epsilon;
        if(std::abs(detz) > epsilon)
            rez[1] = det / dety;
        else
            rez[1] = epsilon;
        if(std::abs(detz) > epsilon)
            rez[2] = det / detz;
        else
            rez[2] = epsilon;
        return rez;
    }


};