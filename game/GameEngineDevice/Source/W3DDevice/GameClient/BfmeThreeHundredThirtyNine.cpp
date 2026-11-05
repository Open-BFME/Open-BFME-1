// MouseThreadClass::MouseThreadClass, retail 0x00700240 (20 bytes): runs the
// ThreadClass base constructor with a null name (Zero Hour's defaulted
// argument) and installs ??_7MouseThreadClass@@6B@.
// Open-BFME-2's matched MouseThreadClass constructor is byte-identical and
// BFME1's ILT slot confirms the decoration.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/thread.h
class ThreadClass
{
public:
	ThreadClass(const char *name);

protected:
	void *m_vptr;	// +0x00
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp
class MouseThreadClass : public ThreadClass
{
public:
	MouseThreadClass();
};

extern "C" void *__identifier("??_7MouseThreadClass@@6B@")[];

MouseThreadClass::MouseThreadClass() : ThreadClass(0)
{
	m_vptr = __identifier("??_7MouseThreadClass@@6B@");
}
