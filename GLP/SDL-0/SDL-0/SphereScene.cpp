#include "SphereScene.h"

#include "Shape3D.h"

void SphereScene::LoadShaders()
{
    m_vertexShader.LoadFrom("sphere.vert", VERTEX);
    m_fragmentShader.LoadFrom("sphere.frag", FRAGMENT);
}

void SphereScene::CreateShaderPrograms()
{
    m_Program.Compose({&m_vertexShader, &m_fragmentShader});
}

void SphereScene::VerticeInformationSlicer()
{
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicies.size() * sizeof(float), m_indicies.data(), GL_STATIC_DRAW);
    glBindVertexArray(m_vao);
}

SphereScene::SphereScene():Scene()
{
    glGenBuffers(1, &m_vboV);
    glGenBuffers(1, &m_vboI);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboV);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboI);

    Shape3D::CreateSphere(m_vertices, m_indicies, m_lineIndices, Vector3(0.0, 0.0, 0.0), 1.0f, 10,10);
}

void SphereScene::SetupScene()
{
    LoadShaders();
    CreateShaderPrograms();
    //Indexes array buffer
    //Create one ID to be given at object generation and store it in m_vao via reference
    glGenVertexArrays(1, &m_vao);
    //Binding the VAO 
    //   /!\ If you have multiple VAOs, you should bind the correct VAO after each change
    glBindVertexArray(m_vao);
    

    cout<<"vbo : "<<m_vboV<<endl;

    cout<<"i : "<<m_vboI<<endl;

    VerticeInformationSlicer();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    m_projection = Matrix4::createPerspectiveFOV(70.0f, Window::Dimension.x, Window::Dimension.y, 0.1f, 1000.0f);
    m_position = Vector3(0, 0, -4.0f);
    m_mv = Matrix4::createTranslation(m_position);
    m_rotation = Matrix4::createRotationX(1.5);

}

void SphereScene::UpdateScene()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	
    float timeValue = (float)SDL_GetTicks() / 1000;
    float sinusoidValue = (sin(timeValue))/2.0f;
	
    //m_position.y = sinusoidValue;
    m_Program.Use();
    m_mv = Matrix4::createTranslation(m_position);
    Matrix4 rotationX = Matrix4::createRotationX(0.005f *sinusoidValue);
    Matrix4 rotationY = Matrix4::createRotationY(0.001f);
    Matrix4 rotationZ = Matrix4::createRotationY(0.001f);
    m_rotation *= rotationX;
    m_rotation *= rotationY;
    m_rotation *= rotationZ;
    m_mv = m_mv * m_rotation;
	

    m_Program.setMatrix4("mv_matrix", m_mv);
    m_Program.setMatrix4("projection", m_projection);
    
    glVertexPointer(3, GL_FLOAT, 0, m_vertices.data());

    glDrawElements(GL_TRIANGLES, m_indicies.size(), GL_UNSIGNED_INT, m_indicies.data());
    //glDrawArrays(GL_TRIANGLES, 3, 300);
}
