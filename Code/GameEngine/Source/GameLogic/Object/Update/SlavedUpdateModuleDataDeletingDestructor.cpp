// cl: /DNDEBUG /MD /EHsc
//
// Retail's SlavedUpdateModuleData vtable at 0x0108E730 names this scalar
// deleting destructor in slot zero. Its call target is the independently
// matched destructor body at 0x00126980.

class AsciiString
{
	char *m_str;
public:
	~AsciiString();
};

class UpdateModuleData
{
public:
	virtual ~UpdateModuleData() {}
	unsigned int m_04;
};

class SlavedUpdateModuleData : public UpdateModuleData
{
public:
	virtual ~SlavedUpdateModuleData();

private:
	int m_values[16];
	AsciiString m_weldingSysName;
	AsciiString m_weldingFXBone;
	unsigned char m_stayOnSameLayerAsMaster;
};

SlavedUpdateModuleData::~SlavedUpdateModuleData()
{
}
