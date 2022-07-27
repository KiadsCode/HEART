#pragma once
#include <string>
#include <iostream>
namespace heart {
	class STRING
	{
	public:
		std::string name, val;
		STRING(std::string NAME, std::string VALUE);
		~STRING();
		bool isUsing = false;
	};
}