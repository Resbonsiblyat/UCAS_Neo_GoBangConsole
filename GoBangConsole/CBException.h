#pragma once
#include <string>
class CBException {

public:
	std::string msg;
	CBException(std::string s) : msg("ÆåÅÌÄ£¿é´íÎó£º" + s) {}

};