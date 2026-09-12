// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The vtable at 0x010E75C0 belongs to the twelve-byte FX particle-system
// service created by the retail factory.  Its slot 8 body loads the FX
// particle-system definitions through the three-string INI entry point.

template <typename T>
class StringBase
{
protected:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: StringBase<char>(other) {}
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
};

class INI
{
public:
	INI();
	~INI();
	void load(BFMERetailAsciiString file, BFMERetailAsciiString block,
		BFMERetailAsciiString name, int loadType, int reload);

private:
	char m_unported[0x848];
};

class Rva010E75C0FXParticleSystemManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void reset();
	virtual void Rva00339330LoadFXParticleSystem(const char *name);
};

void Rva010E75C0FXParticleSystemManager::Rva00339330LoadFXParticleSystem(
	const char *name)
{
	reset();
	INI ini;
	ini.load(BFMERetailAsciiString("Data\\INI\\FXParticleSystem.ini"),
		BFMERetailAsciiString("FXParticleSystem"),
		BFMERetailAsciiString(name), 1, 0);
}
