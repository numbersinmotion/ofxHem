#include "HalfEdgeMesh.h"

namespace ofxHem {

    HalfEdgeMesh::HalfEdgeMesh() {
        
    }

    HalfEdgeMesh::HalfEdgeMesh(ofMesh _mesh): mesh(_mesh) {
        
        if (mesh.getMode() == OF_PRIMITIVE_TRIANGLES) {
            
            map<pair<int, int>, shared_ptr<HalfEdge>> indexLookup;
            
            for (int i = 0; i < mesh.getNumVertices(); i++)
                vertices.push_back(make_shared<Vertex>(Vertex(mesh.getVertices()[i], mesh.getNormals()[i])));
            
            if (!mesh.hasNormals()) {
                // calculate normals
            }
            
            for (int i = 0; i < mesh.getIndices().size() / 3; i++) {
                
                // initialize face and half edges
                faces.push_back(make_shared<Face>(Face()));
                for (int j = 0; j < 3; j++)
                    halfEdges.push_back(make_shared<HalfEdge>(HalfEdge()));
                
                // set up indices
                unsigned int indices[3] = {mesh.getIndices()[3 * i + 0], mesh.getIndices()[3 * i + 1], mesh.getIndices()[3 * i + 2]};
                
                // get position of vertices of triangle
                shared_ptr<Vertex> a = vertices[indices[0]];
                shared_ptr<Vertex> b = vertices[indices[1]];
                shared_ptr<Vertex> c = vertices[indices[2]];
                
                // set up face variables
                faces[faces.size() - 1]->setHalfEdge(halfEdges[halfEdges.size() - 1]);
                
                glm::vec3 faceCenter = (a->getPosition() + b->getPosition() + c->getPosition()) / 3.0f;
                faces[faces.size() - 1]->setCenter(faceCenter);
                
                glm::vec3 faceNormal = glm::normalize((a->getNormal() + b->getNormal() + c->getNormal()) / 3.0f);
                faces[faces.size() - 1]->setNormal(faceNormal);
                
                // if counter-clockwise reverse indices
                if (glm::dot(faceNormal, glm::cross(a->getPosition() - b->getPosition(), c->getPosition() - b->getPosition())) < 0) {
                    for (int j = 0; j < 3; j++)
                        indices[j] = mesh.getIndices()[3 * i + (3 - j - 1)];
                }
                
                for (int j = 0; j < 3; j++) {
                    
                    int jNext = (j + 1) % 3;
                    
                    vertices[indices[j]]->addFace(faces[faces.size() - 1]);
                    
                    halfEdges[halfEdges.size() - 1 - j]->setFace(faces[faces.size() - 1]);
                    halfEdges[halfEdges.size() - 1 - j]->setVertex(vertices[indices[j]]);
                    halfEdges[halfEdges.size() - 1 - j]->setNextHalfEdge(halfEdges[halfEdges.size() - 1 - jNext]);
                    
                    map<pair<int, int>, shared_ptr<HalfEdge>>::iterator findReverse = indexLookup.find(pair<int, int>(indices[jNext], indices[j]));
                    if (findReverse != indexLookup.end()) {
                        halfEdges[halfEdges.size() - 1 - j]->setOppositeHalfEdge(findReverse->second);
                        findReverse->second->setOppositeHalfEdge(halfEdges[halfEdges.size() - 1 - j]);
                    }
                    
                    indexLookup.insert(pair<pair<int, int>, shared_ptr<HalfEdge>>(pair<int, int>(indices[j], indices[jNext]), halfEdges[halfEdges.size() - 1 - j]));
                    
                }
                
            }
            
        }
        
        calculateVertexNormals();
        
    }

    ofMesh HalfEdgeMesh::getMesh() {
        return mesh;
    }

    vector<shared_ptr<Vertex>> HalfEdgeMesh::getVertices() {
        return vertices;
    }

    vector<shared_ptr<HalfEdge>> HalfEdgeMesh::getHalfEdges() {
        return halfEdges;
    }

    vector<shared_ptr<Face>> HalfEdgeMesh::getFaces() {
        return faces;
    }

    HalfEdgeMesh HalfEdgeMesh::subdivide() {
        
        if (mesh.getMode() == OF_PRIMITIVE_TRIANGLES) {
            
            ofMesh newMesh;
            newMesh.setMode(OF_PRIMITIVE_TRIANGLES);
            newMesh.addVertices(mesh.getVertices());
            newMesh.addNormals(mesh.getNormals());
            int countOriginalVertices = mesh.getNumVertices();
            
            // (start, end) -> new
            map<pair<int, int>, int> indexLookup;
            
            // set up vertices
            int countNewVertices = 0;
            for (int i = 0; i < mesh.getNumIndices() / 3; i++) {
                for (int j = 3 * i; j < 3 * i + 3; j++) {
                    int jNext = j + 1;
                    if (j % 3 == 2) jNext = j - 2;
                    map<pair<int, int>, int>::iterator findIndex = indexLookup.find(pair<int, int>(mesh.getIndices()[j], mesh.getIndices()[jNext]));
                    if (findIndex == indexLookup.end()) {
                        indexLookup.insert(pair<pair<int, int>, int>(pair<int, int>(mesh.getIndices()[j], mesh.getIndices()[jNext]), countOriginalVertices + countNewVertices));
                        indexLookup.insert(pair<pair<int, int>, int>(pair<int, int>(mesh.getIndices()[jNext], mesh.getIndices()[j]), countOriginalVertices + countNewVertices));
                        newMesh.addVertex(0.5 * (mesh.getVertices()[mesh.getIndices()[j]] + mesh.getVertices()[mesh.getIndices()[jNext]]));
                        newMesh.addNormal(0.5 * (mesh.getNormals()[mesh.getIndices()[j]] + mesh.getNormals()[mesh.getIndices()[jNext]]));
                        countNewVertices++;
                    }
                }
            }
            
            // set up indices
            unordered_set<int> neighborLookup[countNewVertices];
            for (int i = 0; i < mesh.getNumIndices() / 3; i++) {
                int i1 = mesh.getIndices()[3 * i + 0];
                int i2 = mesh.getIndices()[3 * i + 1];
                int i3 = mesh.getIndices()[3 * i + 2];
                int i12split = indexLookup.find(pair<int, int>(i1, i2))->second;
                int i23split = indexLookup.find(pair<int, int>(i2, i3))->second;
                int i31split = indexLookup.find(pair<int, int>(i3, i1))->second;
                
                newMesh.addIndex(i1);
                newMesh.addIndex(i12split);
                newMesh.addIndex(i31split);
                
                newMesh.addIndex(i12split);
                newMesh.addIndex(i2);
                newMesh.addIndex(i23split);
                
                newMesh.addIndex(i31split);
                newMesh.addIndex(i23split);
                newMesh.addIndex(i3);
                
                newMesh.addIndex(i12split);
                newMesh.addIndex(i31split);
                newMesh.addIndex(i23split);
                
            }
            
            return HalfEdgeMesh(newMesh);
            
        }
        
        return;
        
    }

    void HalfEdgeMesh::calculateNormals() {
        calculateFaceNormals();
        calculateVertexNormals();
    }

    void HalfEdgeMesh::calculateFaceNormals() {
        for (shared_ptr<Face> face : faces) {
            shared_ptr<Vertex> v1 = face->getHalfEdge()->getVertex();
            shared_ptr<Vertex> v2 = face->getHalfEdge()->getNextHalfEdge()->getVertex();
            shared_ptr<Vertex> v3 = face->getHalfEdge()->getNextHalfEdge()->getNextHalfEdge()->getVertex();
            glm::vec3 ba = v2->getPosition() - v1->getPosition();
            glm::vec3 ca = v3->getPosition() - v1->getPosition();
            face->setNormal(glm::normalize(glm::cross(ca, ba)));
            face->setCenter((v1->getPosition() + v2->getPosition() + v3->getPosition()) / 3.0f);
        }
    }

    void HalfEdgeMesh::calculateVertexNormals() {
        for (shared_ptr<Vertex> vertex : vertices) {
            glm::vec3 normal(0);
            for (shared_ptr<Face> face : vertex->getFaces()) normal += face->getNormal();
            vertex->setNormal(normal / vertex->getFaces().size());
        }
    }

}
