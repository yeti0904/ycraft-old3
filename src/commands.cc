#include "commands.hh"
#include "app.hh"
#include "types.hh"
#include "util.hh"

void Commands::Help(std::vector <std::string>& args, App& app) {
	if (args.empty()) {
		app.game.AddToChat("Available commands");
		for (auto& cmd : app.game.commands.commands) {
			app.game.AddToChat("  " + cmd.name);
		}
		return;
	}
	if (!app.game.commands.CommandExists(args[0])) {
		app.game.AddToChat("No such command: " + args[0]);
		return;
	}

	for (auto& helpLine : app.game.commands.GetCommand(args[0]).help) {
		app.game.AddToChat(helpLine);
	}
}

void Commands::Tp(std::vector <std::string>& args, App& app) {
	if (args.size() < 2) {
		app.game.AddToChat("TP: Not enough arguments");
		return;
	}
	for (size_t i = 0; i < 2; ++i) {
		if (!Util::IsNumber(args[i])) {
			app.game.AddToChat("TP: arguments must be integers");
			return;
		}
	}

	app.game.player.position = {
		(float) stod(args[0]),
		(float) stod(args[1])
	};
}

void RegisterCommands(CommandsSystem& commands) {
	commands.AddCommand(
		"help", Commands::Help, {
			"/help {command}",
			"  Returns info on how to use {command}",
			"  If {command} is not given, then show",
			"  a list of commands"
		}
	);
	commands.AddCommand(
		"tp", Commands::Tp, {
			"/tp [x] [y]",
			"  Moves the player to the coordinates [x] [y]"
		}
	);
}