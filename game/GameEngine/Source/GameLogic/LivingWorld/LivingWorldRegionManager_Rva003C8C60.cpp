// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x003C8C60.  The receiver is the LivingWorldRegionManager whose
// constructor is at 0x003C8880.  Its +0x04 campaign is the 0x58-byte object
// built by 0x003C9B60; that parser fills the +0x30 vector with 0xF4-byte
// LivingWorldRegion objects built by 0x0061AF80.  Those objects install the
// 0x01117258 vtable, whose name slot returns "LivingWorldRegion".  This body
// uses the same typed lookup at 0x003C8A50 and dispatches the assignment at
// 0x0061A860 to either one named region or every active region.  That callee
// assigns the already-constructed +0xD4 vector; it does not begin its lifetime.
// The original method name is unavailable, so only that name remains
// address-derived.

#include "ascii_string.h"

class Rva0076F980Mid;

class LivingWorldRegion
{
public:
	void rva0061A860(
		const Rva0076F980Mid &names,
		unsigned int spawnNumber,
		unsigned int startNumber,
		unsigned int replaceDelay,
		unsigned char oneShot,
		unsigned char reclaimOrphans,
		unsigned char requireSpawner);

	unsigned char m_unmodelled00[0xA8];
	unsigned char m_active;
};

struct LivingWorldRegionVector
{
	unsigned int size() const
	{
		return (unsigned int)(m_end - m_begin);
	}

	LivingWorldRegion *operator[](unsigned int index) const
	{
		return m_begin[index];
	}

	LivingWorldRegion **m_begin;
	LivingWorldRegion **m_end;
	LivingWorldRegion **m_capacity;
};

class LivingWorldRegionCampaign
{
public:
	unsigned char m_unmodelled00[0x30];
	LivingWorldRegionVector m_regions;
};

class LivingWorldRegionManager
{
public:
	void rva003C8C60(
		const AsciiString &regionName,
		const Rva0076F980Mid &names,
		unsigned int spawnNumber,
		unsigned int startNumber,
		unsigned int replaceDelay,
		unsigned char oneShot,
		unsigned char reclaimOrphans,
		unsigned char requireSpawner);
	LivingWorldRegion *rva003C8A50(const AsciiString &regionName);

private:
	void *m_vtable;
	LivingWorldRegionCampaign *m_currentCampaign;
};

void LivingWorldRegionManager::rva003C8C60(
	const AsciiString &regionName,
	const Rva0076F980Mid &names,
	unsigned int spawnNumber,
	unsigned int startNumber,
	unsigned int replaceDelay,
	unsigned char oneShot,
	unsigned char reclaimOrphans,
	unsigned char requireSpawner)
{
	if (regionName.compare("All") == 0)
	{
		LivingWorldRegionCampaign *campaign = m_currentCampaign;
		LivingWorldRegionVector *regions = &campaign->m_regions;
		unsigned int index = 0;

		if (regions->size() > 0)
		{
			do
			{
				LivingWorldRegion *region = (*regions)[index];
				if (region->m_active)
				{
					region->rva0061A860(names, spawnNumber, startNumber,
						replaceDelay, oneShot, reclaimOrphans,
						requireSpawner);
				}

				++index;
			} while (index < regions->size());
		}
	}
	else
	{
		LivingWorldRegion *region = rva003C8A50(regionName);
		if (region != 0)
		{
			region->rva0061A860(names, spawnNumber, startNumber,
				replaceDelay, oneShot, reclaimOrphans, requireSpawner);
		}
	}
}
