// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x000BE090, 421 bytes: STLport's
// vector<vector<ScienceType>>::_M_fill_insert, the real body behind the
// 0x0000FC86 ILT thunk.  Its one caller is the grow branch of
// Rva000BE440Store::resizeGroups (retail 0x000BE300), which pushes
// (finish, count - size, &value); the matched caller types that vector as
// vector<ScienceVec>, so the element here is a 12-byte ScienceVec.
//
// The element type is fixed by the bodies this one calls, not by the lift's
// name: the copy constructor at 0x000BB890 strides 4 bytes (ScienceType),
// and __copy_backward / fill at 0x000BCCE0 / 0x000BCC50 walk 12-byte
// elements through vector<p4pod>::operator= (0x00018A70 -> 0x000BC4B0).
// ICoord2D would stride 8, and the 0x0000FC86 thunk would then belong to
// some other body.
//
// /EHsc because retail carries the SEH registration frame and the two EH
// state stores that the destructor of the local ScienceVec needs; the
// stock header's out-of-line helpers stay in the static lib exactly as the
// neighbouring caller TU sees them.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

enum ScienceType
{
    SCIENCE_INVALID = -1
};

typedef _STL::vector<ScienceType> ScienceVec;

template <>
void _STL::vector<ScienceVec, _STL::allocator<ScienceVec> >::_M_fill_insert(
	ScienceVec *position, unsigned int count, const ScienceVec &value)
{
	if (count != 0)
	{
		if ((unsigned int)(this->_M_end_of_storage._M_data - this->_M_finish)
			>= count)
		{
			ScienceVec value_copy = value;
			const unsigned int elements_after =
				(unsigned int)(this->_M_finish - position);
			ScienceVec *old_finish = this->_M_finish;
			if (elements_after > count)
			{
				__uninitialized_copy(this->_M_finish - count,
					this->_M_finish, this->_M_finish, _IsPODType());
				this->_M_finish += count;
				__copy_backward_ptrs(position, old_finish - count,
					old_finish, _TrivialAss());
				_STLP_STD::fill(position, position + count, value_copy);
			}
			else
			{
				uninitialized_fill_n(this->_M_finish,
					count - elements_after, value_copy);
				this->_M_finish += count - elements_after;
				__uninitialized_copy(position, old_finish,
					this->_M_finish, _IsPODType());
				this->_M_finish += elements_after;
				_STLP_STD::fill(position, old_finish, value_copy);
			}
		}
		else
			this->_M_insert_overflow(position, value, _IsPODType(), count);
	}
}
