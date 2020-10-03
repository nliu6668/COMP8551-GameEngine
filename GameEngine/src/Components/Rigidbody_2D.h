#pragma once

struct Rigidbody_2D {
    Rigidbody_2D(float gravity = 1.0f, float linDrag = 0.0f, 
		float angDrag = 0.0f, float mass = 0.0f, 
		float cmX = 0.0f, float cmY = 0.0f, float cmZ = 0.0f,
		float velocity = 0.0f, float angVelocity = 0.0f,
		float acceleration = 0.0f, float angAcceleration = 0.0f) : 
		gravity(gravity), linDrag(linDrag), angDrag(angDrag), 
		mass(mass), cmX(cmX), cmY(cmY), cmZ(cmZ), velocity(velocity), 
		angVelocity(angVelocity), acceleration(acceleration),
		angAcceleration(angAcceleration){}

    float gravity;        //value of gravity on the rigidbody
	float linDrag;        //linear drag co-efficient
	float angDrag;        //angular drag co-efficient
	float mass;           //mass
	float cmX, cmY, cmZ;  //position of the center of mass
	float velocity, angVelocity; //linear and angular velocity
	float acceleration, angAcceleration;  //linear and angular acceleration
};