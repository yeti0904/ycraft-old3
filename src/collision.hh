#pragma once
#include "_components.hh"
#include "types.hh"
#include "level.hh"

// https://www.youtube.com/watch?v=8JJ-4JgR7Dg
// very cool video

namespace Collision {
	bool PointVsRect(FVec2 point, FRect rect);
	bool RectVsRect(FRect rect1, FRect rect2);
	bool RayVsRect(
		FVec2& rayOrigin, FVec2& rayDirection, FRect& targetFVec2, FVec2& contactPoint,
		FVec2& contactNormal, float& t_hitNear
	);
	bool DynamicRectVsRect(
		const FRect& in, const FRect& target, FVec2 contactPoint, FVec2 contactNormal,
		float& time, const FVec2& vel
	);
}
