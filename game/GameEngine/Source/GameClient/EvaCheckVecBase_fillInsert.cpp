// cl: /EHsc
// stlport

// EvaCheckVecBase::fillInsert, retail 0x00425420, 307 bytes.
// EvaCheckVecBase::resize at 0x00425E40 is the named caller.  Retail uses the
// STLport insertion shape for a nontrivial 24-byte record.

#include <vector>

struct Gen_t_004258e0_p24cd
{
	int m_words[6];

	Gen_t_004258e0_p24cd();
	Gen_t_004258e0_p24cd(const Gen_t_004258e0_p24cd &other);
};

struct Elem24
{
	char m_bytes[24];
};

Elem24 *rva00423200FillWalk(Elem24 *first, unsigned count,
	const Elem24 *value);

template <>
void _STL::vector<Gen_t_004258e0_p24cd>::_M_fill_insert(
	Gen_t_004258e0_p24cd *position, unsigned count,
	const Gen_t_004258e0_p24cd &value)
{
	if (count != 0)
	{
		if ((unsigned)(this->_M_end_of_storage._M_data - this->_M_finish)
			>= count)
		{
			Gen_t_004258e0_p24cd value_copy = value;
			const unsigned elements_after =
				(unsigned)(this->_M_finish - position);
			Gen_t_004258e0_p24cd *old_finish = this->_M_finish;
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
				rva00423200FillWalk(
					reinterpret_cast<Elem24 *>(this->_M_finish),
					count - elements_after,
					reinterpret_cast<const Elem24 *>(&value_copy));
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
