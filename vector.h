#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#define PI 3.14159265359
#define epsilon 0.000001

class Vector{
private:
    std::vector<double>components;
public:
    explicit Vector(unsigned long long size = 0){  // Initializes a Vector full of 0's of size
        components.clear();
        for(int i = 0; i < size; i++)
            components.push_back(0);
    }
    explicit Vector(const std::vector<double>&v){  // Takes a std::vector and initializes a Vector with said elements
        components.clear();
        for(int i = 0; i < v.size(); i++){
            components.push_back(v[i]);
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
        for(int i = 0; i < other.components.size(); i++)
            components.push_back(other.components[i]);
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& output, const Vector& myVec) {
        for(int i = 0; i < myVec.components.size(); i++)
            std::cout << myVec.components[i] << ' ';
        return output;
    }
    bool operator<(const Vector& other){
        return this->components[2] < other.components[2];
    }
    Vector operator*(double factor) const{
        ///It does not take into consideration the last coordinate of the vector
        Vector v(this->components.size());
        for(long long i = 0; i < this->components.size()-1; i++)
            v.components[i] = this->components[i] * factor;
        return v;
    }
    double multiply(const Vector& other) const{
        double sum = 0;
        if(other.components.size() != this->components.size())
            throw std::invalid_argument("Sizes of Vectors are not equal");
        for(long long i = 0; i < this->components.size(); i++)
            sum += components[i] * other.components[i];
        return sum;
    }
    double operator*(const Vector& other) const{
        ///It does not take into consideration the last coordinate of the vector
        double sum = 0;
        if(other.components.size() != this->components.size())
            throw std::invalid_argument("Sizes of Vectors are not equal");
        for(long long i = 0; i < this->components.size()-1; i++)
            sum += components[i] * other.components[i];
        return sum;
    }
    double operator*(const std::vector<double>& v) const{
        ///It does not take into consideration the last coordinate of the vector
        double sum = 0;
        if(v.size() != this->components.size())
            throw std::invalid_argument("Sizes of Vectors are not equal");
        for(long long i = 0; i < this->components.size()-1; i++)
            sum += components[i] * v[i];
        return sum;
    }
    Vector operator+(const Vector& other) const{
        if(other.components.size() != this->components.size())
            throw std::invalid_argument("Sizes of Vectors are not equal");
        Vector v(this->components.size());
        for(long long i = 0; i < this->components.size(); i++)
            v.components[i] = this->components[i] + other.components[i];
        return v;
    }
    double& operator[](unsigned long long index){  // Returns a reference to components[index]
        if(index > components.size())
            throw std::invalid_argument("Array index out of bounds");
        return components[index];
    }
    [[nodiscard]] double length() const {  // Returns modulus of vector
        double sum = 0;
        for(int i = 0; i < components.size()-1; i++)
            sum += components[i] * components[i];
        return sqrt(sum);
    }
    [[nodiscard]] double distance(const Vector& v) const{
        double sum = 0;
        for( int i = 0; i < v.get_size(); i++ ){
            sum = sum + (components[i] - v.components[i]) * (components[i]  * v.components[i]);
        }
        return std::sqrt(sum);
    }
    Vector cross_product(const Vector& other) const{
        return Vector(std::vector<double>{components[1] * other.components[2] - components[2] * other.components[1],
                                          components[0] * other.components[2] - components[2] * other.components[0],
                                          components[0] * other.components[1] - components[1] * other.components[0],
                                          1});
    }

    double calculate_angle(const Vector& other) const{  // Calculates the angle between this vector and argument
        double val = (*this * other ) / (other.length() * this->length());
        if(val >= 1 or val <= -1){
            std::cout<<val;
            val = val > 1 ? val - epsilon : val + epsilon;
        }
        if(std::abs(val) < epsilon)
            val = epsilon;
        if( val == val )
            return std::acos(val);
        else
            return 0;
    }
    unsigned long long get_size() const{  // Returns the size of vector
        return components.size();
    }
    double get_elem(int i) const {
        return components[i];
    }
    [[nodiscard]] Vector get_normalised() const{
        return *this * (1 / this->length());
    }
    Vector get_perpendicular_vector(Vector other) const{
        //TODO IMPLEMENT FOR OTHER DIMENSIONS !!!
        if(other.components.size() != 4 )
            throw std::invalid_argument("TO BE IMPLEMENTED");
        Vector v(std::vector<double>{components[1] * other[2] - components[2] * other[1],
                                        components[2] * other[0] - components[0] * other[2],
                                        components[0] * other[1] - components[1] * other[0],
                                        1});
        if(v[2] < 0)
            return v * -1;
        return v.get_normalised();
    }
};
