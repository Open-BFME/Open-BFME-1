// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean-C++ SupplyTruckAIUpdateModuleData constructor.

class AnimalAIUpdateModuleDataBaseShim
{
public:
	void construct();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	static AsciiString TheEmptyString;
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	void init(const AsciiString &, ObjectID);

private:
	void *m_vtable;
	unsigned char m_data[0x6c];
};

class __declspec(novtable) SupplyTruckAIUpdateModuleDataBase
{
public:
	SupplyTruckAIUpdateModuleDataBase()
	{
		AnimalAIUpdateModuleDataBaseShim *base =
			(AnimalAIUpdateModuleDataBaseShim *)this;
		base->construct();
	}
	virtual ~SupplyTruckAIUpdateModuleDataBase();

private:
	unsigned char m_pad[0x60];
};

extern "C" char SupplyTruckAIUpdateModuleData_vtbl;

class __declspec(novtable) SupplyTruckAIUpdateModuleData
	: public SupplyTruckAIUpdateModuleDataBase
{
public:
	SupplyTruckAIUpdateModuleData();
	virtual ~SupplyTruckAIUpdateModuleData();

private:
	unsigned char m_pad[0x20];
	AudioEventRTS m_suppliesDepletedVoice;
};

// ??0SupplyTruckAIUpdateModuleData@@QAE@XZ
SupplyTruckAIUpdateModuleData::SupplyTruckAIUpdateModuleData()
{
	unsigned int zero = 0;
	unsigned int one = 1;
	*(reinterpret_cast<char *volatile *>(this)) = &SupplyTruckAIUpdateModuleData_vtbl;
	m_suppliesDepletedVoice.init(AsciiString::TheEmptyString, (ObjectID)zero);
	*(unsigned int *)((char *)this + 0x7c) = one;
	*(unsigned int *)((char *)this + 0x80) = one;
	*(unsigned int *)((char *)this + 0x64) = zero;
	*(unsigned int *)((char *)this + 0x68) = zero;
	*(unsigned int *)((char *)this + 0x6c) = zero;
	*((unsigned char *)this + 0x74) = (unsigned char)zero;
	*(unsigned int *)((char *)this + 0x70) = 0x42c80000;
	*(unsigned int *)((char *)this + 0x78) = 0x42480000;
}
