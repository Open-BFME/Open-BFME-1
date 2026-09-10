// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME5: STLport vector<Coord3D>::_M_fill_insert, retail 0x000B7AF0,
// 310 bytes.  The real named caller is vector<Coord3D>::resize at 0x000B7C90;
// its insert branch reaches this body through the dedicated 0x00006B45 ILT.
// Keep this TU local: the neighboring resize body has a BFME by-value overload
// which the stock vector header cannot express.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Coord3D
{
	float x;
	float y;
	float z;
};

template <>
void _STL::vector<Coord3D, _STL::allocator<Coord3D> >::_M_fill_insert(
	Coord3D *position, unsigned int count, const Coord3D &value)
{
	if (count != 0)
	{
		if ((unsigned int)(this->_M_end_of_storage._M_data - this->_M_finish)
			>= count)
		{
			const volatile Coord3D *value_source = &value;
			Coord3D value_copy;
			value_copy.x = value_source->x;
			value_copy.y = value_source->y;
			value_copy.z = value_source->z;
			const unsigned int elements_after =
				(unsigned int)(this->_M_finish - position);
			Coord3D *old_finish = this->_M_finish;
			if (elements_after > count)
			{
				__uninitialized_copy(this->_M_finish - count,
					this->_M_finish, this->_M_finish, _IsPODType());
				this->_M_finish += count;
				__copy_backward_ptrs(position, old_finish - count,
					old_finish, _TrivialAss());
				_STLP_STD::fill(position, position + count, (const Coord3D &)value_copy);
			}
			else
			{
				uninitialized_fill_n(this->_M_finish,
					count - elements_after, value_copy);
				this->_M_finish += count - elements_after;
				__uninitialized_copy(position, old_finish,
					this->_M_finish, _IsPODType());
				this->_M_finish += elements_after;
				_STLP_STD::fill(position, old_finish, (const Coord3D &)value_copy);
			}
		}
		else
			this->_M_insert_overflow(position, value, _IsPODType(), count);
	}
}
