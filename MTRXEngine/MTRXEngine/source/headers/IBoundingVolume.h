#pragma once

class IBoundingVolume
{
public:
	virtual float GetGrowth() = 0;
	virtual float GetSize() = 0;
};