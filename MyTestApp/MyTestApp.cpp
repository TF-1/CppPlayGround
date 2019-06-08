// MyTestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "person.h"
#include "contacts.h"
#include "ChronoTest.h"

person getPerson(int i)
{
	std::cout << "getPerson " << i << std::endl;
	if (i == 1) return person("Bob", "main street 1", "000-123456");
	else if (i == 2) return person("Max", "second street 2", "111-123456");
	else if (i == 3) return person("Alice", "Third street 2", "222-123456");
	return person("John Doe", "church street 1", "000-123456");
}

void Test1()
{
	std::cout << "Create on stack" << std::endl;
	person p1("Rich", "main street 1", "000-123456");
	person p2("Cornelius", "second street 2", "111-123456");
	person p3("Don", "Third street 2", "222-123456");

	contacts myContacts;
	std::cout << "Filling contact book P1" << std::endl;
	myContacts.add(getPerson(1)); // temporary object so call rvalue function
	std::cout << "Filling contact book P2" << std::endl;
	myContacts.add(getPerson(2));
	std::cout << "Filling contact book P3" << std::endl;
	myContacts.add(getPerson(3));
	std::cout << "Filling contact book P4" << std::endl;
	myContacts.add(std::move(p1)); // force rvalue function 
	std::cout << "Filling contact book P5" << std::endl;
	myContacts.add(std::move(p2));
	std::cout << "Filling contact book P6" << std::endl;
	myContacts.add(std::move(p3));

	std::cout << "Person 1: "; p1.print();
	std::cout << "Person 2: "; p2.print();
	std::cout << "Person 3: "; p3.print();

	myContacts.print();
}

void Test2()
{
	ChronoTest chronoTest;
	
	chronoTest.test();
}

int main()
{
	Test2();

	int i;
	std::cin >> i;

    return 0;
}

