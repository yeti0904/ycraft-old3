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
	if (label.empty()) {
		return;
	}
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

ssize_t UI::ButtonArray::MouseIsOver(Vec2 cursor) {
	for (size_t i = 0; i < options.size(); ++i) {
		UI::Button buttonCast;
		if (vertical) {
			buttonCast.position = {
				position.x,
				static_cast <int32_t>(position.y + ((size.y / options.size()) * i))
			};
			buttonCast.size          = {
				size.x, static_cast <int32_t> (size.y / options.size())
			};
		}
		else {
			buttonCast.position = {
				static_cast <int32_t>(position.x + ((size.x / options.size()) * i)),
				position.y
			};
			buttonCast.size     = {
				static_cast <int32_t>(size.x / options.size()), size.y
			};
		}

		if (buttonCast.MouseIsOver(cursor)) {
			return i;
		}
	}
	return -1;
}

void UI::ButtonArray::Render(SDL_Renderer* renderer, TextComponents& text) {
	for (size_t i = 0; i < options.size(); ++i) {
		UI::Button buttonCast;
		buttonCast.label    = options[i];
		if (vertical) {
			buttonCast.position = {
				position.x,
				static_cast <int32_t>(position.y + ((size.y / options.size()) * i))
			};
			buttonCast.size          = {
				size.x, static_cast <int32_t> (size.y / options.size())
			};
		}
		else {
			buttonCast.position = {
				static_cast <int32_t>(position.x + ((size.x / options.size()) * i)),
				position.y
			};
			buttonCast.size     = {
				static_cast <int32_t>(size.x / options.size()), size.y
			};
		}

		if ((i == (size_t) selected) || (i == (size_t) set)) {
			continue;
		}
		else {
			buttonCast.outlineColour = outline;
			buttonCast.filledColour  = filled;
		}

		buttonCast.Render(renderer, text);
	}
	
	UI::Button buttonCast;
	if (vertical) {
		buttonCast.position = {
			position.x,
			static_cast <int32_t>(position.y + ((size.y / options.size()) * set))
		};
		buttonCast.size          = {
			size.x, static_cast <int32_t> (size.y / options.size())
		};
	}
	else {
		buttonCast.position = {
			static_cast <int32_t>(position.x + ((size.x / options.size()) * set)),
			position.y
		};
		buttonCast.size          = {
			static_cast <int32_t> (size.x / options.size()), size.y
		};
	}
	buttonCast.outlineColour = selectedOutline;
	buttonCast.filledColour  = selectedFilled;
	if (set >= 0) {
		buttonCast.label    = options[set];
		buttonCast.Render(renderer, text);
	}
	
	if (selected < 0) {
		return;
	}

	buttonCast.label    = options[selected];
	if (vertical) {
		buttonCast.position = {
			position.x,
			static_cast <int32_t>(position.y + ((size.y / options.size()) * selected))
		};
	}
	else {
		buttonCast.position = {
			static_cast <int32_t>(position.x + ((size.x / options.size()) * selected)),
			position.y
		};
	}
	buttonCast.Render(renderer, text);
}

void UI::ButtonArray::UpdateSelected(Vec2 cursor) {
	selected = MouseIsOver(cursor);
}

bool UI::Textbox::MouseIsOver(Vec2 cursor) {
	UI::Button buttonCast;
	buttonCast.position = position;
	buttonCast.size     = size;

	return buttonCast.MouseIsOver(cursor);
}

void UI::Textbox::Render(SDL_Renderer* renderer, TextComponents& text) {
	SDL_Rect box;
	box.x = position.x;
	box.y = position.y;
	box.w = size.x;
	box.h = size.y;

	SDL_SetRenderDrawColor(renderer, filled.r, filled.g, filled.b, filled.a);
	SDL_RenderFillRect(renderer, &box);
	SDL_SetRenderDrawColor(renderer, outline.r, outline.g, outline.b, outline.a);
	SDL_RenderDrawRect(renderer, &box);

	// render text
	text.RenderText(renderer, input, {position.x + 1, position.y + 5}, 1.0, false);

	// render cursor
	Vec2 cursorOffset = text.GetTextSize(input.substr(0, cursorPosition), 1.0);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(
		renderer,
		position.x + cursorOffset.x + 1, position.y + 4,
		position.x + cursorOffset.x + 1, position.y + size.y - 5
	);
}

void UI::Textbox::HandleEvent(SDL_Event& event) {
	if (!focused) {
		return;
	}
	switch (event.type) {
		case SDL_TEXTINPUT: {
			input += event.text.text;
			cursorPosition += std::string(event.text.text).size();
			if (std::string(event.text.text).back() == '\n') {
				input.erase(input.find('\n'), 1);
			}
			break;
		}
		case SDL_TEXTEDITING: {
			break;
		}
	}
}

void UI::Textbox::Reset() {
	Textbox();
}

void UI::Textbox::Backspace() {
	if (input.empty()) {
		return;
	}
	input.pop_back();
	-- cursorPosition;
}
