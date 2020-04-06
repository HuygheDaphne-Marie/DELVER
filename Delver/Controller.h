#pragma once
class Controller
{
public:
	Controller() = default;
	virtual ~Controller();

	virtual void Update(float elapsedSec) = 0;
};

