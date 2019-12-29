#include "Vertex.h"

namespace ofxHem {

    Vertex::Vertex() {
        
    }

    Vertex::Vertex(glm::vec3 _position, glm::vec3 _normal) {
        position = _position;
        normal = _normal;
    }

    glm::vec3 Vertex::getPosition() {
        return position;
    }

    glm::vec3 Vertex::getNormal() {
        return normal;
    }

    vector<shared_ptr<Face>> Vertex::getFaces() {
        return vector<shared_ptr<Face>>(faces.begin(), faces.end());
    }

    void Vertex::setPosition(glm::vec3 _position) {
        position = _position;
    }

    void Vertex::setNormal(glm::vec3 _normal) {
        normal = _normal;
    }


    void Vertex::addFace(shared_ptr<Face> _face) {
        faces.insert(_face);
    }
    
}
