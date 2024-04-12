#include "SphereScene.h"

#include "Shape3D.h"

void SphereScene::LoadShaders()
{
    m_vertexShader.LoadFrom("cube.vert", VERTEX);
    m_fragmentShader.LoadFrom("cube.frag", FRAGMENT);
    m_tessVertexShader.LoadFrom("cubeTess.vert", VERTEX);
    m_tessFragShader.LoadFrom("cubeTess.frag", FRAGMENT);
    m_tessControlShader.LoadFrom("cube.tesc", TESSELLATION_CONTROL);
    m_tessEvalShader.LoadFrom("cube.tese", TESSELLATION_EVALUATION);
}

void SphereScene::CreateShaderPrograms()
{
    m_Program.Compose({&m_vertexShader, &m_fragmentShader});
    m_tessProgram.Compose({&m_tessVertexShader, &m_tessFragShader, &m_tessControlShader, &m_tessEvalShader});
}

void SphereScene::VerticeInformationSlicer()
{
    float* verticeArray = new float[m_vertices.size()]();
    std::copy(m_vertices.begin(), m_vertices.end(), verticeArray);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), verticeArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //glPatchParameteri(GL_PATCHES, 3);
    delete [] verticeArray;
}

SphereScene::SphereScene()
{
    Shape3D::CreateSphere(m_vertices, m_indicies, m_lineIndices, Vector3(0,0,0), 0.5f, Vector2(15,15));
}

void SphereScene::SetupScene()
{
    LoadShaders();
    CreateShaderPrograms();
    projection = Matrix4::createPerspectiveFOV(70.0f, Window::Dimension.x, Window::Dimension.y, 0.1f, 1000.0f);
    position = Vector3(0, 0, -4.0f);
    mv = Matrix4::createTranslation(position);

    //Create one ID to be given at object generation and store it in m_vao via reference
    glGenVertexArrays(1, &m_vao);
    //Binding the VAO 
    //   /!\ If you have multiple VAOs, you should bind the correct VAO after each change
    glBindVertexArray(m_vao);

    //Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo);
    VerticeInformationSlicer();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //Creating and loading the simple texture
    m_WallTexture = Texture2D();
    m_WallTexture.load("Textures/wall.png");
    m_WallTexture.generate();
    m_WallTexture.use();
    glGenerateTextureMipmap(m_WallTexture.id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

}

void SphereScene::UpdateScene()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	
    float timeValue = (float)SDL_GetTicks() / 1000;
    float sinusoidValue = (sin(timeValue))/2.0f;
	
    position.y = sinusoidValue;
    m_Program.Use();
    mv = Matrix4::createTranslation(position -Vector3(0.5f,0,0));
    Matrix4 rotationX = Matrix4::createRotationX(0.01f );
    Matrix4 rotationY = Matrix4::createRotationY(0.005f );
    Matrix4 rotationZ = Matrix4::createRotationY(0.01f );
    rotation *= rotationX;
    rotation *= rotationY;
    rotation *= rotationZ;
    mv = mv * rotation;
	

    m_Program.setMatrix4("mv_matrix", mv);
    m_Program.setMatrix4("projection", projection);
    std::cout<<m_vertices.size()<< std::endl;
    //glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    glDrawElements(GL_TRIANGLES, m_indicies.size(), GL_UNSIGNED_INT, (void*)0);
    // m_tessProgram.Use();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //
    // mv = Matrix4::createTranslation(position + Vector3(0.5f,0,0));
    // mv = mv * rotation;
    // //m_Program.setMatrix4("mv_matrix", mv);
    //
    // m_tessProgram.setMatrix4("mv_matrix", mv);
    // m_tessProgram.setMatrix4("projection", projection);
    // m_tessProgram.setFloat("ratio", (sinusoidValue + 1) * 10);
    // glDrawArrays(GL_PATCHES, 0, m_vertices.size());
}
