/*
	Author: Mohamed Kazma
	Description: Interface for all updateable classes
*/

#pragma once
#ifndef IUPDATEABLE_H
#define IUPDATEABLE_H

class IUpdateable
{
public:
	virtual void PhysicsUpdate() = 0;	// Call a physics update

private:
protected:
};
#endif // !IUPDATEABLE_H

