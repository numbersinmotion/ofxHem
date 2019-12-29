#include "Face.h"

namespace ofxHem {

    Face::Face() {
        halfEdge = nullptr;
    }

    shared_ptr<HalfEdge> Face::getHalfEdge() {
        return halfEdge;
    }

    glm::vec3 Face::getCenter() {
        return center;
    }

    glm::vec3 Face::getNormal() {
        return normal;
    }

    void Face::setHalfEdge(shared_ptr<HalfEdge> _halfEdge) {
        halfEdge = _halfEdge;
    }

    void Face::setCenter(glm::vec3 _center) {
        center = _center;
    }

    void Face::setNormal(glm::vec3 _normal) {
        normal = _normal;
    }
    
}
