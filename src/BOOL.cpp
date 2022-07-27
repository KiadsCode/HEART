#include "BOOL.h"
using namespace heart;

BOOL::BOOL(std::string NAME, std::string VALUE){
    name = NAME;
    val = VALUE;
}
BOOL::~BOOL() {
    name = "";
    val = "";
}