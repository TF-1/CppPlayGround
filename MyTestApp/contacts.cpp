#include "stdafx.h"
#include "contacts.h"
#include <algorithm>


contacts::contacts()
{
}


contacts::~contacts()
{
}

void contacts::add(const person& p)
{
	std::cout << "contacts::add(const person&)" << std::endl;
	person p1(std::move(p));
	p.print();
	p1.print();
}

void contacts::add(person&& p)
{
	std::cout << "contacts::add(const person&&)" << std::endl;
	person p1(std::move(p));
	p.print();
	p1.print();
}

void contacts::remove(const person& p)
{
	auto position = std::find_if(persons.begin(), persons.end(), 
		[&p](const person& p2)
		{
			return p.name == p2.name; 
		});

	if (position != persons.end())
		persons.erase(position);
}

void contacts::print()
{
	std::cout << "=== Contacts Book" << std::endl;
	for (const auto& p : persons)
	{
		std::cout << p.name << "\t" << p.address << "\t";
		for (const auto& t : p.telefoneNumbers)
			std::cout << t << " ";
		std::cout << std::endl;
	}
}


bool contacts::find(const person& p)
{
	auto position = std::find_if(persons.begin(), persons.end(),
		[&p](const person& p2)
	{
		return p.name == p2.name;
	});

	return (position != persons.end());
}


