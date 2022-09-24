#ifndef YCRAFT_CHAT_HH
#define YCRAFT_CHAT_HH

#include "_components.hh"

class App;

struct ChatItem {
	uint32_t    time;
	std::string content;
};

namespace Chat {
	bool                      IsCommand(std::string input);
	std::vector <std::string> ParseCommand(std::string input);
}

typedef void (*CommandCallback)(std::vector <std::string>&, App&);

struct Command {
	std::string               name;
	CommandCallback           function;
	std::vector <std::string> help;
};

void InitCommands(App* p_app);

class CommandsSystem {
	public:
		// variables
		std::vector <Command> commands;

		// functions
		CommandsSystem();
		void AddCommand(
			std::string name, CommandCallback callback, std::vector <std::string> help
		);
		void    RunCommand(std::string name, std::vector <std::string> arguments);
		bool    CommandExists(std::string name);
		Command GetCommand(std::string name);
};

#endif