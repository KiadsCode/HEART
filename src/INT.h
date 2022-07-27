#pragma once
#include <string>
#include <iostream>
namespace heart {
	class INT
	{
	public:
		std::string name;
		int val;
		INT(std::string NAME, int VALUE);
		~INT();
		bool isUsing = false;
	};
}