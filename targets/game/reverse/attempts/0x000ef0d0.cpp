// ?d_000ef0d0@@YAXXZ
// partial score=0.96 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef UnsignedInt TeamID;
typedef UnsignedInt TeamPrototypeID;

class Snapshot
{
public:
	virtual void crc(void);
	virtual void xfer(void *);
	virtual void loadPostProcess(void);
};

class SubsystemInterface
{
public:
	virtual void init(void);
	virtual void reset(void);
	virtual void update(void);

private:
	void *m_name;
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool isSaving();
	virtual void slot03();
	virtual Bool isDoingCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void xferTeamID(UnsignedInt *);
	virtual void xferInt(Int *);
	virtual void xferUnsignedShort(UnsignedShort *);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *);
};

struct BfmeFormattedText
{
	char *m_text;
	int m_tag;
};

union TeamFactoryXferLocal
{
	XferVersion version;
	BfmeFormattedText error;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(
	BfmeFormattedText *, int, const char *, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);

class TeamPrototype
{
public:
	TeamPrototypeID getID() const
	{
		return *(const TeamPrototypeID *)((const char *)this + 0x0c);
	}
};

struct BfmeQ1107
{
	char m_pad[0x0c];
};

class BfmeW1107
{
public:
	BfmeQ1107 *bfmeGo1107A(int);
};

struct BfmeRbNode
{
	char m_pad[8];
	BfmeRbNode *m_left;
	char m_pad1[0x0c];
	TeamPrototype *m_value;
};

namespace _STL
{
struct _Rb_tree_node_base;
template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}

struct BfmeTeamPrototypeIterator
{
	BfmeRbNode *m_node;

	TeamPrototype *operator*() const
	{
		return m_node->m_value;
	}

	bool operator!=(const BfmeTeamPrototypeIterator &other) const
	{
		return m_node != other.m_node;
	}

	BfmeTeamPrototypeIterator &operator++()
	{
		m_node = (BfmeRbNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)m_node);
		return *this;
	}
};

struct BfmeTeamPrototypeMap
{
	BfmeRbNode *m_header;
	unsigned int m_size;
	unsigned int m_compare;

	unsigned int size() const
	{
		return m_size;
	}

	BfmeTeamPrototypeIterator begin() const
	{
		BfmeTeamPrototypeIterator result = { m_header->m_left };
		return result;
	}

	BfmeTeamPrototypeIterator end() const
	{
		BfmeTeamPrototypeIterator result = { m_header };
		return result;
	}
};

class TeamFactory : public Snapshot
{
protected:
	virtual void xfer(Xfer *);

private:
	BfmeTeamPrototypeMap m_prototypes;
	TeamPrototypeID m_uniqueTeamPrototypeID;
	TeamID m_uniqueTeamID;
};

void TeamFactory::xfer(Xfer *xfer)
{
	if (xfer->isDoingCRC())
		return;

	TeamFactoryXferLocal local;
	local.version.m_version = 1;
	local.version.m_currentVersion = 1;
	xfer->xferVersion(&local.version);
	xfer->xferTeamID(&m_uniqueTeamID);

	UnsignedShort prototypeCount = m_prototypes.size();
	xfer->xferUnsignedShort(&prototypeCount);
	if (prototypeCount != m_prototypes.size())
	{
		bfmeFormatText(&local.error, 5, 0);
		_CxxThrowException(&local.error, (void *)0x011DFE5C);
	}

	TeamPrototypeID teamPrototypeID;
	TeamPrototype *teamPrototype;
	AsciiString prototypeName;
	if (xfer->isSaving())
	{
		for (BfmeTeamPrototypeIterator it = m_prototypes.begin(); it != m_prototypes.end(); ++it)
		{
			teamPrototype = *it;
			teamPrototypeID = teamPrototype->getID();
			xfer->xferTeamID(&teamPrototypeID);
			xfer->xferSnapshot((Snapshot *)teamPrototype);
		}
	}
	else
	{
		for (UnsignedShort i = 0; i < prototypeCount; ++i)
		{
			xfer->xferTeamID(&teamPrototypeID);
			teamPrototype = (TeamPrototype *)((BfmeW1107 *)((char *)this - 8))->bfmeGo1107A(teamPrototypeID);
			if (teamPrototype == 0)
			{
				BfmeFormattedText error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (void *)0x011DFE5C);
			}
			xfer->xferSnapshot((Snapshot *)teamPrototype);
		}
	}
}
