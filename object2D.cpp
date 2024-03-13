#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0.7f), color),
        VertexFormat(corner + glm::vec3(width, length, 0.7f), color),
        VertexFormat(corner + glm::vec3(0, length, 0.7f), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateStar(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, float size)
{
    std::vector<VertexFormat> vertices;

    vertices.emplace_back(glm::vec3(0, 0, 4), color);
    int x, y;
    for (int i = 0; i < 10; i++) {

        if (i % 2 == 1) {
            x = size / 2 * sin(glm::radians((float)i * 36));
			y = size / 2 * cos(glm::radians((float)i * 36));
        }
        else {
            x = size * sin(glm::radians((float)i * 36));
            y = size * cos(glm::radians((float)i * 36));
        }
        vertices.emplace_back(glm::vec3(x, y, 4), color);
    }


    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1 };

    star->SetDrawMode(GL_TRIANGLE_FAN);

    star->InitFromData(vertices, indices);
    return star;
}

Mesh* object2D::CreateDiamond(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length/2, length/2, 0.5f), color),
        VertexFormat(corner + glm::vec3(-length/2, length / 2, 0.5f), color),
        VertexFormat(corner + glm::vec3(0, length, 0.5f), color),
        VertexFormat(corner + glm::vec3(0, length / 2 - width/2, 0.5f), color),
        VertexFormat(corner + glm::vec3(0, length / 2 + width/2, 0.5f), color),
        VertexFormat(corner + glm::vec3(3*length/4, length / 2 - width / 2, 0.5f), color),
        VertexFormat(corner + glm::vec3(3*length/4, length / 2 + width / 2, 0.5f), color),
    };

    std::vector<unsigned int> indices = { 0, 1, 2,
                                          1, 3, 2,
                                          4, 6, 7,
                                          4, 5, 7,
    };

    Mesh* diamond = new Mesh(name);
    diamond->SetDrawMode(GL_TRIANGLES);

    diamond->InitFromData(vertices, indices);
    return diamond;
}

Mesh* object2D::CreateHex(
    const std::string& name,
    glm::vec3 color,
    bool fill,
    float size)
{
    std::vector<VertexFormat> vertices;
    vertices.emplace_back(glm::vec3(0, 0, 0.6f), color);
    int x, y;
    for (int i = 0; i < 6; i++) {

        x = size * sin(glm::radians((float)i * 60));
        y = size * cos(glm::radians((float)i * 60));
        vertices.emplace_back(glm::vec3(x, y, 0.6f), color);
    }


    Mesh* hex = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6, 1 };

    hex->SetDrawMode(GL_TRIANGLE_FAN);

    hex->InitFromData(vertices, indices);
    return hex;
}

Mesh* object2D::CreateSmallHex(
    const std::string& name,
    glm::vec3 color,
    bool fill,
    float size)
{
    std::vector<VertexFormat> vertices;
    vertices.emplace_back(glm::vec3(0, 0, 2.f), color);
    int x, y;
    for (int i = 0; i < 6; i++) {

        x = size * sin(glm::radians((float)i * 60));
        y = size * cos(glm::radians((float)i * 60));
        vertices.emplace_back(glm::vec3(x, y, 2.f), color);
    }


    Mesh* hex = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6, 1};

    hex->SetDrawMode(GL_TRIANGLE_FAN);

    hex->InitFromData(vertices, indices);
    return hex;
}

