#pragma once

#include "ofMain.h"

namespace ofxHem {

    class HalfEdge;

    class Face {
        public:
            Face();
            shared_ptr<HalfEdge> getHalfEdge();
            glm::vec3 getCenter();
            glm::vec3 getNormal();
            void setHalfEdge(shared_ptr<HalfEdge> _halfEdge);
            void setCenter(glm::vec3 _center);
            void setNormal(glm::vec3 _normal);
        private:
            shared_ptr<HalfEdge> halfEdge;
            glm::vec3 center;
            glm::vec3 normal;
    };
    
}
