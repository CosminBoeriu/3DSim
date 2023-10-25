#pragma once
#include "frustum.h"

class Projection: public Shape{
private:
    std::vector<bool>updatedVertexes;
    sf::VertexArray projectedPoints;
    sf::VertexArray projectedSurfaces;
    sf::VertexArray projectedEdges;
    std::vector<sf::Color> colorEdges = {sf::Color(sf::Color::White), sf::Color(sf::Color::Red), sf::Color(sf::Color::Blue), sf::Color(sf::Color::Green)};
public:
    Projection(const std::vector<Vector>& iv, const std::vector<std::vector<int>>& conn, const std::vector<std::vector<int>>& fcs, int x): Shape(iv, conn, fcs, x){}
    void calculate_projection_coordinates(const Camera& cam){
        this->transformedVec = cam.calculate_coordinates_of_shape(this->transformedVec);
    }
    [[nodiscard]] virtual std::unique_ptr<Shape> clone() const override{
        return std::make_unique<Projection>(*this);
    };
    Projection(const Shape& oth): Shape(oth){}
    void generate_sfml_surfaces(){
        projectedPoints = sf::VertexArray(sf::Points, transformedVec.size());
        // std::sort(transformedVec.begin(), transformedVec.end());
        for(int i = 0; i < connections.size(); i++){
            projectedPoints[i].position = sf::Vector2f(transformedVec[i][0], transformedVec[i][1]);
            projectedPoints[i].color = colorEdges[i];
        }
        int count = 0;
        projectedEdges = sf::VertexArray(sf::Lines, 2 * edges);
        for(int i = 0; i < connections.size(); i++) {
            for (int j = 0; j < connections[i].size(); j++){
                    if( i < connections[i][j]) {
                        projectedEdges[count++] = projectedPoints[i];
                        projectedEdges[count++] = projectedPoints[connections[i][j]];
                    }
                }
        }
    }
    sf::VertexArray get_edges(){
        return projectedEdges;
    }
    friend std::ostream& operator<<(std::ostream& output, const Projection& myProj) {
        for(int i = 0; i < myProj.transformedVec.size(); i++)
            std::cout << myProj.transformedVec[i];
        return output;
    }
    void update(const Camera& cam){
        Shape::update();
        calculate_projection_coordinates(cam);
        generate_sfml_surfaces();
    }
};