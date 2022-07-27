#include "INT.h"
using namespace heart;

INT::INT(std::string NAME, int VALUE) {
	val = VALUE;
	name = NAME;
}
INT::~INT() {
	val = 0;
	name = "";
}