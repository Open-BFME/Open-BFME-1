// ?clearStatusBit63@Rva00266EB0SiegeDeployBase@@QAEXXZ
// partial score=0.62 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// SiegeDeploy helper at 0x00266EF0: setStatus on the object at +8 with
// BitFlags dword1 = 0x80000000 (status bit 63), then transition(0), then
// clear the dword at +0x40. Sibling of Rva00266EB0SiegeDeployStateDispatch.

class Object
{
public:
	void setStatus(const unsigned *flags, bool set);
};

class Rva00266EB0SiegeDeployBase
{
public:
	void transition(int value);
	void clearStatusBit63(void);

private:
	unsigned char m_pad00[8];
	Object *m_object;
	unsigned char m_pad0C[0x34];
	unsigned m_field40;
};

// ?clearStatusBit63@Rva00266EB0SiegeDeployBase@@QAEXXZ
void Rva00266EB0SiegeDeployBase::clearStatusBit63(void)
{
	unsigned flags[3];
	flags[0] = 0;
	flags[2] = 0;
	flags[1] = 0x80000000u;
	m_object->setStatus(flags, false);
	transition(0);
	m_field40 = 0;
}
