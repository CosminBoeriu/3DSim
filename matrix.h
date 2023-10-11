#pragma once
#include <memory>
#include "vector.h"
#define PRECISION_ANGLE 100

class Matrix{
protected:
    std::vector<Vector>mat; // Matrix that has size1 lines and size2 columns. We can assume that Vectors compose the lines
    unsigned long long size1, size2;
public:
    explicit Matrix(unsigned long long size1 = 0, unsigned long long size2 = 0): size1(size1), size2(size2){
        for(int i = 0; i < size1; i++){
            mat.emplace_back(size2);
        }
    }
    explicit Matrix(const std::vector<std::vector<double>>&v){
        size1 = v.size(); size2 = v[0].size();
        for(int i = 0; i < size1; i++){
            Vector v1(size2);
            for(int j = 0; j < size2; j++){
                v1[j] = v[i][j];
            }
            mat[i] = v1;
        }
    }
    Matrix(const Matrix& other){
        mat.clear();
        for(int i = 0; i < other.size1; i++){
            mat[i] = other.get_row(i);
        }
        size1 = other.size1;
        size2 = other.size2;
    }
    Matrix& operator=(const Matrix& other){
        if(&other == this){
            return *this;
        }
        mat.clear();
        for(int i = 0; i < other.size1; i++){
            mat[i] = other.get_row(i);
        }
        size1 = other.size1;
        size2 = other.size2;
        return *this;
    }
    static Matrix identityMatrix(unsigned long long size){
        Matrix rez(size, size);
        for(int i = 0; i < size; i++)
            rez[i][i] = 1;
        return rez;
    }
    Vector operator*(const Vector& v) const{
        Vector rez = Vector(size1);
        if( v.get_size() != size2 ){
            throw std::invalid_argument("Matrix and Vector sizes are not compatible for product operation");
        }
        for(int i = 0; i < size1; i++){
            rez[i] = mat[i] * v;
        }
        return rez;
    }
    Matrix operator*(double factor) const{
        Matrix rez(*this);
        for(int i = 0; i < size1; i++){
            rez[i] = mat[i] * factor;
        }
        return rez;
    }
    Vector& operator[](unsigned long long index){
        if(index >= size1 )
            throw std::invalid_argument("Array index out of bounds");
        return mat[index];
    }
    Vector get_row(unsigned long long index) const{
        return {(mat[index])};
    }
};

class scaleMatrix: public Matrix{
private:
    double scale_factor;
public:
    scaleMatrix(unsigned long long size, double scale_factor): Matrix(Matrix::identityMatrix(size) * scale_factor), scale_factor(scale_factor){
        mat[size-1][size-1] = 1;
    };
};

class translateMatrix: public Matrix{
private:
    translateMatrix(unsigned long long size, Vector newposition): Matrix(size, size){
        for(int i = 0; i < size; i++)
            mat[i][size-1] = newposition[i];
    }
};

class rotationMatrix: public Matrix{
public:
    /**This map is a static precalculated structure that stores rotation matrices for every angle with .00 precision and around every axis **/
    inline static std::map<int, std::vector<std::shared_ptr<Matrix>>>PRECALCULATED_ROTATION_MATRIX;
public:
    static void CALCULATE_ROTATION_MATRIX(){
        for(int i = 0; i < (int)(2 * PI * PRECISION_ANGLE); i++){
            PRECALCULATED_ROTATION_MATRIX[i] = std::vector<std::shared_ptr<Matrix>>();
            for(int j = 0; j < 3; j++ ) {
                PRECALCULATED_ROTATION_MATRIX[i].push_back(std::shared_ptr<Matrix>(new rotationMatrix((double)i / PRECISION_ANGLE, j, 4)));
            }
        }
    }
    rotationMatrix(double angle, int axis, int size = 4): Matrix(size, size){ // axis: 0 = x, 1 = y, 2 = z
        double cosAngle = std::cos(angle);
        double sinAngle = std::sin(angle);
        for(int i = 0; i < size; i++)
            mat[i][i] = 1;
        if(axis == 0){
            mat[1][1] = mat[2][2] = cosAngle;
            mat[1][2] = sinAngle;
            mat[2][1] = -sinAngle;
            return;
        }
        if(axis == 1){
            mat[0][0] = mat[2][2] = cosAngle;
            mat[0][2] = -sinAngle;
            mat[2][0] = sinAngle;
            return;
        }
        if(axis == 2){
            mat[0][0] = mat[1][1] = cosAngle;
            mat[0][1] = sinAngle;
            mat[1][0] = -sinAngle;
        }
    }
    static Vector rotateAroundAxis(const Vector& v, double angle, int axis){
        /** Axis can be either OX, OY, OZ.
        0 < ANGLE < 2 * PI determines the rotation angle of vector v around said axis **/
        while(angle < 0)
            angle += 2 * PI;
        std::shared_ptr<Matrix>m = (PRECALCULATED_ROTATION_MATRIX[(int)(angle * PRECISION_ANGLE)][axis]);
        Vector rez = (*m) * v;
        return rez;
    }
};


