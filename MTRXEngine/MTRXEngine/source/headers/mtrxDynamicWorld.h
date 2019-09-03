#pragma once

class mtrxDynamicWorld
{
public:
	mtrxDynamicWorld();
	~mtrxDynamicWorld();

	Update();

private:
	RigidbodyManager m_rbManager;
	ParticleManager m_pManager;
};