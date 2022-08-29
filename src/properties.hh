#ifndef YCRAFT_PROPERTIES_HH
#define YCRAFT_PROPERTIES_HH

#include "_components.hh"

class Properties {
	private:
		struct Property {
			std::string key;
			std::string value;
		};
		std::vector <Property> properties;
		enum class TokenType {
			Key = 0,
			Equals = 1,
			Value = 2
		};
		struct Token {
			TokenType   type;
			std::string content;
			size_t      line;
		};
	public:
		Properties() {}
		void         Parse(const std::string& str);
		std::string& Get(const std::string& key);
		std::string& operator[](std::string key);
		bool         Contains(const std::string& key);
		std::string  Stringify();
};

#endif
