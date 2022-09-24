#include "chat.hh"
#include "app.hh"
#include "constants.hh"
#include "util.hh"

App* app;

bool Chat::IsCommand(std::string input) {
	return (input.length() > 1) && (input[0] == GAME_COMMAND_PREFIX);
}

std::vector <std::string> Chat::ParseCommand(std::string input) {
	std::string               in = input.substr(1);
	std::vector <std::string> ret;
	std::string               reading;

	for (auto& ch : in) {
		if (ch == ' ') {
			ret.push_back(reading);
			reading = "";
		}
		else {
			reading += ch;
		}
	}
	if (reading != "") {
		ret.push_back(reading);
	}

	return ret;
}

void InitCommands(App* p_app) {
	app = p_app;
}

CommandsSystem::CommandsSystem() {
	
}

void CommandsSystem::AddCommand(
	std::string name, CommandCallback callback, std::vector <std::string> help
) {
	commands.push_back({name, callback, help});
	Util::Log("Registered command %s", name.c_str());
}

void CommandsSystem::RunCommand(std::string name, std::vector <std::string> arguments) {
	for (auto& command : commands) {
		if (command.name == name) {
			command.function(arguments, *app);
			return;
		}
	}
}

bool CommandsSystem::CommandExists(std::string name) {
	for (auto& cmd : commands) {
		if (cmd.name == name) {
			return true;
		}
	}
	return false;
}

Command CommandsSystem::GetCommand(std::string name) {
	for (auto& cmd : commands) {
		if (cmd.name == name) {
			return cmd;
		}
	}

	Util::Error("Failed to get command %s", name.c_str());
	return {"", nullptr, {}};
}