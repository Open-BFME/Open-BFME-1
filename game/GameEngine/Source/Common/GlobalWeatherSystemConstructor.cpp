// cl: /DNDEBUG /MD /EHsc /O2
//
// The constructor at retail 0x0039B450 belongs to the same multiple-inheritance
// family as the matched Rva0039B560 destructor at 0x0039B560. The constructor
// calls SubsystemInterface at 0x009A1A30, installs the two family vtables, and
// builds the five eight-byte elements at +0x28 through the CRT vector helper.

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() { }
};

class SubsystemInterface
{
public:
	SubsystemInterface();                                      ///< matched 0x009A1A30
	virtual ~SubsystemInterface();                            ///< matched 0x009A1A40

private:
	unsigned int m_name;
};

class HRBMD_Buffer
{
public:
	HRBMD_Buffer();                                            ///< pinned 0x0003747A
	~HRBMD_Buffer();                                           ///< pinned 0x0001A401

private:
	unsigned int m_body;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) { }
	~BFMERetailAsciiString();

	void *m_data;
};

class Rva0039B450Element
{
public:
	Rva0039B450Element();                                      ///< pinned 0x0003C0BA
	~Rva0039B450Element();                                     ///< pinned 0x00048D42

private:
	unsigned int m_words[2];
};

class GlobalWeatherSystem : public SubsystemInterface, public BfmeBaseVUQ
{
public:
	GlobalWeatherSystem();

private:
	unsigned int m_at0C;
	unsigned int m_at10;
	unsigned int m_at14;
	HRBMD_Buffer m_buffer;                                     ///< +0x18
	BFMERetailAsciiString m_str;                               ///< +0x1C
	unsigned int m_at20;
	unsigned int m_at24;                                       ///< +0x24, untouched
	Rva0039B450Element m_array[5];                             ///< +0x28
};

// ??0GlobalWeatherSystem@@QAE@XZ
GlobalWeatherSystem::GlobalWeatherSystem()
	: m_at0C(0)
	, m_at10(1)
	, m_at14(0)
	, m_at20(0)
{
}
