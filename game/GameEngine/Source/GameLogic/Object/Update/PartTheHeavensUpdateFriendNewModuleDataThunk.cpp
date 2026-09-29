// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PartTheHeavensUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

struct Rva0006AA90Element;

class Rva0006AA90Vector
{
public:
	Rva0006AA90Vector()
	{
		m_start = 0;
		m_finish = 0;
		m_end = 0;
	}

	Rva0006AA90Element *end() const { return m_finish; }

	Rva0006AA90Element *m_start;
	Rva0006AA90Element *volatile m_finish;
	Rva0006AA90Element *m_end;
	unsigned char m_padding;
	unsigned char m_flag;
	unsigned char m_reserved[2];
};

class Rva0006A3C0
{
public:
	Rva0006A3C0()
		: m_field0( 0 )
		, m_field4( 0 )
		, m_points()
	{
	}

	~Rva0006A3C0();

	int m_field0;
	int m_field4;
	Rva0006AA90Vector m_points;
};

class Rva0006AB10Curve
{
public:
	void set(float time, float value, int inTangent, int outTangent);

	int m_field0;
	int m_field4;
	Rva0006AA90Vector m_points;
	Rva0006AA90Element *m_current;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	~BFMERetailAsciiString();

	char *m_data;
};

class Rva000299E10String
{
public:
	Rva000299E10String() {}
	~Rva000299E10String() {}

	BFMERetailAsciiString m_name;
};

class Rva000299E10Record
{
public:
	Rva000299E10Record()
		: m_current( m_curve.m_points.end() )
	{
		m_tail3 = 0;
		m_tail2 = 0;
		m_tail1 = 0;
		m_tail0 = 0;
	}

	__forceinline ~Rva000299E10Record() {}

	Rva0006A3C0 m_curve;
	Rva0006AA90Element *m_current;
	int m_tail0;
	int m_tail1;
	int m_tail2;
	int m_tail3;
};

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
};

class PartTheHeavensUpdateModuleData : public Snapshot
{
public:
	PartTheHeavensUpdateModuleData();
	virtual ~PartTheHeavensUpdateModuleData();

private:
	int m_unnamed0;
	Rva000299E10String m_name;
	int m_opaque0c;
	Rva000299E10Record m_record0;
	Rva000299E10Record m_record1;
	Rva000299E10Record m_record2;
};

PartTheHeavensUpdateModuleData::PartTheHeavensUpdateModuleData()
	: m_opaque0c(0)
{
	((Rva0006AB10Curve *)&m_record0.m_curve)->set(0.0f, 0.0f, 0, 0);
	((Rva0006AB10Curve *)&m_record1.m_curve)->set(0.0f, 1.0f, 0, 0);
	((Rva0006AB10Curve *)&m_record2.m_curve)->set(0.0f, 0.0f, 0, 0);
}

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl PartTheHeavensUpdateFieldParse(MultiIniFieldParse &parse);

class PartTheHeavensUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@PartTheHeavensUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PartTheHeavensUpdate::friend_newModuleData(INI *ini)
{
	PartTheHeavensUpdateModuleData *data = new PartTheHeavensUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &PartTheHeavensUpdateFieldParse);
	return (ModuleData *)data;
}
