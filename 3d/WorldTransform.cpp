#include "WorldTransform.h"
#include "MyMathUtility.h"

void WorldTransform::PlayerUpdate(WorldTransform worldTransform[],size_t pointNum) {
	worldTransform[pointNum].matWorld_ =
	  MyMathUtility::MySynMatrix4WorldTransform(worldTransform[pointNum]);
	if (worldTransform[pointNum].parent_ == &worldTransform[PartId::kRoot]) {
		worldTransform[pointNum].matWorld_ *= worldTransform[PartId::kRoot].matWorld_;
	}
	if (worldTransform[pointNum].parent_ == &worldTransform[PartId::kSpine]) {
		worldTransform[pointNum].matWorld_ *= worldTransform[PartId::kSpine].matWorld_;
	}
	if (worldTransform[pointNum].parent_ == &worldTransform[PartId::kChest]) {
		worldTransform[pointNum].matWorld_ *= worldTransform[PartId::kChest].matWorld_;
	}
	if (worldTransform[pointNum].parent_ == &worldTransform[PartId::kHip]) {
		worldTransform[pointNum].matWorld_ *= worldTransform[PartId::kHip].matWorld_;
	}
	worldTransform[pointNum].TransferMatrix();
}
