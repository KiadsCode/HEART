#include "STRING.h"
using namespace heart;

STRING::STRING(std::string NAME, std::string VALUE) {
	name = NAME;
	val = VALUE;
}
STRING::~STRING() {
	name = "";
	val = "";
}