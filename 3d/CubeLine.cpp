#include "CubeLine.h"

void CubeLine::Initialize() {
	Vector3 cubeVertex_[8] = 
    {
	  {0.0f, 5.0f, 0.0f},
      {0.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 0.0f},
      {5.0f, 5.0f, 0.0f},
	  {0.0f, 5.0f, 5.0f},
      {0.0f, 0.0f, 5.0f},
      {5.0f, 0.0f, 5.0f},
      {5.0f, 5.0f, 5.0f}
    };

    int edgeList_[12][2] = {
	  {0, 1},
      {1, 2},
      {2, 3},
      {3, 0},
      {4, 5},
      {5, 6},
	  {6, 7},
      {7, 4},
      {0, 4},
      {1, 5},
      {2, 6},
      {3, 7}
    };

    Vector4 color = {0xFF, 0xFF, 0xFF, 0xFF};
}