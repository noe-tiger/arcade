//
// EPITECH PROJECT, 2018
// arcade
// File description:
// exceptions
//

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <exception>
#include <string>

namespace arcade {
class arc_Exceptions : public std::exception {
      public:
	arc_Exceptions(const std::string &message,
		       const std::string &component = "Unknown");
	const std::string &getComponent() const;
	const char *what() const throw();

      private:
	std::string _message;
	std::string _component;
};
} // namespace arcade

#endif // EXCEPTIONS_HPP_
