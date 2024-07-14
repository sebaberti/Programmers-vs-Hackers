#pragma once
#include "Hacker.h"


class HackerDios : public Hacker
{
public:
	HackerDios();
	int attackUtn() override;
	void saySth() override;
};
