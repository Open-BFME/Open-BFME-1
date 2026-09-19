// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: UpgradeSoundSelectorClientBehaviorModuleData::parseSoundUpgrade.
// The field parser constructs one SoundUpgrade record and appends it to the
// module-data vector at +0x08.

class INI;

extern void j_0000e656();

inline void *__cdecl operator new(unsigned int, void *place)
{
	return place;
}

inline void __cdecl operator delete(void *, void *)
{
}

struct Rva00608FE0Element
{
	Rva00608FE0Element();
	Rva00608FE0Element(const Rva00608FE0Element &);
	~Rva00608FE0Element();

	void parse(INI *ini);

	unsigned char m_body[528];
};

#pragma comment(linker, "/alternatename:??0Rva00608FE0Element@@QAE@XZ=?j_0002a48c@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva00608FE0Element@@QAE@ABU0@@Z=?j_00042339@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00608FE0Element@@QAE@XZ=?j_00034158@@YAXXZ")
#pragma comment(linker, "/alternatename:?parse@Rva00608FE0Element@@QAEXPAVINI@@@Z=?j_00044210@@YAXXZ")

namespace _STL
{
struct __false_type
{
};

template <class Type>
__forceinline void _Construct(Type *place, const Type &value)
{
	new (place) Type(value);
}

template <class Type>
class allocator
{
};

template <class Type>
class sound_upgrade_vector
{
public:
	Type *m_start;
	Type *m_finish;
	Type *m_end_of_storage;

	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);
};

template <class Type, class Allocator>
class vector
{
public:
	__forceinline void push_back(const Type &value)
	{
		if (m_finish != m_end_of_storage)
		{
			new (m_finish) Type(value);
			++m_finish;
		}
		else
		{
			__false_type tag;
			_M_insert_overflow(m_finish, value, tag, 1, true);
		}
	}

	public:
	Type *m_start;
	Type *m_finish;
	Type *m_end_of_storage;
};
}

class UpgradeSoundSelectorClientBehaviorModuleData
{
public:
	static void __cdecl parseSoundUpgrade(INI *ini, void *instance,
		void *, const void *);

private:
	unsigned char m_pad[8];
	_STL::sound_upgrade_vector<Rva00608FE0Element> m_soundUpgrades;
};

// ?parseSoundUpgrade@UpgradeSoundSelectorClientBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
void __cdecl UpgradeSoundSelectorClientBehaviorModuleData::parseSoundUpgrade(
	INI *ini, void *instance, void *, const void *)
{
	UpgradeSoundSelectorClientBehaviorModuleData *self =
		(UpgradeSoundSelectorClientBehaviorModuleData *)instance;
	if (self == 0)
		return;

	Rva00608FE0Element value;
	value.parse(ini);
	_STL::sound_upgrade_vector<Rva00608FE0Element> *items =
		&self->m_soundUpgrades;
	if (items->m_finish != items->m_end_of_storage)
	{
		_STL::_Construct(items->m_finish, value);
		++items->m_finish;
	}
	else
	{
		// The existing 528-byte STLport overflow body is entered through its
		// ILT; keeping the call target explicit preserves retail's relocation.
		_STL::__false_type tag;
		items->_M_insert_overflow(items->m_finish, value, tag, 1, true);
	}
}
