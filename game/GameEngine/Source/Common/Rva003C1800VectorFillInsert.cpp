// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport vector 2-byte POD _M_fill_insert, retail 0x003C1800,
// 243 bytes. Same shape as BfmeVectorFillInsert36.cpp; element width is two
// bytes (sar 1 / add ebp,ebp). Overflow arm is the landed ushort
// _M_insert_overflow at 0x003C16A0. Copy/fill helpers are the Gen_p2pod
// tgrid bodies in this dump (d_003b8450).

struct Gen_t_003c1800_p2pod
{
	unsigned short v;
};

#include <vector>

Gen_t_003c1800_p2pod *bfmeUninitializedFillN2(
	Gen_t_003c1800_p2pod *first, unsigned count,
	const Gen_t_003c1800_p2pod &value);

template <>
void _STL::vector<Gen_t_003c1800_p2pod>::_M_fill_insert(
	Gen_t_003c1800_p2pod *position, unsigned count,
	const Gen_t_003c1800_p2pod &value)
{
	if (count != 0)
	{
		if ((unsigned)(this->_M_end_of_storage._M_data - this->_M_finish)
			>= count)
		{
			Gen_t_003c1800_p2pod value_copy = value;
			const unsigned elements_after =
				(unsigned)(this->_M_finish - position);
			Gen_t_003c1800_p2pod *old_finish = this->_M_finish;
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
				bfmeUninitializedFillN2(this->_M_finish,
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
