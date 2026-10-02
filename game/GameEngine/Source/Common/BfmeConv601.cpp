// The owned object is a CriticalSectionClass::LockClass sentry: it is deleted
// here, so the destructor reached is the sentry's (mutex.h).
#include "../../../Libraries/Source/WWVegas/WWLib/mutex.h"

class BfmeRefCHC
{
};

class BfmeThingCHC
{
public:
	void bfmeGoCHC(BfmeRefCHC *what);
	CriticalSectionClass::LockClass *m_bfmeRef;
};

void BfmeThingCHC::bfmeGoCHC(BfmeRefCHC *what)
{
	CriticalSectionClass::LockClass *cur = m_bfmeRef;
	if (what != (BfmeRefCHC *)cur)
	{
		if (cur != 0)
		{
			delete cur;
		}
		m_bfmeRef = (CriticalSectionClass::LockClass *)what;
	}
}