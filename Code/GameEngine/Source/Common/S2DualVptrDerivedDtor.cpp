// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Destructor twin of the dual-vptr constructor at 0x00694E00
// (S2DualVptrDerivedCtors.cpp). Restores the second-base vtable at +8 to
// 0x01073744 then tails into the first-base destructor at 0x009A1A40.

class S4Base009A1A40
{
public:
	virtual ~S4Base009A1A40();
	virtual void keepFirst();
	int m_pad;
};

class GenBase01073744
{
public:
	virtual ~GenBase01073744() {}
	virtual void keepSecond();
};

class __declspec(novtable) Rva00694E00 : public S4Base009A1A40, public GenBase01073744
{
public:
	virtual ~Rva00694E00();
	virtual void keepOwn();
};

// @??1Rva00694E00@@UAE@XZ 0x00694E30
Rva00694E00::~Rva00694E00()
{
}
