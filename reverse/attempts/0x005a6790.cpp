// ?setValue@Rva005A6790Object@@QAEHH@Z
// partial score=0.95 date=2026-09-09
// Clean C++ matches 56/60 bytes. The only remaining difference is the
// register allocation around the final Mouse vtable call.

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
		TheMouse->setCursor(m_value);
	return old;
}
