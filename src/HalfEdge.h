#pragma once

#include "ofMain.h"

namespace ofxHem {

    class Vertex;
    class Face;

    class HalfEdge {
        public:
            HalfEdge();
            shared_ptr<Vertex> getVertex();
            shared_ptr<Face> getFace();
            shared_ptr<HalfEdge> getNextHalfEdge();
            shared_ptr<HalfEdge> getOppositeHalfEdge();
            void setVertex(shared_ptr<Vertex> _vertex);
            void setFace(shared_ptr<Face> _face);
            void setNextHalfEdge(shared_ptr<HalfEdge> _nextHalfEdge);
            void setOppositeHalfEdge(shared_ptr<HalfEdge> _oppositeHalfEdge);
        private:
            shared_ptr<Vertex> vertex;
            shared_ptr<Face> face;
            shared_ptr<HalfEdge> nextHalfEdge;
            shared_ptr<HalfEdge> oppositeHalfEdge;
    };
    
}
