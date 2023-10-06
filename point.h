#include <SFML/Graphics.hpp>
#include <cmath>
#define PI 3.14159265359

class Vector{
private:
    std::vector<double>components;
public:
    explicit Vector(unsigned long long size){  // Initializes a Vector full of 0's of size
        for(int i = 0; i < size; i++)
            components.push_back(0);
    }
    explicit Vector( const std::vector<double>&v){  // Takes a std::vector and initializes a Vector with said elements
        for(auto i : v){
            components.push_back(i);
        }
    }
    Vector(const Vector& other){
        components.clear();
        for(double i : other.components)
            components.push_back(i);
    }
    Vector& operator=(const Vector& other){  // Assigment operator
        if(&other == this){
            return *this;
        }
        components.clear();
        for(double i : other.components)
            components.push_back(i);
        return *this;
    }
    Vector operator*(double alpha){
        Vector v(this->components.size());
        for(long long i = 0; i < this->components.size(); i++)
            this->components[i] = v.components[i] * alpha;
        return v;
    }
    double operator*(const Vector& other) const{
        double sum = 0;
        if(other.components.size() != this->components.size())
            throw std::invalid_argument("Sizes of Vectors are not equal");
        for(long long i = 0; i < this->components.size(); i++)
            sum += components[i] * other.components[i];
        return sum;
    }
    double operator*(const std::vector<double>& v) const{
        double sum = 0;
        if(v.size() != this->components.size())
            throw std::invalid_argument("Sizes of Vectors are not equal");
        for(long long i = 0; i < this->components.size(); i++)
            sum += components[i] * v[i];
        return sum;
    }
    Vector operator+(const Vector& other){
        if(other.components.size() != this->components.size())
            throw std::invalid_argument("Sizes of Vectors are not equal");
        Vector v(this->components.size());
        for(long long i = 0; i < this->components.size(); i++)
            this->components[i] = v.components[i];
        return v;
    }
    double& operator[](unsigned long long index){  // Returns a reference to components[index]
        if(index > components.size())
            throw std::invalid_argument("Array index out of bounds");
        return components[index];
    }
    double length() const {  // Returns modulus of vector
        double sum = 0;
        for(double elem : components)
            sum += elem * elem;
        return sqrt(sum);
    }

    double calculate_angle(const Vector& other) const{  // Calculates the angle between this vector and argument
        return *this * other / (this->length() * other.length());
    }
    unsigned long long get_size() const{  // Returns the size of vector
        return components.size();
    }

};


class Matrix{
private:
    std::vector<Vector>mat; // Matrix that has size1 lines and size2 columns. We can assume that Vectors compose the lines
    unsigned long long size1, size2;
public:
    Matrix(unsigned long long size1, unsigned long long size2): size1(size1), size2(size2){
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
    Vector& operator[](unsigned long long index){
        if(index >= size1 )
            throw std::invalid_argument("Array index out of bounds");
        return mat[index];
    }
};

