#pragma once

#include "ofMain.h"
#include <unordered_set>

namespace ofxHem {

    class HalfEdge;
    class Face;

    class Vertex {
        public:
            Vertex();
            Vertex(glm::vec3 _position, glm::vec3 _normal);
            glm::vec3 getPosition();
            glm::vec3 getNormal();
            vector<shared_ptr<Face>> getFaces();
            void setPosition(glm::vec3 _position);
            void setNormal(glm::vec3 _normal);
            void addFace(shared_ptr<Face> _face);
        private:
            glm::vec3 position;
            glm::vec3 normal;
            unordered_set<shared_ptr<Face>> faces;
    };
    
}
