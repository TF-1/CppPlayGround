#pragma once
#include <string>
#include <iostream>
#include <vector>

class person
{
public:
	person();
	person(const std::string& n, const std::string& a, const std::string& t);
	~person();

	person(const person&);
	person& operator=(const person&);
	person(person&&);
	person& operator=(const person&&);

	void print() const;
public:
	std::string name;
	std::string address;
	std::vector<std::string> telefoneNumbers;
};

