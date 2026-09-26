// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

struct Gen_t_0074d9c0_p128pod
{
	char bytes[36];
};

#include <vector>

Gen_t_0074d9c0_p128pod *bfmeUninitializedFillN36(
	Gen_t_0074d9c0_p128pod *first, unsigned count,
	const Gen_t_0074d9c0_p128pod &value);

template <>
void _STL::vector<Gen_t_0074d9c0_p128pod>::_M_fill_insert(
	Gen_t_0074d9c0_p128pod *position, unsigned count,
	const Gen_t_0074d9c0_p128pod &value)
{
	if (count != 0)
	{
		if ((unsigned)(this->_M_end_of_storage._M_data - this->_M_finish)
			>= count)
		{
			Gen_t_0074d9c0_p128pod value_copy = value;
			const unsigned elements_after =
				(unsigned)(this->_M_finish - position);
			Gen_t_0074d9c0_p128pod *old_finish = this->_M_finish;
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
				bfmeUninitializedFillN36(this->_M_finish,
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
