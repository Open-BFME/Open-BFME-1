// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
//
// The pin at ILT 0x0003913F identifies the jump as the OCL upgrades vector
// insertion entry.  The existing OCLUpgradesVectorInsert.cpp owns the 305-byte
// implementation at 0x00262FE0, so this TU emits only the compiler tail thunk.

struct OCLSpecialPowerModuleData
{
	struct Upgrades
	{
		int m_first;
		int m_second;
	};
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

template <class Type, class Allocator>
  class vector
  {
  protected:
      void _M_insert_overflow(Type *, const Type &, const __false_type &, unsigned int, bool);
  };
}

class Rva0003913FVectorThunk
	: public _STL::vector<OCLSpecialPowerModuleData::Upgrades,
		_STL::allocator<OCLSpecialPowerModuleData::Upgrades> >
{
  public:
      void invoke(OCLSpecialPowerModuleData::Upgrades *position,
          const OCLSpecialPowerModuleData::Upgrades &value,
          const _STL::__false_type &tag, unsigned int fillLength, bool atEnd);
  };

  // ?j_0003913f@@YAXXZ
  void Rva0003913FVectorThunk::invoke(
      OCLSpecialPowerModuleData::Upgrades *position,
      const OCLSpecialPowerModuleData::Upgrades &value,
      const _STL::__false_type &tag, unsigned int fillLength, bool atEnd)
  {
      _M_insert_overflow(position, value, tag, fillLength, atEnd);
  }
