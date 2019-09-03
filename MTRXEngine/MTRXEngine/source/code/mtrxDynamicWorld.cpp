
#include <mtrxDynamicWorld.h>

mtrxDynamicWorld::mtrxDynamicWorld()
{
}

mtrxDynamicWorld::~mtrxDynamicWorld()
{}

mtrxDynamicWorld::Update()
{
	m_rbManager.PhysicsUpdate();
}
