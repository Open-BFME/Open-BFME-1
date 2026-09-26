// ?rva003C8160@LivingWorldRegionManager@@QAEPAVLivingWorldRegion@@PAUCoord3D@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x003C8160, 332 bytes.  The matched caller at 0x003C8B90 passes a
// Coord3D by pointer and consumes this member's LivingWorldRegion * result.
// The manager vtable and the existing 0x003C8A50 lookup establish the campaign
// and region layout.  The 0x00006C5D, 0x0000FE52, and 0x00021CEC thunks route
// the string operations and float-pair host call used by this method.

#include "ascii_string.h"

extern const char Rva006A16B0Empty[];

struct Coord3D
{
	float x;
	float y;
	float z;
};

class BfmeThingESM
{
public:
	virtual void release() = 0;

	int m_refCount;
};

// The retail pair is an eight-byte float aggregate.  Its source-level type
// name is established by the existing BfmeHostESM pin; keeping it POD lets
// this call use the same by-value x86 ABI as the body at 0x00A09BA0.
struct BfmePairESM
{
	BfmePairESM(float first, float second)
	{
		x = first;
		y = second;
	}

	BfmePairESM(const BfmePairESM &other) throw()
	{
		x = other.x;
		y = other.y;
	}

	~BfmePairESM();

	float x;
	float y;
};

class BfmeHostESM
{
public:
	char bfmeDoESM(BfmeThingESM *thing, BfmePairESM pair, void **out,
		int one, int oneAgain);
};

// This is the existing state singleton spelling used by the matched caller;
// the extra vtable slots below are the independently observed +0x7c lookup
// dispatch used only by this helper.
class Gen_00609320
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual BfmeThingESM *lookup(const char *name, int zero) = 0;
};

extern Gen_00609320 *g_bfmeStateDF;

class BfmeStateLookup
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual BfmeThingESM *lookup(const char *name, int zero) = 0;
};

class LivingWorldRegion;

struct LivingWorldRegionVector
{
	unsigned int size() const
	{
		return (unsigned int)(m_end - m_begin);
	}

	LivingWorldRegion **m_begin;
	LivingWorldRegion **m_end;
	LivingWorldRegion **m_capacity;

	LivingWorldRegion **begin() const
	{
		return m_begin;
	}

	LivingWorldRegion *operator[](unsigned int index) const
	{
		return m_begin[index];
	}
};

class LivingWorldRegion
{
public:
	unsigned char m_pad00[0x28];
	AsciiString m_name;
};

class LivingWorldRegionCampaign
{
public:
	AsciiString m_name;
	unsigned char m_pad04[0x2c];
	LivingWorldRegionVector m_regions;
};

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8160(Coord3D *position);

private:
	void *m_vtable;
	LivingWorldRegionCampaign *m_campaign;
	unsigned char m_pad08[0x1c];
	BfmeStateLookup *m_state;
};

LivingWorldRegion *LivingWorldRegionManager::rva003C8160(Coord3D *position)
{
	unsigned int index = 0;
	LivingWorldRegionVector *regions = &m_campaign->m_regions;

	if (regions->size() > 0)
	{
		do
		{
			{
				AsciiString fullName = (m_campaign->m_name + ".")
					+ regions->begin()[index]->m_name;
				const char *text = *(const char **)&fullName;
				if (text != 0)
					text += 8;
				else
					text = Rva006A16B0Empty;

				BfmeThingESM *thing = m_state->lookup(text, 0);

				if (thing != 0)
				{
					char ok = ((BfmeHostESM *)g_bfmeStateDF)->bfmeDoESM(
						thing, BfmePairESM(position->x, position->y), 0, 1, 1);

					--thing->m_refCount;
					if (thing->m_refCount == 0)
						thing->release();

					if (ok)
						return regions->begin()[index];
				}
			}

			++index;
		} while (index < regions->size());
	}

	return 0;
}
