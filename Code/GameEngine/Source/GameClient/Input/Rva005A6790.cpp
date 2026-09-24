// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
// stlport
#include "PreRTS.h"

extern void j_000423b6(void);

struct Rva00579160Manager {};
extern Rva00579160Manager *Rva00579160TheManager;

struct Rva005A63D0Mouse
{
	virtual void slot00(void); virtual void slot04(void);
	virtual void slot08(void); virtual void slot0c(void);
	virtual void slot10(void); virtual void slot14(void);
	virtual void slot18(void); virtual void slot1c(void);
	virtual void slot20(void); virtual void slot24(void);
	virtual void slot28(void); virtual void slot2c(void);
	virtual void slot30(void); virtual void slot34(void);
	virtual void setCursor(int value);
};
extern Rva005A63D0Mouse *TheMouse;

typedef void (__fastcall *Rva005A6790Slot38Fn)(Rva005A63D0Mouse *, int, int);
struct Rva005A6790MouseVtable
{
	void *slots[14];
	Rva005A6790Slot38Fn slot38;
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
		vtable->slot38(mouse, cursorValue, cursorValue);
	}
	return old;
}
