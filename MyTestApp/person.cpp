#include "stdafx.h"
#include "person.h"


person::person()
{
	std::cout << "person::person() => default" << std::endl;
}

person::person(const std::string& n, const std::string& a, const std::string& t) :
	name(n),
	address(a)
{
	std::cout << "person::person()" << std::endl;
	telefoneNumbers.push_back(t);
}


person::person(const person&p) :
	name(p.name),
	address(p.address),
	telefoneNumbers(p.telefoneNumbers)
{
	std::cout << "person::person(const person&)" << std::endl;
}

person& person::operator=(const person&p)
{
	std::cout << "person::operator=(const person&)" << std::endl;
	if (this != &p) 
	{ 
		this->address = p.address;
		this->name = p.name;
		this->telefoneNumbers = p.telefoneNumbers;
	}
	// by convention, always return *this
	return *this;
}

person::person(person&& p) :
	name(p.name),
	address(p.address),
	telefoneNumbers(p.telefoneNumbers)
{
	std::cout << "person::person(const person&&)" << std::endl;
	p.name = "n.a";
	p.address = "n.a";
	p.telefoneNumbers.clear();
}

person& person::operator=(const person&&p)
{
	std::cout << "person::operator=(const person&)" << std::endl;
	if (this != &p)
	{
		this->address = p.address;
		this->name = p.name;
		this->telefoneNumbers = p.telefoneNumbers;
	}
	// by convention, always return *this
	return *this;
}

person::~person()
{
	std::cout << "person::~person = " << name << std::endl;
}


void person::print() const
{
	std::cout << "PP name=" << name << " , address=" << address << std::endl;
}
