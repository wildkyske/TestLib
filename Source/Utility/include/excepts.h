#pragma once
#ifndef EXCEPTS_H
#define EXCEPTS_H

#include <exception>

class msgexcpt : public std::exception
{
#if __linux__
public:
	msgexcpt(const char* const& msg) throw() : _msg(msg){}
	virtual ~msgexcpt() throw() {}
	virtual const char* what() const throw() {return _msg;}
protected:
	const char* _msg;
#else
public:
	msgexcpt(const char* const& msg) throw() : std::exception(msg) {}
	virtual ~msgexcpt() throw() {}
#endif
};

#endif
