#pragma once
#include "Hacker.h"


class HackerTrainee : public Hacker 
{
public:
	HackerTrainee();
	int attackUtn() override;
	void saySth() override;
};

