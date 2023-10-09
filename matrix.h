#include "vector.h"

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
private:
    static std::map<int, double>sin_preCalc, cos_preCalc;
    static int angleTr(double angle){
        return int(angle * 10000);
    }
    static void preCalc(){
        for(int i = 0; i < 2 * PI * 10000; i++){
            sin_preCalc[i] = sin(double(i)/10000);
            cos_preCalc[i] = cos(double(i)/10000);
        }
    }
};
