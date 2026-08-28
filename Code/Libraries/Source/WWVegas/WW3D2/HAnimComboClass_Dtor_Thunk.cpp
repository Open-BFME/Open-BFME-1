// cl: /DNDEBUG /MD /EHsc

// Slot 0 of the vtable at 0x0113EAE0, which ??0HAnimComboClass installs -- a
// constructor writes the vptr of its own class, so the table is named by whoever
// stores it and slot 0 of a table whose class has a virtual destructor is that
// destructor's deleting stub.
//
// The destructor releases the buffer at +4 only when the flag at +0xD says this
// object owns it, then clears the flag and the count whether it owned one or
// not. The guard is a bare `if` on the flag rather than a comparison with true:
// retail tests the byte against itself.
//
// The buffer is freed with the scalar operator delete and no destructor call, so
// whatever it points at has none -- it is written here as a byte pointer, which
// is the weakest claim that produces those bytes.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class HAnimComboClass
{
public:
	HAnimComboClass(void);
	virtual ~HAnimComboClass(void);

private:
	unsigned char *m_anims;
	int m_count;
	bool m_pad;
	bool m_owned;
};

// ??_GHAnimComboClass@@UAEPAXI@Z
HAnimComboClass::~HAnimComboClass(void)
{
	if (m_anims != 0 && m_owned) {
		delete m_anims;
		m_anims = 0;
	}
	m_owned = false;
	m_count = 0;
}
