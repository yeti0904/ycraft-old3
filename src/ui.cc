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
