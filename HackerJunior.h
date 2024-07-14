#pragma once
#include "Hacker.h"


class HackerJunior : public Hacker
{
public:
	HackerJunior();
	int attackUtn() override;
	void saySth() override;
};