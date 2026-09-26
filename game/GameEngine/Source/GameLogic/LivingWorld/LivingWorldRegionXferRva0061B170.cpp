// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// Vtable 0x01117258 slot 3 reaches this LivingWorldRegion transfer body.
#include "ascii_string.h"
#include "Common/System/xfer.h"
#include "coord2d.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <vector>

int bfmeCallFHA(void *first, void *second);
void *bfmeMakeBNG(void *first, void *second);
unsigned int bfmeHash0000DD28(unsigned int left, unsigned int right);

struct Rva0061B170TransferState
{
	char m_before18[0x18];
	bool m_at18;
};

class LivingWorldRegion
{
public:
	void rva0061B170(Xfer *xfer);

private:
	char m_beforeA8[0xA8];
	bool m_active;
	char m_toAC[3];
	int m_atAC;
	char m_toB4[4];
	void *m_madeBNG;
	AsciiString m_atB8;
	Coord2D m_atBC;
	int m_spawnNumber;
	int m_startNumber;
	int m_replaceDelay;
	bool m_oneShot;
	bool m_reclaimOrphans;
	char m_toD4[2];
	std::vector<AsciiString> m_names;
	Coord2D m_atE0;
	bool m_requireSpawner;
	char m_toEC[3];
	Rva0061B170TransferState *m_atEC;
};

void LivingWorldRegion::rva0061B170(Xfer *xfer)
{
	*xfer == m_active;
	int oldHandle = bfmeCallFHA(m_madeBNG, m_madeBNG);
	*xfer == oldHandle;
	m_madeBNG = bfmeMakeBNG((void *)oldHandle, (void *)oldHandle);
	*xfer == m_atAC;
	*xfer == m_atB8;
	*xfer == m_atBC;
	*xfer == m_oneShot;
	*xfer == m_reclaimOrphans;
	*xfer == m_spawnNumber;
	*xfer == m_startNumber;
	*xfer == m_replaceDelay;
	*xfer == m_atE0;
	*xfer == m_requireSpawner;
	if (xfer->IsLoading())
	{
		_ReadWriteBarrier();
		int count;
		*xfer == count;
		m_names.clear();
		for (int i = 0; i < count; ++i)
		{
			AsciiString name;
			*xfer == name;
			m_names.push_back(name);
		}
		unsigned int madeHandle = (unsigned int)m_madeBNG;
		unsigned int hash = bfmeHash0000DD28(madeHandle, 0xC56EC456);
		if (hash != 0x462E416F)
		{
			m_atEC->m_at18 = 1;
			return;
		}
		m_atEC->m_at18 = 0;
		return;
	}
	else
	{
		int count = m_names.size();
		*xfer == count;
		for (int i = 0; i < count; ++i)
		{
			AsciiString name(m_names[i]);
			*xfer == name;
		}
	}
}
