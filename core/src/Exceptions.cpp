//
// EPITECH PROJECT, 2018
// arcade
// File description:
// exceptions
//

#include "Exceptions.hpp"

namespace arcade {
arc_Exceptions::arc_Exceptions(const std::string &message,
			       const std::string &component)
	: _message(message)
	, _component(component)
{
}

const std::string &arc_Exceptions::getComponent() const
{
	return _component;
}
const char *arc_Exceptions::what() const throw()
{
	return _message.c_str();
}
} // namespace arcade
