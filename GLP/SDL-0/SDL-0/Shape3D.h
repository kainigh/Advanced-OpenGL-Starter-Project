#pragma once
#include <vector>
#include "Vector2.h"
#include "Vector3.h"
#include "Window.h"

using namespace std;

class Shape3D {
protected:

    public:
	static inline void CreateCube(vector<float>& vertices, Vector2 center, Vector3 dimensions) {
		
	}



	static inline void CreateSphere(vector<float>& vertices, vector<int>& indices, vector<int>& lineIndices, Vector3 center, float radius, Vector2 subdivisions)
	{
		float x, y, z, xy;
		float pi = Maths::pi;
		//Face dimensions
		float horizontalStep = 2 * pi / subdivisions.x;	//Horizontal 
		float verticalStep =  pi / subdivisions.y;		//Vertical
		float horizontalAngle, verticalAngle;

		for(int line = 0; line < subdivisions.y; ++line)
		{
			verticalAngle = pi/2 - line * verticalStep;
			xy = radius * cosf(verticalAngle);
			z = radius * sinf(verticalAngle);

			for(int column = 0; column < subdivisions.x; ++column)
			{
				horizontalAngle = column * horizontalStep;
				x = xy * cosf(horizontalAngle);
				y = xy * sinf(horizontalAngle);
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
		}
		int k1, k2;
		for(int i = 0; i < subdivisions.y; ++i)
		{
			k1 = i * (subdivisions.x + 1);															
			k2 = k1 + (subdivisions.x + 1);

			for(int j = 0; j < subdivisions.x; ++j, ++k1, ++k2)
			{
				  if(i != 0)
				  {
					  indices.push_back(k1);
					  indices.push_back(k2);
					  indices.push_back(k2+1);
				  }
				if(i != (subdivisions.y-1))
				{
					  indices.push_back(k1+1);
					  indices.push_back(k2);
					  indices.push_back(k2+1);
				}
				lineIndices.push_back(k1);
				lineIndices.push_back(k2);
				if(i!=0)
				{
					lineIndices.push_back(k1);
					lineIndices.push_back(k1 + 1);
				}
			}
		}
	}

};