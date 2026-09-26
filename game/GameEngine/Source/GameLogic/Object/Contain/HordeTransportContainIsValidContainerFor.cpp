// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME: HordeTransportContain::isValidContainerFor, retail 0x0024BD70.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

typedef bool Bool;

class HordeTransportContainResult
{
};

class HordeTransportContainModuleData
{
public:
	unsigned char m_pad[0x168];
	int m_slotCapacity;
};

class HordeTransportContainInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual HordeTransportContainResult *getResult(void) = 0;
};

class Object
{
public:
	unsigned char m_pad[0x94];
	unsigned char m_status;
	unsigned char m_pad95[0x1fc - 0x95];
	HordeTransportContainInterface *m_contain;
};

class BfmeRva493A0Object;
class BfmeRva493A0Result;

class Rva002493A0
{
public:
	BfmeRva493A0Result *find2(BfmeRva493A0Object *object);
};

class HordeTransportContain
{
public:
	unsigned char m_pad04[0x14];
	_STL::list<int> m_memberList;

	HordeTransportContainModuleData *getModuleData(void) const
	{
		return *(HordeTransportContainModuleData **)((char *)this - 0x1c);
	}

	Bool preflight(Object *object, Bool checkCapacity) const;
	virtual Bool isValidContainerFor(const Object *object, Bool checkCapacity) const;
};

#pragma comment(linker, "/alternatename:?preflight@HordeTransportContain@@QBE_NPAVObject@@_N@Z=?j_000237b8@@YAXXZ")

// ?isValidContainerFor@HordeTransportContain@@UBE_NPBVObject@@_N@Z
Bool HordeTransportContain::isValidContainerFor(const Object *object,
	Bool checkCapacity) const
{
	if (!preflight((Object *)object, checkCapacity))
		return false;

	HordeTransportContainInterface *contain =
		((Object *)object)->m_contain;
	if (contain == 0)
	{
		if ((((Object *)object)->m_status & 0x20) == 0)
			goto failed;

	Bool found = ((Rva002493A0 *)((char *)this - 0x20))->find2(
		(BfmeRva493A0Object *)object) != 0;
	return found;
	}

	if (contain->getResult() == 0)
		goto failed;

	if (checkCapacity != true)
		goto success;

	if (m_memberList.size() >=
		(unsigned int)getModuleData()->m_slotCapacity)
		goto failed;

	goto success;

failed:
	return false;

success:
	return true;
}
