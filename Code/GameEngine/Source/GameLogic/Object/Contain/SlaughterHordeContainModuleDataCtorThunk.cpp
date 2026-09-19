// cl: /DNDEBUG /MD /EHsc

// A base constructed out of line, this class's vptr, an array, then three fields.
//
// ??_L spells the array out completely from its five arguments: base at +0x24C,
// eight elements, twenty-four bytes each, and the element's constructor and
// destructor. Eight times twenty-four lands exactly on +0x30C, where the three
// remaining fields begin.
//
// The base constructor takes no arguments and is called rather than inlined, so
// it is declared without a body; this class stores its own vptr, so it is not
// novtable.
class HordeSiegeEngineContainModuleData
{
public:
	HordeSiegeEngineContainModuleData();

	virtual ~HordeSiegeEngineContainModuleData();

private:
	unsigned char m_head[0x248];
};

class SlaughterEntry
{
public:
	SlaughterEntry();
	~SlaughterEntry();

private:
	unsigned char m_body[0x18];
};

class SlaughterHordeContainModuleData : public HordeSiegeEngineContainModuleData
{
public:
	SlaughterHordeContainModuleData();

private:
	SlaughterEntry m_entries[8];
	int m_30c;
	int m_310;
	bool m_314;
};

// ??0SlaughterHordeContainModuleData@@QAE@XZ
SlaughterHordeContainModuleData::SlaughterHordeContainModuleData()
{
	m_30c = 0;
	m_310 = 0;
	m_314 = false;
}
