#pragma once
#include "BaseScene.h"
#include "Texture.h"

class CubeScene : public Scene
{
private:
    Texture2D m_WallTexture;
    Shader m_tessVertexShader, m_tessFragShader, m_vertexShader, m_fragmentShader, m_tessControlShader, m_tessEvalShader;
    ShaderProgram m_Program, m_tessProgram;
    Matrix4 projection, mv, rotation;
    Vector3 position;
    bool wireframe;
protected:
    void LoadShaders() override;
    void CreateShaderPrograms() override;
    void VerticeInformationSlicer() override;
public:
    CubeScene();
    ~CubeScene() = default;
    void SetupScene() override;
    void UpdateScene() override;
protected:
    
};
