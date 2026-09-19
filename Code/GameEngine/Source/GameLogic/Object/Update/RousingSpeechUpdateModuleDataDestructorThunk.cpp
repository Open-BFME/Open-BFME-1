// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RousingSpeechUpdateModuleData dtor.

class RousingSpeechUpdateModuleDataMemberA
{
public:
	~RousingSpeechUpdateModuleDataMemberA();
private:
	unsigned char m_pad[0x10];
};

class RousingSpeechUpdateModuleDataMemberB
{
public:
	~RousingSpeechUpdateModuleDataMemberB();
private:
	unsigned char m_pad[4];
};

class RousingSpeechUpdateModuleDataBase
{
public:
	virtual ~RousingSpeechUpdateModuleDataBase();
private:
	unsigned char m_pad[0x26c];
};

class __declspec(novtable) RousingSpeechUpdateModuleData : public RousingSpeechUpdateModuleDataBase
{
public:
	virtual ~RousingSpeechUpdateModuleData();
private:
	RousingSpeechUpdateModuleDataMemberA m_a;
	RousingSpeechUpdateModuleDataMemberB m_b;
};

// ??1RousingSpeechUpdateModuleData@@UAE@XZ
RousingSpeechUpdateModuleData::~RousingSpeechUpdateModuleData()
{
}
