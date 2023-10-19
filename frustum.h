#include "shape.h"

class Camera{
protected:
    double alpha, beta; /// ALPHA = rotation around OX, BETA = rotation around OY; -85 degrees < ALPHA < 85 degrees
    std::vector<Vector>base;  //
    Vector focalPoint = Vector(4), defaultScreenCenter = Vector(4), rotatedScreenCenter = Vector(4);
    double nearDist = 1000, farDist = 10000;
    Matrix transform, distanceMat;
public:
    Camera(): alpha(0), beta(0){
        base.push_back(Vector(std::vector<double>{1, 0, 0, 1}));
        base.push_back(Vector(std::vector<double>{0, 1, 0, 1}));
        base.push_back(Vector(std::vector<double>{0, 0, 1, 1}));
        defaultScreenCenter = Vector(std::vector<double>{0, 0, 1000, 1});
        rotatedScreenCenter = defaultScreenCenter;
        distanceMat = Matrix(4, 4);
        distanceMat[0][0] = nearDist; distanceMat[1][1] = nearDist; distanceMat[2][2] = nearDist + farDist;
        distanceMat[2][3] = - nearDist * farDist; distanceMat[3][2] = 1;
        calculate_matrix();
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
    Vector get_coordinates_of_point(const Vector& v){
        return transform * v;
    }
    void calculate_matrix(){
        transform = Matrix::identityMatrix(4);
        transform.change_column(focalPoint, 3);
        transform = rotationMatrix::get_rotation_matrix(-beta, 1) * rotationMatrix::get_rotation_matrix(-alpha, 0) * transform;
        transform = distanceMat * transform;
    }

};