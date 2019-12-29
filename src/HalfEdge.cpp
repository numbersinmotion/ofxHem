#include "HalfEdge.h"

namespace ofxHem {

    HalfEdge::HalfEdge() {
        vertex = nullptr;
        face = nullptr;
        nextHalfEdge = nullptr;
        oppositeHalfEdge = nullptr;
    }

    shared_ptr<Vertex> HalfEdge::getVertex() {
        return vertex;
    }

    shared_ptr<Face> HalfEdge::getFace() {
        return face;
    }

    shared_ptr<HalfEdge> HalfEdge::getNextHalfEdge() {
        return nextHalfEdge;
    }

    shared_ptr<HalfEdge> HalfEdge::getOppositeHalfEdge() {
        return oppositeHalfEdge;
    }

    void HalfEdge::setVertex(shared_ptr<Vertex> _vertex) {
        vertex = _vertex;
    }

    void HalfEdge::setFace(shared_ptr<Face> _face) {
        face = _face;
    }

    void HalfEdge::setNextHalfEdge(shared_ptr<HalfEdge> _nextHalfEdge) {
        nextHalfEdge = _nextHalfEdge;
    }

    void HalfEdge::setOppositeHalfEdge(shared_ptr<HalfEdge> _oppositeHalfEdge) {
        oppositeHalfEdge = _oppositeHalfEdge;
    }

}
