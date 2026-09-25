// ?d_002475a0@@YAXXZ
// partial score=0.43 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include <map>
#include <set>
#include <vector>

// Retail 0x002475A0 is reached by HordeContain's base-transfer ILT at
// 0x00024BDB.  The matched AODHordeContain transfer caller proves that role,
// but no source evidence proves the canonical private HordeContain field
// names.  Keep the owner address-derived while retaining the witnessed
// STLport/Xfer layout and the callee spellings printed by tools/callees.py.

typedef bool Bool;
typedef unsigned int UnsignedInt;

struct Rva002475A0XferVersion
{
	Rva002475A0XferVersion() {}
	Rva002475A0XferVersion(unsigned char version, unsigned char currentVersion)
		: m_version(version), m_currentVersion(currentVersion) {}

	unsigned char m_version;
	unsigned char m_currentVersion;
};

class Rva002475A0Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading();
	virtual void slot02();
	virtual void slot03();
	virtual Bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Rva002475A0Xfer &xferVersion(Rva002475A0XferVersion *version);
	virtual void slot11();
	virtual void slot12();
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
	virtual Rva002475A0Xfer &xferSnapshot(void *value);
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual Rva002475A0Xfer &xferUnsignedInt(UnsignedInt *value);
	virtual Rva002475A0Xfer &xferInt(int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual Rva002475A0Xfer &xferBool(Bool *value);
};

static __forceinline void rva002475a0XferVersion(
	Rva002475A0Xfer *xfer, const Rva002475A0XferVersion &version)
{
	xfer->xferVersion((Rva002475A0XferVersion *)&version);
}

extern void j_0000c9b4();
extern void j_0001f91f();
extern void j_00026dd7();
extern void j_000353c8();
extern void j_00036ac5();
extern void j_0003d37a();
extern void j_00047ba9();
extern void j_000499f9();
extern void *__cdecl operator new(unsigned int size);

// The owning class's destructor witnesses these STLport instantiations at the
// same offsets.  The 4-byte tree payload and the 28-byte vector payload keep
// the address-derived/generated type spellings of their retail helpers.
struct Gen_t_000ef440_k4
{
	int value;
};

bool operator==(const Gen_t_000ef440_k4 &left,
	const Gen_t_000ef440_k4 &right)
{
	return left.value == right.value;
}

bool operator<(const Gen_t_000ef440_k4 &left,
	const Gen_t_000ef440_k4 &right)
{
	return left.value < right.value;
}

struct Gen_t_00223550_p4pod
{
	int a[1];
};

bool operator==(const Gen_t_00223550_p4pod &left,
	const Gen_t_00223550_p4pod &right)
{
	return left.a[0] == right.a[0];
}

bool operator<(const Gen_t_00223550_p4pod &left,
	const Gen_t_00223550_p4pod &right)
{
	return left.a[0] < right.a[0];
}

struct Rva00244A80Element
{
	int m_head;
	int m_snapshot0;
	int m_snapshot1;
	int m_snapshot2;
	Bool m_flag;
	unsigned char m_padding[3];
	int m_tail0;
	int m_tail1;
};

template <class Type>
class Rva002475A0PublicVector : public _STL::vector<Type>
{
public:
	using _STL::vector<Type>::_M_start;
	using _STL::vector<Type>::_M_finish;
	using _STL::vector<Type>::_M_end_of_storage;
	using _STL::vector<Type>::_M_fill_insert;
	using _STL::vector<Type>::_M_insert_overflow;
};

class Rva002475A0BaseCall
{
public:
	void xfer(Rva002475A0Xfer *xfer);
};

class Rva002475A0FieldCall
{
public:
	void xfer(Rva002475A0Xfer *xfer);
};

class Rva002475A0MapCall
{
};

class Rva002475A0SetCall
{
};

class Rva002475A0VectorCall
{
};

template <class Type>
class Rva002475A0Vector4
{
public:
	void push_back(const Type &value)
	{
		if (_M_finish != _M_end_of_storage)
		{
			if (_M_finish != 0)
				*_M_finish = value;
			++_M_finish;
		}
		else
		{
			typedef void (Rva002475A0VectorCall::*Call)(
				Type *, const Type &, const _STL::__false_type &,
				UnsignedInt, Bool);
			union { void (*raw)(); Call member; } vectorCall;
			vectorCall.raw = j_00047ba9;
			(((Rva002475A0VectorCall *)this)->*vectorCall.member)(
				_M_finish, value,
				reinterpret_cast<const _STL::__false_type &>(value), 1, true);
		}
	}

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

#pragma comment(linker, "/alternatename:?xfer@Rva002475A0BaseCall@@QAEXPAVRva002475A0Xfer@@@Z=?j_0003d37a@@YAXXZ")
#pragma comment(linker, "/alternatename:?xfer@Rva002475A0FieldCall@@QAEXPAVRva002475A0Xfer@@@Z=?j_00026dd7@@YAXXZ")
#pragma comment(linker, "/alternatename:?_M_fill_insert@?$vector@URva00244A80Element@@V?$allocator@URva00244A80Element@@@_STL@@@_STL@@QAEXPAURva00244A80Element@@IABU3@@Z=?j_00036ac5@@YAXXZ")

static __forceinline void rva002475a0ObjectID(
	Rva002475A0Xfer *xfer, UnsignedInt *value)
{
	typedef void (__cdecl *Call)(Rva002475A0Xfer *, UnsignedInt *);
	((Call)j_0000c9b4)(xfer, value);
}

// ?xfer@Rva002475A0HordeContain@@QAEXPAVRva002475A0Xfer@@@Z
class Rva002475A0HordeContain
{
public:
	void xfer(Rva002475A0Xfer *xfer);

private:
	unsigned char m_head[0xe8];
	Bool m_flagE8;
	Bool m_flagE9;
	unsigned char m_paddingEA[0x2a];
	_STL::set<Gen_t_000ef440_k4> m_set;
	_STL::map<int, Gen_t_00223550_p4pod> m_map;
	unsigned char m_padding12c[0x0c];
	_STL::list<int> m_list;
	unsigned char m_padding13c[0x78];
	UnsignedInt m_objectID1b4;
	int m_value1b8;
	UnsignedInt m_objectID1bc;
	Rva002475A0Vector4<int> m_vector4;
	int m_value1cc;
	int m_value1d0;
	int m_value1d4;
	Rva002475A0PublicVector<Rva00244A80Element> m_vector28;
	UnsignedInt m_objectID1e4;
	UnsignedInt m_value1e8;
	UnsignedInt m_value1ec;
	Bool m_flag1f0;
	unsigned char m_padding1f1[7];
	UnsignedInt m_objectID1f8;
	Bool m_flag1fc;
	Bool m_flag1fd;
	Bool m_flag1fe;
	unsigned char m_padding1ff;
	int m_value200;
	Bool m_flag204;
	Bool m_flag205;
	unsigned char m_padding206[2];
	UnsignedInt m_objectID208;
	int m_value20c;
	unsigned char m_padding210[4];
	unsigned char m_snapshot214[0x0c];
	Bool m_flag220;
	Bool m_flag221;
};

#pragma comment(linker, "/alternatename:?insert_unique@?$_Rb_tree@UGen_t_000ef440_k4@@U1@U?$_Identity@UGen_t_000ef440_k4@@@_STL@@U?$less@UGen_t_000ef440_k4@@@3@V?$allocator@UGen_t_000ef440_k4@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@UGen_t_000ef440_k4@@U?$_Nonconst_traits@UGen_t_000ef440_k4@@@_STL@@@_STL@@_N@2@ABUGen_t_000ef440_k4@@@Z=?j_000499f9@@YAXXZ")

void Rva002475A0HordeContain::xfer(Rva002475A0Xfer *xfer)
{
	((Rva002475A0BaseCall *)this)->xfer(xfer);
	if (xfer->isLightCRC())
		return;

	const Rva002475A0XferVersion &version = Rva002475A0XferVersion(1, 3);
	rva002475a0XferVersion(xfer, version);
	xfer->xferBool(&m_flagE8);
	xfer->xferUnsignedInt((UnsignedInt *)((unsigned char *)this + 0x140));
	xfer->xferBool(&m_flagE9);
	xfer->xferBool(&m_flag1fe);

	int listCount = m_list.size();
	xfer->xferInt(&listCount);
	if (xfer->isLoading())
	{
		int listValue = 0;
		for (int i = 0; i < listCount; ++i)
		{
			xfer->xferInt(&listValue);
			m_list.push_back(listValue);
		}
	}
	else
	{
		for (_STL::list<int>::iterator it = m_list.begin();
			it != m_list.end(); ++it)
		{
			int listValue = *it;
			xfer->xferInt(&listValue);
		}
	}

	int mapCount = m_map.size();
	xfer->xferInt(&mapCount);
	if (xfer->isLoading())
	{
		UnsignedInt key = 0;
		int value = 0;
		for (int i = 0; i < mapCount; ++i)
		{
			rva002475a0ObjectID(xfer, &key);
			xfer->xferInt(&value);
			typedef void **(Rva002475A0MapCall::*Call)(void **);
			union { void (*raw)(); Call member; } mapCall;
			mapCall.raw = j_0001f91f;
			void **slot = (((Rva002475A0MapCall *)&m_map)->*mapCall.member)(
				(void **)&key);
			*(int *)slot = value;
		}
	}
	else
	{
		for (_STL::map<int, Gen_t_00223550_p4pod>::iterator it =
			m_map.begin(); it != m_map.end(); ++it)
		{
			UnsignedInt key = (UnsignedInt)it->first;
			int value = it->second.a[0];
			rva002475a0ObjectID(xfer, &key);
			xfer->xferInt(&value);
		}
	}

	((Rva002475A0FieldCall *)((unsigned char *)this + 0xec))->xfer(xfer);

	int setCount = m_set.size();
	xfer->xferInt(&setCount);
	if (xfer->isLoading())
	{
		Gen_t_000ef440_k4 value;
		for (int i = 0; i < setCount; ++i)
		{
			rva002475a0ObjectID(xfer, (UnsignedInt *)&value.value);
			m_set.insert(value);
		}
	}
	else
	{
		for (_STL::set<Gen_t_000ef440_k4>::iterator it =
			m_set.begin(); it != m_set.end(); ++it)
		{
			int value = it->value;
			rva002475a0ObjectID(xfer, (UnsignedInt *)&value);
		}
	}

	if (version.m_currentVersion < 3)
	{
		Rva002475A0Vector4<int> *vector4 = &m_vector4;
		int vectorCount = (int)(vector4->_M_finish - vector4->_M_start);
		xfer->xferInt(&vectorCount);
		if (xfer->isLoading())
		{
			for (int i = 0; i < vectorCount; ++i)
			{
				void *record = operator new(8);
				if (record != 0)
				{
					((UnsignedInt *)record)[0] = 0;
					((UnsignedInt *)record)[1] = (UnsignedInt)-1;
				}
				Rva002475A0XferVersion oldVersion;
				oldVersion.m_version = 1;
				oldVersion.m_currentVersion = 1;
				xfer->xferVersion(&oldVersion);
				typedef void (__cdecl *HandOver)(Rva002475A0Xfer *, void *);
				((HandOver)j_000353c8)(xfer, record);
				xfer->xferInt((int *)((unsigned char *)record + 4));

				vector4->push_back((int)record);
			}
		}
		else
		{
			for (int i = 0; i < vectorCount; ++i)
			{
				void *record = (void *)vector4->_M_start[i];
				Rva002475A0XferVersion oldVersion;
				oldVersion.m_version = 1;
				oldVersion.m_currentVersion = 1;
				xfer->xferVersion(&oldVersion);
				typedef void (__cdecl *HandOver)(Rva002475A0Xfer *, void *);
				((HandOver)j_000353c8)(xfer, record);
				xfer->xferInt((int *)((unsigned char *)record + 4));
			}
		}
	}

	xfer->xferBool(&m_flag1fc);
	xfer->xferBool(&m_flag1fd);
	int vector28Count = (int)m_vector28.size();
	xfer->xferInt(&vector28Count);
	if (xfer->isLoading())
	{
		Rva00244A80Element value;
		value.m_head = 0;
		value.m_snapshot0 = 0;
		value.m_snapshot1 = 0;
		value.m_snapshot2 = 0;
		value.m_flag = true;
		value.m_tail0 = 0;
		value.m_tail1 = 0;
		int oldCount = (int)m_vector28.size();
		if (vector28Count < oldCount)
			m_vector28._M_finish = m_vector28._M_start + vector28Count;
		else if (vector28Count > oldCount)
		{
			m_vector28._M_fill_insert(m_vector28._M_finish,
				(unsigned)(vector28Count - oldCount), value);
		}
	}
	for (int i = 0; i < vector28Count; ++i)
	{
		Rva00244A80Element value;
		value.m_head = 0;
		value.m_snapshot0 = 0;
		value.m_snapshot1 = 0;
		value.m_snapshot2 = 0;
		value.m_flag = true;
		value.m_tail0 = 0;
		value.m_tail1 = 0;
		if (!xfer->isLoading())
			value = m_vector28.begin()[i];
		xfer->xferSnapshot(&value.m_snapshot0);
		xfer->xferBool(&value.m_flag);
		if (xfer->isLoading())
			m_vector28.begin()[i] = value;
	}

	rva002475a0ObjectID(xfer, &m_objectID1e4);
	xfer->xferUnsignedInt(&m_value1e8);
	rva002475a0ObjectID(xfer, &m_objectID1b4);
	xfer->xferInt((int *)((unsigned char *)this + 0x1b8));
	rva002475a0ObjectID(xfer, &m_objectID1bc);
	xfer->xferInt(&m_value20c);
	xfer->xferUnsignedInt((UnsignedInt *)((unsigned char *)this + 0x1cc));
	xfer->xferInt(&m_value1d0);
	xfer->xferInt(&m_value1d4);
	xfer->xferSnapshot(&m_snapshot214).xferBool(&m_flag220);
	xfer->xferUnsignedInt(&m_value1ec);
	xfer->xferBool(&m_flag1f0);
	xfer->xferUnsignedInt(&m_value1ec);
	rva002475a0ObjectID(xfer, &m_objectID1f8);
	xfer->xferInt(&m_value200);
	xfer->xferBool(&m_flag204);
	xfer->xferBool(&m_flag205);
	rva002475a0ObjectID(xfer, &m_objectID208);
	if (version.m_currentVersion > 1)
		xfer->xferBool(&m_flag221);
}
