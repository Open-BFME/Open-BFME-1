// cl: /DNDEBUG /MD /EHsc

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
		AnimalAIUpdateModuleDataBaseShim *base = (AnimalAIUpdateModuleDataBaseShim *)this;
		base->construct();
	}
	virtual ~SupplyTruckAIUpdateModuleDataBase();

private:
	unsigned char m_pad[0x60];
};

extern "C" char WorkerAIUpdateModuleData_vtbl;

class __declspec(novtable) WorkerAIUpdateModuleData
	: public SupplyTruckAIUpdateModuleDataBase
{
public:
	WorkerAIUpdateModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x2c];
	AudioEventRTS m_suppliesDepletedVoice;
};

// ??0WorkerAIUpdateModuleData@@QAE@XZ
WorkerAIUpdateModuleData::WorkerAIUpdateModuleData()
{
	unsigned int zero = 0;
	unsigned int one = 1;
	*(reinterpret_cast<char *volatile *>(this)) = &WorkerAIUpdateModuleData_vtbl;
	m_suppliesDepletedVoice.init(AsciiString::TheEmptyString, (ObjectID)zero);
	*(unsigned int *)((char *)this + 0x88) = one;
	*(unsigned int *)((char *)this + 0x8c) = one;
	*(unsigned int *)((char *)this + 0x64) = zero;
	*(unsigned int *)((char *)this + 0x68) = zero;
	*(unsigned int *)((char *)this + 0x6c) = zero;
	*(unsigned int *)((char *)this + 0x70) = zero;
	*(unsigned int *)((char *)this + 0x74) = zero;
	*(unsigned int *)((char *)this + 0x78) = zero;
	*((unsigned char *)this + 0x80) = (unsigned char)zero;
	*(unsigned int *)((char *)this + 0x7c) = 0x42c80000;
	*(unsigned int *)((char *)this + 0x84) = 0x42480000;
}
