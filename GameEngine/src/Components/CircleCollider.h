#pragma once

struct CircleCollider {
	CircleCollider(float radius = 0.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f,
	float bbX1 = 0.0f, float bbY1 = 0.0f, float bbX2 = 0.0f, float bbY2 = 0.0f,
	float bbX3 = 0.0f, float bbY3 = 0.0f, float bbX4 = 0.0f, float bbY4 = 0.0f,
	bool isTrigger = false, bool render = false) :
	radius(radius), x(x), y(y), z(z), bbX1(bbX1), bbY1(bbY1),
	bbX2(bbX2), bbY2(bbY2), bbX3(bbX3), bbY3(bbY3), bbX4(bbX4), bbY4(bbY4),
	isTrigger(isTrigger), render(render){}
	
	float radius;     //dimensions
	float x, y, z;    //position (relative to entity)
	float bbX1, bbY1, bbX2, bbY2, bbX3, bbY3, bbX4, bbY4;  //bounding box for AABB
	bool isTrigger;   //specifies if collider is a trigger
	bool render;      //specifies whether to render the collider
}