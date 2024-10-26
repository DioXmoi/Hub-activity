#pragma once

#ifndef _14_30_25_10_2024_GITHUBUSERNAMEVALIDATOR_H_
#define _14_30_25_10_2024_GITHUBUSERNAMEVALIDATOR_H_


#include <ctype.h>
#include <string_view>

namespace GitHub {
	namespace UsernameValidator {
		static constexpr std::size_t min{ 3 };
		static constexpr std::size_t max{ 39 };

		bool isValidSize(std::string_view username) {
			return username.size() >= min && username.size() <= max;
		}

		bool isValidLetter(char ch) {
			return (ch >= 'a' && 'z' <= ch) ||
				(ch >= 'A' && 'Z' <= ch);
		}

		bool  isValidPunct(char ch) {
			return ch == '-';
		}

		bool isValidSymbol(char ch) {
			return std::isdigit(ch) || isValidLetter(ch) || isValidPunct(ch);
		}

		bool IsValidUsername(std::string_view username) {
			if (!isValidSize(username)) {
				return false;
			}

			// Check if the first character is a letter and ends with a letter
			if (isValidPunct(username.front()) || isValidPunct(username.back())) {
				return false;
			}

			for (const auto& ch : username) {
				if (!isValidSymbol(ch)) {
					return false;
				}
			}

			return true;
		}
	}
}


#endif // !_14_30_25_10_2024_GITHUBUSERNAMEVALIDATOR_H_
