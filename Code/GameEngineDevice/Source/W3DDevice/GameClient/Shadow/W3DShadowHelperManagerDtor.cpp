// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// FILE: W3DShadowHelperManagerDtor.cpp //////////////////////////////////////
//
// Sibling-file definition for W3DShadowHelperManager's destructor (declared
// as a stand-in in W3DShadow.cpp). See the comment there: defining this in
// the same TU as ~W3DShadowManager's delete-call site made MSVC inline it and
// broke that already-matched row, so the real body lives here instead.
//
// The dtor body is two back-to-back inlined REF_PTR_RELEASE(x) sequences
// (dec [x+4]; if it hits zero, call [x]'s vtable slot 0 -- Delete_This --
// then null the slot): exactly RefCountClass::Release_Ref's inlined shape
// (see WWLib/refcount.h, "Release_Ref is NOT virtual in retail"). The two
// members' real types are lost; RefCountClass* reproduces the byte-exact
// inlined release since neither Release_Ref nor Delete_This is overridden
// through this stand-in.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
		{
			Delete_This();
		}
	}

protected:
	virtual void Delete_This(void);						///< vtable +0x00

	int NumRefs;										///< retail this+0x04
};

class W3DShadowHelperManager
{
public:
	~W3DShadowHelperManager();
private:
	RefCountClass *m_helper1;								///< retail this+0x00
	RefCountClass *m_helper2;								///< retail this+0x04
};

W3DShadowHelperManager::~W3DShadowHelperManager()
{
	if (m_helper1 != 0)
	{
		m_helper1->Release_Ref();
		m_helper1 = 0;
	}

	if (m_helper2 != 0)
	{
		m_helper2->Release_Ref();
		m_helper2 = 0;
	}
}
