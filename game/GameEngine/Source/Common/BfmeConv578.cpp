#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class WindowManager
{
public:
};

extern WindowManager *g_rva012F19E8WindowManager;

class Rva0046B2A0
{
public:
	void invoke();
};

typedef void (WindowManager::*WindowManagerStringMember)(const AsciiString *);

union WindowManagerStringCast
{
	void (Rva0046B2A0::*b2a0Member)();
	WindowManagerStringMember member;
};

// The recorded thunk takes its manager in ECX and forwards the string pointer.
static __forceinline void callWindowManagerInvoke(
	WindowManager *manager, void (Rva0046B2A0::*function)(), AsciiString *name)
{
	WindowManagerStringCast cast;
	cast.b2a0Member = function;
	(manager->*cast.member)(name);
}

class BfmeThingCDA
{
public:
	void bfmeStepCDA();
	void bfmeGoCDA(void *what);

	unsigned char m_bfmeFlag;
	unsigned char m_bfmeReady;
	unsigned char m_bfmePad02[2];
	void *m_bfmeVal;
	unsigned char m_bfmeCommandReady;
	unsigned char m_bfmePad09[0x13];
	unsigned char m_bfmePortraitReady;
	unsigned char m_bfmePad1D[0x0b];
	void *m_bfmePortrait;
};

void j_00001f32();
void j_0002d817();
void j_0001587f();


class BfmeLayoutVHH
{
};

void bfmeGoVHH(char index, BfmeLayoutVHH *name);

class Gen_00588A30
{
public:
	void bfmeReset(int index);
};

void BfmeThingCDA::bfmeGoCDA(void *what)
{
	if (what != m_bfmeVal || !m_bfmeFlag)
	{
		bfmeStepCDA();
		m_bfmeVal = what;
		m_bfmeFlag = true;
	}
}

// ?bfmeStepCDA@BfmeThingCDA@@QAEXXZ
void BfmeThingCDA::bfmeStepCDA()
{
	if (m_bfmeReady)
	{
		if (m_bfmeCommandReady)
		{
			j_00001f32();
			m_bfmeCommandReady = 0;
		}

		j_0002d817();
		m_bfmePortraitReady = 0;
		j_0001587f();
		m_bfmeReady = 0;

		if (m_bfmePortrait != 0)
		{
			{
				AsciiString name("CommandUI/Portrait");
				callWindowManagerInvoke(g_rva012F19E8WindowManager, &Rva0046B2A0::invoke, &name);
			}
			m_bfmePortrait = 0;
		}

		AsciiString name;
		for (int index = 0; index < 6; ++index)
		{
			bfmeGoVHH((char)index, (BfmeLayoutVHH *)&name);
			callWindowManagerInvoke(g_rva012F19E8WindowManager, &Rva0046B2A0::invoke, &name);
		}
	}

	m_bfmeFlag = 0;
	m_bfmeVal = 0;
	for (int index = 0; index < 6; ++index)
		((Gen_00588A30 *)this)->bfmeReset(index);
}
