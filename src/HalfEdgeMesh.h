#pragma once

#include "ofMain.h"
#include "Vertex.h"
#include "HalfEdge.h"
#include "Face.h"
#include <unordered_set>

namespace ofxHem {
    class HalfEdgeMesh {
        public:
            HalfEdgeMesh();
            HalfEdgeMesh(ofMesh _mesh);
            ofMesh getMesh();
            vector<shared_ptr<Vertex>> getVertices();
            vector<shared_ptr<HalfEdge>> getHalfEdges();
            vector<shared_ptr<Face>> getFaces();
            HalfEdgeMesh subdivide();
            void calculateNormals();
        private:
            void calculateFaceNormals();
            void calculateVertexNormals();
            ofMesh mesh;
            vector<shared_ptr<Vertex>> vertices;
            vector<shared_ptr<HalfEdge>> halfEdges;
            vector<shared_ptr<Face>> faces;
    };
}
