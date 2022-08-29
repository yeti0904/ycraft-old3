#include "ui.hh"
#include "collision.hh"

bool UI::Button::MouseIsOver(Vec2 cursor) {
	return (
		(cursor.x > position.x) &&
		(cursor.y > position.y) &&
		(cursor.x < position.x + size.x) &&
		(cursor.y < position.y + size.y)
	);
}

void UI::Button::Render(SDL_Renderer* renderer, TextComponents& text) {
	SDL_Rect shape = {position.x, position.y, size.x, size.y};

	// render box
	SDL_SetRenderDrawColor(
		renderer, filledColour.r, filledColour.g, filledColour.b, filledColour.a
	);
	SDL_RenderFillRect(renderer, &shape);
	SDL_SetRenderDrawColor(
		renderer, outlineColour.r, outlineColour.g, outlineColour.b, outlineColour.a
	);
	SDL_RenderDrawRect(renderer, &shape);

	// render text
	Vec2 labelSize = text.GetTextSize(label, 1.0);
	Vec2 textPos = {
		(size.x / 2) - (labelSize.x / 2),
		(size.y / 2) - (labelSize.y / 2)
	};

	text.RenderText(
		renderer, label, {position.x + textPos.x, position.y + textPos.y},
		1.0, true
	);
}

bool UI::Checkbox::MouseIsOver(Vec2 cursor) {
	UI::Button buttonCast;
	buttonCast.position = position;
	buttonCast.size     = size;

	return buttonCast.MouseIsOver(cursor);
}

void UI::Checkbox::Render(SDL_Renderer* renderer) {
	SDL_Rect outline;
	outline.x = position.x;
	outline.y = position.y;
	outline.w = size.x;
	outline.h = size.y;

	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderDrawRect(renderer, &outline);

	if (activated) {
		SDL_Rect indicator;
		indicator.x = outline.x + 2;
		indicator.y = outline.y + 2;
		indicator.w = outline.w - 4;
		indicator.h = outline.h - 4;

		SDL_RenderFillRect(renderer, &indicator);
	}
}
