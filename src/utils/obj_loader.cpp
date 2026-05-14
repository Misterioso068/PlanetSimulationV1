#include "utils/obj_loader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

ObjData ObjLoader::load(const std::string& filePath) {
    ObjData result;

    std::vector<GLfloat> positions;   // raw positions from 'v' lines
    std::vector<GLfloat> uvs;         // raw uvs from 'vt' lines
    std::vector<GLfloat> normals;     // raw normals from 'vn' lines

    // map of "posIdx/uvIdx/normIdx" -> final vertex index
    // used to deduplicate vertices
    std::unordered_map<std::string, GLuint> vertexMap;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Failed to open obj file: " << filePath << "\n";
        return result;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;
        ss >> token;

        if (token == "mtllib") {
            ss >> result.mtlFile;

        } else if (token == "usemtl") {
            ss >> result.materialName;

        } else if (token == "v") {
            // vertex position
            GLfloat x, y, z;
            ss >> x >> y >> z;
            positions.push_back(x);
            positions.push_back(y);
            positions.push_back(z);

        } else if (token == "vt") {
            // texture coordinate
            GLfloat u, v;
            ss >> u >> v;
            uvs.push_back(u);
            uvs.push_back(v);

        } else if (token == "vn") {
            // normal
            GLfloat x, y, z;
            ss >> x >> y >> z;
            normals.push_back(x);
            normals.push_back(y);
            normals.push_back(z);

        } else if (token == "f") {
            // face — parse each vertex token e.g "1/2/3"
            std::vector<std::string> faceTokens;
            std::string faceToken;
            while (ss >> faceToken) {
                faceTokens.push_back(faceToken);
            }

            // triangulate — fan triangulation handles quads and ngons
            // e.g 4 vertices: (0,1,2) and (0,2,3)
            for (int i = 1; i < (int)faceTokens.size() - 1; i++) {
                std::string corners[3] = { faceTokens[0], faceTokens[i], faceTokens[i + 1] };

                for (const auto& corner : corners) {
                    // check if we already have this vertex combination
                    if (vertexMap.count(corner)) {
                        result.indices.push_back(vertexMap[corner]);
                        continue;
                    }

                    // parse "posIdx/uvIdx/normIdx" — each part is optional
                    int posIdx = 0, uvIdx = 0, normIdx = 0;
                    std::istringstream css(corner);
                    std::string part;
                    int partNum = 0;
                    while (std::getline(css, part, '/')) {
                        if (!part.empty()) {
                            int idx = std::stoi(part) - 1; // obj is 1-based
                            if (partNum == 0) posIdx = idx;
                            else if (partNum == 1) uvIdx = idx;
                            else if (partNum == 2) normIdx = idx;
                        }
                        partNum++;
                    }

                    // build final vertex: x,y,z, u,v, nx,ny,nz
                    GLuint newIndex = result.vertices.size() / 8;

                    result.vertices.push_back(positions[posIdx * 3]);
                    result.vertices.push_back(positions[posIdx * 3 + 1]);
                    result.vertices.push_back(positions[posIdx * 3 + 2]);

                    if (!uvs.empty()) {
                        result.vertices.push_back(uvs[uvIdx * 2]);
                        result.vertices.push_back(uvs[uvIdx * 2 + 1]);
                    } else {
                        result.vertices.push_back(0.0f);
                        result.vertices.push_back(0.0f);
                    }

                    if (!normals.empty()) {
                        result.vertices.push_back(normals[normIdx * 3]);
                        result.vertices.push_back(normals[normIdx * 3 + 1]);
                        result.vertices.push_back(normals[normIdx * 3 + 2]);
                    } else {
                        result.vertices.push_back(0.0f);
                        result.vertices.push_back(0.0f);
                        result.vertices.push_back(1.0f);
                    }

                    vertexMap[corner] = newIndex;
                    result.indices.push_back(newIndex);
                }
            }
        }
    }

    return result;
}