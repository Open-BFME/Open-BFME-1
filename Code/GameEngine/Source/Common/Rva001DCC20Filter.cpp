// cl: /DNDEBUG /MD /EHs-c-
// Partition-style filter: Object query(m_viewer, 0), then if that fails and
// the viewer is type-1, treat a recently-active weapon as a hit. The query
// callee is still the 725-byte dump at 0x001CF9F0 (ILT 0x00047ED8).

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	bool query(Object *viewer, int extra);
	bool bfmeHasActiveOrRecentlyActiveWeapon(void) const;

	unsigned char m_unreconstructed_00[0x2C];
	int m_type;
};

class Rva001DCC20Filter
{
public:
	bool allow(Object *object);

private:
	unsigned char m_unreconstructed_00[8];
	Object *m_viewer;
	unsigned char m_match;
};

bool Rva001DCC20Filter::allow(Object *object)
{
	unsigned char ok = (unsigned char)object->query(m_viewer, 0);
	if (!ok)
	{
		if (m_viewer && m_viewer->m_type == 1)
		{
			if (object->bfmeHasActiveOrRecentlyActiveWeapon())
				ok = 1;
		}
	}

	return m_match != ok;
}
