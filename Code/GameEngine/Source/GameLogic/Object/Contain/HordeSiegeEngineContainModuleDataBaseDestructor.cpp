// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: HordeSiegeEngineContainModuleDataBase's destructor, retail
// 0x0022B030, 132 bytes. The body carried only a machine byte-dump row; the
// symbols.csv pin names it.
//
// Three members and a base, in the usual reverse order: the member at +0x20C,
// the list at +0x174, the AsciiString at +0x170 and then HordeContainModuleData
// itself. There is no vptr store at the top and no restore at the end, which is
// what __declspec(novtable) on this class gives -- the same shape the other
// ModuleData destructors in the ledger have.
//
// The list is STLport's: its destructor clears out of line and then hands the
// sentinel node back to the pool, sixteen bytes of it, which is what an
// eight-byte element makes a node.

namespace _STL
{

template <class _Tp> class allocator
{
};

template <bool __threads, int __inst> class __node_alloc
{
public:
	static void _M_deallocate(void *block, unsigned int bytes);
};

template <class _Tp, class _Alloc = allocator<_Tp> > class _List_base
{
public:
	~_List_base()
	{
		clear();

		if (m_bfmeNode)
			__node_alloc<true, 0>::_M_deallocate(m_bfmeNode, 16);
	}

	void clear();						// ILT 0x00036048

private:
	void *m_bfmeNode;
};

}

struct Gen_t_0022b000_p8cd
{
	char m_bfmeBody[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();						// retail 0x00887940

private:
	char *m_bfmeData;
};

class HordeSiegeEngineContainModuleDataMemberA
{
public:
	~HordeSiegeEngineContainModuleDataMemberA();		// ILT 0x0001A401

private:
	char m_bfmePad[4];
};

class HordeContainModuleData
{
public:
	virtual ~HordeContainModuleData();			// ILT 0x000376E1

private:
	char m_bfmePad[0x170 - 0x04];
};

class __declspec(novtable) HordeSiegeEngineContainModuleDataBase
	: public HordeContainModuleData
{
public:
	virtual ~HordeSiegeEngineContainModuleDataBase();

private:
	AsciiString m_bfmeName;					// +0x170
	_STL::_List_base<Gen_t_0022b000_p8cd> m_bfmeEntries;	// +0x174
	char m_bfmePad178[0x20C - 0x178];
	HordeSiegeEngineContainModuleDataMemberA m_bfmeTail;	// +0x20C
};

// ??1HordeSiegeEngineContainModuleDataBase@@UAE@XZ
HordeSiegeEngineContainModuleDataBase::~HordeSiegeEngineContainModuleDataBase()
{
}
