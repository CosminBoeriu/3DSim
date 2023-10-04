#include <SFML/Graphics.hpp>
#include <cmath>
#define PI 3.14159265359

class Vector{
private:
    std::vector<double>components;
public:
    explicit Vector(unsigned long long size){
        for(int i = 0; i < size; i++)
            components.push_back(0);
    }
    explicit Vector( const std::vector<double>&v){
        for(auto i : v){
            components.push_back(i);
        }
    }
    Vector& operator=(const Vector& other){
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
    Vector operator+(const Vector& other){
        if(other.components.size() != this->components.size())
            throw std::invalid_argument("Sizes of Vectors are not equal");
        Vector v(this->components.size());
        for(long long i = 0; i < this->components.size(); i++)
            this->components[i] = v.components[i];
        return v;
    }
    double& operator[](unsigned long long index){
        if(index > components.size())
            throw std::invalid_argument("Array index out of bounds");
        return components[index];
    }
    double length() const {
        double sum = 0;
        for(double elem : components)
            sum += elem * elem;
        return sqrt(sum);
    }
    double dot_product(const Vector& other ) const {
        double sum = 0;
        if(other.components.size() != this->components.size())
            throw std::invalid_argument("Sizes of Vectors are not equal");
        for(long long i = 0; i < this->components.size(); i++)
            sum += components[i] * other.components[i];
        return sum;
    }
    double dot_product(const std::vector<double>&v) const{
        double sum = 0;
        if(v.size() != this->components.size())
            throw std::invalid_argument("Sizes of Vectors are not equal");
        for(long long i = 0; i < this->components.size(); i++)
            sum += components[i] * v[i];
        return sum;
    }
    double calculate_angle(const Vector& other) const{
        return this->dot_product(other) / (this->length() * other.length());
    }
    unsigned long long get_size(){
        return components.size();
    }

};


class Matrix{
private:
    std::vector<std::vector<double>>mat;
    unsigned long long size1, size2;
public:
    Matrix(unsigned long long size1, unsigned long long size2): size1(size1), size2(size2){
        for(int i = 0; i < size1; i++){
            std::vector<double>v1;
            for(int j = 0; j < size2; j++ ){
                v1.push_back(0);
            }
            mat.push_back(v1);
        }
    }
    explicit Matrix(double m[4][4]){  //Most used matrix deserves its own initialisation
        size1 = size2 = 4;
        for(int i = 0; i < size1; i++){
            std::vector<double>v1;
            for(int j = 0; j < size2; j++){
                v1.push_back(m[i][j]);
            }
            mat.push_back(v1);
        }
    }
    Vector& operator*(const Vector& v) const{
        Vector rezultat = Vector(4);
    }
};

