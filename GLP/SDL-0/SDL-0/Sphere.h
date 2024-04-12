#pragma once
#include "Object3D.h"
#include "Vector3.h"

class Sphere : public Object3D
{
protected:
    float m_radius;
public:
    Sphere(Vector3 position = Vector3(0,0,0), float radius = 0.5f);
    ~Sphere()=default;
    void Generate() override;
    void Draw() override;
};
