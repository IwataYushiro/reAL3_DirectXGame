#include "WorldTransform.h"
#include "MyMathUtility.h"

void WorldTransform::Update(WorldTransform worldTransform) {
	worldTransform.matWorld_ =
	  MyMathUtility::MySynMatrix4WorldTransform(worldTransform);
	
	worldTransform.TransferMatrix();
}
