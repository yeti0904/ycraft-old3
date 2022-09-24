#ifndef YCRAFT_COMMANDS_HH
#define YCRAFT_COMMANDS_HH

#include "_components.hh"
#include "chat.hh"

class App;

void RegisterCommands(CommandsSystem& commands);

namespace Commands {
	void Help(std::vector <std::string>& args, App& app);
	void Tp(std::vector <std::string>& args, App& app);
}

#endif