#include "stdafx.h"
#include "ChronoTest.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;

static std::string toString(const chrono::system_clock::time_point& tp, bool gmt = false)
{
	// Convert to C time_t 
	std::time_t time = chrono::system_clock::to_time_t(tp);
	// Calculate the millisecond part
	auto tse_ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	auto tse_s  = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
	auto milliseconds = tse_ms - tse_s;

	// Construct the format string
	std::ostringstream fmt;
	fmt << "%Y-%m-%d %H:%M:%S." << std::setfill('0') << std::setw(3) << milliseconds.count() << " %z";
	// Format the string 
	char mbstr[64];
	struct tm buf;
	if (gmt)
		gmtime_s(&buf, &time);
	else
		localtime_s(&buf, &time);
	if (std::strftime(mbstr, sizeof(mbstr), fmt.str().c_str(), &buf))
	{
		return std::string(mbstr);
	}
	return std::string();
}

ChronoTest::ChronoTest()
{
}


ChronoTest::~ChronoTest()
{
}



void ChronoTest::test()
{
	// std::chrono::time_point
	auto tp = chrono::system_clock::now();
	std::cout << "Now local= " << toString(tp).c_str() << std::endl;
	std::cout << "Now GMT  = " << toString(tp, true).c_str() << std::endl;


}
