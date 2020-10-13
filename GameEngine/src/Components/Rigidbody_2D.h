#pragma once

struct Rigidbody_2D {
    Rigidbody_2D(float gravity = 1.0f, float mass = 0.0f, 
		float linDrag = -1.0f, float angDrag = 0.0f, 
		float cmX = 0.0f, float cmY = 0.0f, float cmZ = 0.0f,
		float velocityX = 0.0f, float velocityY = 0.0f,
		float angVelocityX = 0.0f, float angVelocityY = 0.0f,
		float accelerationX = 0.0f, float accelerationY = 0.0f,
		float angAcceleration = 0.0f) : 
		gravity(gravity), mass(mass), linDrag(linDrag), 
		angDrag(angDrag), cmX(cmX), cmY(cmY), cmZ(cmZ), velocityX(velocityX), 
		velocityY(velocityY), angVelocityX(angVelocityX), angVelocityY(angVelocityY),
		accelerationX(accelerationX), accelerationY(accelerationY),
		angAcceleration(angAcceleration){}

    float gravity;        //value of gravity on the rigidbody
	float linDrag;        //linear drag co-efficient.  if unsure of value, use the mass
	float angDrag;        //angular drag co-efficient
	float mass;           //mass
	float cmX, cmY, cmZ;  //position of the center of mass
	float velocityX, velocityY, angVelocityX, angVelocityY; //linear and angular velocity
	float accelerationX, accelerationY, angAcceleration;  //linear and angular acceleration
};