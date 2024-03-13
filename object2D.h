#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill = false);
    Mesh* CreateStar(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, float size = 50);
    Mesh* CreateDiamond(const std::string& name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill = false);
    Mesh* CreateHex(const std::string& name, glm::vec3 color, bool fill = false, float size = 40);
    Mesh* CreateSmallHex(const std::string& name, glm::vec3 color, bool fill = false, float size = 40);

}
