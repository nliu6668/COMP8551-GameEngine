#pragma once

struct CapsuleCollider {
	CapsuleCollider(float radius = 0.0f, float a = 0.0f,
	float x = 0.0f, float y = 0.0f, float z = 0.0f,
	bool isTrigger = false, bool render = false) :
	radius(radius), x(x), y(y), z(z), bbHeight(a + radius * 2),
	bbWidth(radius * 2), isTrigger(isTrigger), render(render){}
	
	float radius, a;     //dimensions  (a represents the length between the ends of the capsule)
	float x, y, z;    //position (relative to entity)
	float bbHeight, bbWidth;  //bounding box for AABB
	bool isTrigger;   //specifies if collider is a trigger
	bool render;      //specifies whether to render the collider
};