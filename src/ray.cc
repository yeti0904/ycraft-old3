#include "ray.hh"

float Ray::DegreesToRadians(float degrees) {
	return degrees * (M_PI / 180.0f);
}

Ray::Ray Ray::MoveInDirection(Ray ray, float distance) {
	Ray ret = ray;
	ret.pos = {
		cos(DegreesToRadians(ray.dir)) * distance,
		sin(DegreesToRadians(ray.dir)) * distance
	};
	return ret;
}