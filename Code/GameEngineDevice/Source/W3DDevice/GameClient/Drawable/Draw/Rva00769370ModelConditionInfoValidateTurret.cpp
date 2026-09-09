// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Ireference/shims/stringinline
//
// Retail 0x00769370, 204 bytes.  The constructor/destructor layout and the
// two 0x18-spaced turret records identify this as a ModelConditionInfo-shaped
// object, but the original BFME method spelling is not recovered.  Keep the
// owning method address-derived until a named caller proves the source name.
//
// The stack argument is the retail pointer-key lookup owner.  Its exact body
// is Rva00769260Owner::lookup, and the two singleton views below intentionally
// reuse the proven data-symbol spellings from isPausedOrLoading.cpp.

#include "StringInline.h"

struct Rva0075B660Logic
{
	char m_pad[0x6b];
	bool m_flag;
};

struct Rva0075B660State
{
	char m_pad[0x54];
	bool m_flag;
};

extern Rva0075B660Logic *TheBfmeGameLogic;
extern Rva0075B660State *TheGameState;
extern void setFPMode(void);

class Rva00769260Owner
{
public:
	void *lookup(void *key, int *value);
};

class Gen_007622C0
{
public:
	AsciiString method(void) const;
};

struct Rva00769370AsciiData
{
	int m_refCount;
	unsigned short m_length;
};

struct Rva00769370AsciiView
{
	Rva00769370AsciiData *m_data;

	bool isEmpty(void) const
	{
		return m_data == 0 || m_data->m_length == 0;
	}
};

struct Rva00769370TurretInfo
{
	unsigned int m_angleNameKey;
	unsigned int m_pitchNameKey;
	float m_angle;
	float m_pitch;
	int m_angleBone;
	int m_pitchBone;
};

class Rva00769370ModelConditionInfo
{
public:
	void validateTurretInfo(Rva00769260Owner *owner);

private:
	char m_pad00[0xf0];
	Rva00769370TurretInfo m_turrets[2];
	char m_pad120[4];
	unsigned char m_validStuff;
};

void Rva00769370ModelConditionInfo::validateTurretInfo(Rva00769260Owner *owner)
{
	if (m_validStuff != 0)
		return;

	setFPMode();
	AsciiString model = reinterpret_cast<const Gen_007622C0 *>(this)->method();

	for (int turretSlot = 0; turretSlot < 2; ++turretSlot)
	{
		Rva00769370TurretInfo &turret = m_turrets[turretSlot];
		bool canLookup =
			(TheBfmeGameLogic != 0 && TheBfmeGameLogic->m_flag) ||
			(TheGameState != 0 && TheGameState->m_flag);
		const Rva00769370AsciiView &modelView =
			reinterpret_cast<const Rva00769370AsciiView &>(model);

		if (canLookup && !modelView.isEmpty())
		{
			if (turret.m_angleNameKey != 0)
			{
				if (owner->lookup(reinterpret_cast<void *>(turret.m_angleNameKey),
					&turret.m_angleBone) == 0)
					turret.m_angleBone = 0;
			}
			else
			{
				turret.m_angleBone = 0;
			}

			if (turret.m_pitchNameKey != 0)
			{
				if (owner->lookup(reinterpret_cast<void *>(turret.m_pitchNameKey),
					&turret.m_pitchBone) == 0)
					turret.m_pitchBone = 0;
			}
			else
			{
				turret.m_pitchBone = 0;
			}
		}
		else
		{
			turret.m_angleBone = 0;
			turret.m_pitchBone = 0;
		}
	}

	m_validStuff = 1;
}
