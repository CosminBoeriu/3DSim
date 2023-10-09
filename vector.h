#include <SFML/Graphics.hpp>
#include <cmath>
#define PI 3.14159265359

class Vector{
private:
    std::vector<double>components;
public:
    explicit Vector(unsigned long long size = 0){  // Initializes a Vector full of 0's of size
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
    Vector operator*(double factor) const{
        Vector v(this->components.size());
        for(long long i = 0; i < this->components.size(); i++)
            v.components[i] = this->components[i] * factor;
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
