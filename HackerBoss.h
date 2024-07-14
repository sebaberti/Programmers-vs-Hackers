#pragma once
#include "Hacker.h"

class HackerBoss : public Hacker
{
public:
	HackerBoss();
	int attackUtn() override;

	void saySth() override;
	virtual void moveHacker(int arr[][30]) override;
	virtual void animation(float) override;
	virtual void getFreezed() override;
};

