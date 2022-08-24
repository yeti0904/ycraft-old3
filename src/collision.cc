#include "collision.hh"

bool Collision::PointVsRect(FVec2 point, FRect rect) {
	return (
		(point.x >= rect.x) && (point.y >= rect.y) &&
		(point.x < rect.x + rect.w) && (point.y < rect.y + rect.h)
	);
}

bool Collision::RectVsRect(FRect rect1, FRect rect2) {
	return (
		(rect1.x < rect2.x + rect2.w) &&
		(rect1.x + rect1.w > rect2.x) &&
		(rect1.y < rect2.y + rect2.h) &&
		(rect1.y + rect1.h > rect2.y)
	);
}

bool Collision::RayVsRect(
	FVec2& rayOrigin, FVec2& rayDirection, FRect& target, FVec2& contactPoint,
	FVec2& contactNormal, float& t_hitNear
) {
	FVec2 t_near = {
		(target.x - rayOrigin.x) / rayDirection.x,
		(target.y - rayOrigin.y) / rayDirection.y
	};
	FVec2 t_far = {
		(target.x + target.w - rayOrigin.x) / rayDirection.x,
		(target.y + target.h - rayOrigin.y) / rayDirection.y
	};

	if (t_near.x > t_far.x) {
		std::swap(t_near.x, t_far.x);
	}
	if (t_near.y > t_far.y) {
		std::swap(t_near.y, t_far.y);
	}

	if ((t_near.x > t_far.y) || (t_near.y > t_far.x)) {
		return false;
	}

	t_hitNear = std::max(t_near.x, t_near.y);
	float t_hitFar  = std::max(t_far.x, t_far.y);

	if (t_hitFar < 0) {
		return false;
	}

	contactPoint.x = rayOrigin.x + t_hitNear * rayDirection.x;
	contactPoint.y = rayOrigin.y + t_hitNear * rayDirection.y;

	if (t_near.x > t_near.y) {
		if (rayDirection.x < 0) {
			contactNormal = {1, 0};
		}
		else {
			contactNormal = {-1, 0};
		}
	}
	else if (t_near.x < t_near.y) {
		if (rayDirection.y < 0) {
			contactNormal = {0, 1};
		}
		else {
			contactNormal = {0, -1};
		}
	}

	return true;
}
/*
bool Collision::DynamicRectVsRect(
	const FRect& in, const FRect& target, FVec2 contactPoint, FVec2 contactNormal,
	float& time, const FVec2& vel
) {
	if ((vel.x == 0) && (vel.y == 0)) {
		return false;
	}

	FRect expandedTarget;
	expandedTarget.x = target.x - in.w / 2;
	expandedTarget.y = target.y - in.h / 2;
	expandedTarget.w = target.w + in.w;
	expandedTarget.h = target.h + in.h;
}
*/
