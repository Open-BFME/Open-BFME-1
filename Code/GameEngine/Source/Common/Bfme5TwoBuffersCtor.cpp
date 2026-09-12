// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1

void *bfmeAlloc1134(unsigned int bytes);

#include "Common/STLTypedefs.h"
#include <map>

struct BfmeSplitValue
{
	~BfmeSplitValue();
	unsigned int m_bfmeFirst;
	unsigned int m_bfmeSecond;
	char m_bfmePadding[0x18];
	unsigned int m_bfmeState;
	char m_bfmeTail[0x1C];
};

struct BfmeSplitNode
{
	BfmeSplitNode *m_bfmeRoot;
	BfmeSplitNode *m_bfmeLeft;
	BfmeSplitNode *m_bfmeParent;
	BfmeSplitNode *m_bfmeRight;
	BfmeSplitValue m_bfmeValue;
};

void Open2SendNotice51B0C0(int value);

struct Gen_005878D0FirstValue
{
	unsigned int m_bfmeValue;
};

typedef _STL::map<int, Gen_005878D0FirstValue> Gen_00587D40FirstMap;
typedef _STL::map<int, BfmeSplitValue> Gen_00587D40SecondMap;

class BfmeBase1134
{
public:
	BfmeBase1134(void);
	virtual ~BfmeBase1134(void);

private:
	int m_bfme04;
};

struct BfmeBuffer1134
{
	BfmeBuffer1134(unsigned int bytes)
	{
		m_bfmeData = 0;
		m_bfmeData = (char *)bfmeAlloc1134(bytes);
		m_bfmeLength = 0;
		m_bfmeData[0] = 0;
		*(int *)(m_bfmeData + 4) = 0;
		*(char **)(m_bfmeData + 8) = m_bfmeData;
		*(char **)(m_bfmeData + 12) = m_bfmeData;
	}
	~BfmeBuffer1134(void);

	char *m_bfmeData;
	int m_bfmeLength;
};

class Gen_00587D40 : public BfmeBase1134
{
public:
	Gen_00587D40(void);
	virtual ~Gen_00587D40(void);
	void rva005878d0(BfmeSplitNode *node);

private:
	int m_bfme08;
	char m_bfme0C;
	char m_bfme0D;
	char m_bfme0E[10];
	BfmeBuffer1134 m_bfmeFirst;
	int m_bfme20;
	BfmeBuffer1134 m_bfmeSecond;
};

// ??0Gen_00587D40@@QAE@XZ
Gen_00587D40::Gen_00587D40(void) :
	m_bfme08(0),
	m_bfme0C(0),
	m_bfme0D(0),
	m_bfmeFirst(0x18),
	m_bfmeSecond(0x50)
{
}

// ?rva005878d0@Gen_00587D40@@QAEXPAUBfmeSplitNode@@@Z
void Gen_00587D40::rva005878d0(BfmeSplitNode *node)
{
	Gen_00587D40SecondMap *second =
		reinterpret_cast<Gen_00587D40SecondMap *>(&m_bfmeSecond);
	if (node == reinterpret_cast<BfmeSplitNode *>(m_bfmeSecond.m_bfmeData))
		return;

	unsigned int firstValue = node->m_bfmeValue.m_bfmeFirst;
	if (node->m_bfmeValue.m_bfmeState == 3)
		return;

	Gen_00587D40FirstMap *first =
		reinterpret_cast<Gen_00587D40FirstMap *>(&m_bfmeFirst);
	Gen_00587D40FirstMap::iterator found = first->find(node->m_bfmeValue.m_bfmeSecond);

	if (found != first->end() && found->second.m_bfmeValue == firstValue)
		first->erase(found);
	if (node->m_bfmeValue.m_bfmeState != 0)
	{
		Open2SendNotice51B0C0(firstValue);
		node->m_bfmeValue.m_bfmeState = 3;
	}
	else
	{
		Gen_00587D40SecondMap::iterator secondIterator =
			*reinterpret_cast<Gen_00587D40SecondMap::iterator *>(&node);
		second->erase(secondIterator);
	}
}
