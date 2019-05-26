#pragma once
#include <vector>
#include "person.h"

class contacts
{
public:
	contacts();
	~contacts();

	void add(const person& p);
	void add(person&& p);
	void remove(const person& p);

	void print();
private:
	bool find(const person& p);
private:
	std::vector<person> persons;
};

