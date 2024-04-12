#pragma once
#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"

class SphereScene : public Scene
{
private:
    Texture2D m_WallTexture;
    Shader m_tessVertexShader, m_tessFragShader, m_vertexShader, m_fragmentShader, m_tessControlShader, m_tessEvalShader;
    ShaderProgram m_Program, m_tessProgram;
    Matrix4 projection, mv, rotation;
    Vector3 position;
    bool wireframe;

    std::vector<int> m_indicies, m_lineIndices;
protected:
    void LoadShaders() override;
    void CreateShaderPrograms() override;
    void VerticeInformationSlicer() override;
public:
    SphereScene();
    ~SphereScene() = default;
    void SetupScene() override;
    void UpdateScene() override;
public:
    
};
