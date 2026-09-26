// cl: /DNDEBUG /MD /EHsc

// W3DFloorDrawModuleDataBase's constructor, retail 0x00759460.
// The derived W3DFloorDrawModuleData constructor remains in its original TU;
// this focused TU keeps that call opaque to MSVC while supplying the real
// BFME base layout.

class W3DFloorDrawModuleDataBase
{
public:
	__declspec(noinline) W3DFloorDrawModuleDataBase();
	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[4];
	unsigned int m_unmodelled_08;
};

__declspec(noinline) W3DFloorDrawModuleDataBase::W3DFloorDrawModuleDataBase()
	: m_unmodelled_08( 0 )
{
}
