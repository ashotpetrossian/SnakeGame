#pragma once

#include <exception>
#include <string>

class SnakeException : public std::exception
{
private:
	std::string message;
public:
	explicit SnakeException(const std::string& s) : message{s} { }

	const char* what() const noexcept override
	{
		return message.c_str();
	}
};

class CollisionException : public SnakeException
{
public:
	explicit CollisionException(const std::string& msg) :
		SnakeException("Collision!" + msg) { }
};

class WindowCloseException : public SnakeException
{
public:	
	explicit WindowCloseException(const std::string& msg) :
		SnakeException("Window closed!" + msg) { }
};

class PathFindException : public SnakeException
{
public:
	explicit PathFindException(const std::string& msg) :
		SnakeException("Cannot find a path: " + msg) { }
};