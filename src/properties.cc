#include "properties.hh"
#include "util.hh"

void Properties::Parse(const std::string& str) {
	std::string         reading;
	std::vector <Token> tokens;
	size_t              currentLine = 1;

	for (size_t i = 0; i <= str.length(); ++i) {
		if (str[i] == '\n') {
			++ currentLine;
		}
		switch (str[i]) {
			case '=': { // property
				tokens.push_back({TokenType::Key, Util::Trim(reading), currentLine});
				tokens.push_back({TokenType::Equals, "", currentLine});
				reading = "";
				break;
			}
			case '\n':
			case '\0': { // value
				tokens.push_back({TokenType::Value, Util::Trim(reading), currentLine});
				reading = "";
				break;
			}
			default: {
				reading += str[i];
				break;
			}
		}
	}

	if (tokens.size() % 3 != 0) {
		fprintf(
			stderr, "[ERROR] Missing tokens around line %lli\n",
			(long long int) tokens.back().line
		);
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < tokens.size(); ++i) {
		if (tokens[i].type == TokenType::Key) {
			std::string key = tokens[i].content;
			++ i;
			if (tokens[i].type == TokenType::Equals) {
				++ i;
				if (tokens[i].type == TokenType::Value) {
					Get(key) = tokens[i].content;
				}
				else {
					fprintf(
						stderr, "[ERROR] Expected value at line %lli\n",
						(long long int) tokens[i].line
					);
					exit(EXIT_FAILURE);
				}
			}
			else {
				fprintf(
					stderr, "[ERROR] Expected equals at line %lli\n",
					(long long int) tokens[i].line
				);
				exit(EXIT_FAILURE);
			}
		}
		else {
			fprintf(
				stderr, "[ERROR] Expected key at line %lli\n",
				(long long int) tokens[i].line
			);
			exit(EXIT_FAILURE);
		}
	}
}

std::string& Properties::Get(const std::string& key) {
	for (auto& prop : properties) {
		if (prop.key == key) {
			return prop.value;
		}
	}
	properties.push_back({key, ""});
	return properties.back().value;
}

std::string& Properties::operator[](std::string key) {
	return Get(key);
}

bool Properties::Contains(const std::string& key) {
	for (auto& prop : properties) {
		if (prop.key == key) {
			return true;
		}
	}
	return false;
}

std::string Properties::Stringify() {
	std::string ret;
	for (auto& prop : properties) {
		ret += prop.key + " = " + prop.value + "\n";
	}
	return ret;
}
