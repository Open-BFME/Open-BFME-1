// ?attemptDamage@Object@@UAEXPAURva001D28F0Element@@@Z
// Candidate derived from reverse/attempts/0x001d4810.cpp.  This source keeps
// the dispatch class declaration-only so no synthetic vtable is emitted.

#define _STLP_NO_EXCEPTIONS 1

extern const float BfmeZeroRange;

struct Rva001D28F0Element
{
	unsigned char m_beforeDelay[0x24];
	float m_delay;
	unsigned char m_afterDelay[0x34];
};

class ObjectDamageFallback
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void dispatch(Rva001D28F0Element *damageInfo);
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type>
void __cdecl BfmeElementConstruct(Type *destination, const Type &value);

template <class Type, class Allocator = allocator<Type> >
class vector
{
public:
	void appendAtEnd(const Type &value, const __false_type &tag);

protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
__forceinline void vector<Type, Allocator>::appendAtEnd(
	const Type &value, const __false_type &tag)
{
	if (_M_finish != _M_end_of_storage)
	{
		BfmeElementConstruct(_M_finish, value);
		++_M_finish;
	}
	else
	{
		_M_insert_overflow(_M_finish, value, tag, 1, true);
	}
}
}

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void attemptDamage(Rva001D28F0Element *damageInfo);
	virtual void forwardDamage(Rva001D28F0Element *damageInfo) = 0;

private:
	unsigned char m_beforeStatusSign[0x94];
	signed char m_statusSign;
	unsigned char m_beforePendingDamage[0x34c - 0x99];
	_STL::vector<Rva001D28F0Element> m_pendingDamage;
};

void Object::attemptDamage(Rva001D28F0Element *damageInfo)
{
	if ((m_statusSign & 0x80) == 0)
		goto statusReady;
	damageInfo->m_delay = 1.0f;

statusReady:
	if (damageInfo->m_delay > BfmeZeroRange)
	{
		_STL::__false_type tag;
		m_pendingDamage.appendAtEnd(*damageInfo, tag);
		return;
	}

	forwardDamage(damageInfo);
}
