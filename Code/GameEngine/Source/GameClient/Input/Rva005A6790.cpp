// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
// stlport
#include "PreRTS.h"

extern void j_000423b6(void);

struct Rva00579160Manager {};
extern Rva00579160Manager *Rva00579160TheManager;

class Mouse;
typedef Mouse Rva005A63D0Mouse;
extern Rva005A63D0Mouse *TheMouse;

typedef void (__fastcall *Rva005A6790Slot38Fn)(Rva005A63D0Mouse *, int, int);
struct Rva005A6790MouseVtable
{
	void *slot00;
	void *slot04;
	void *slot08;
	void *slot0c;
	void *slot10;
	void *slot14;
	void *slot18;
	void *slot1c;
	void *slot20;
	void *slot24;
	void *slot28;
	void *slot2c;
	void *slot30;
	void *slot34;
	Rva005A6790Slot38Fn setCursor;
};

struct Rva005A6790Object
{
	char m_padding[0x1ec];
	int m_value;
	int setValue(int value);
};

int Rva005A6790Object::setValue(int value)
{
	int old = m_value;
	m_value = value;
	typedef bool (__fastcall *Check)(Rva00579160Manager *);
	if (((Check)j_000423b6)(Rva00579160TheManager))
	{
		Rva005A63D0Mouse *mouse = TheMouse;
		int cursorValue = m_value;
		Rva005A6790MouseVtable *vtable =
			*(Rva005A6790MouseVtable **)mouse;
		vtable->setCursor(mouse, cursorValue, cursorValue);
	}
	return old;
}
