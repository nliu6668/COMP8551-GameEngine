#pragma once

struct BoxCollider {
	BoxCollider(float width = 0.0f, float height = 0.0f, 
	float x = 0.0f, float y = 0.0f, float z = 0.0f,
	float bbHeight, float bbWidth,
	bool isTrigger = false, bool render = false) :
	width(width), height(height), x(x), y(y), z(z), bbHeight(height),
	bbWidth(width), isTrigger(isTrigger), render(render){}
	
	float width, height;  //dimensions
	float x, y, z;        //position (relative to the entity)
	float bbHeight, bbWidth;  //bounding box for AABB
	bool isTrigger;  //specifies if collider is a trigger
	bool render;     //specifies whether to render the collider
};
