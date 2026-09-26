// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <sstream>

extern "C" void *memset(void *, int, unsigned);
#pragma intrinsic(memset)

namespace _STL
{

template <>
streamsize basic_stringbuf<char, char_traits<char>, allocator<char> >::_M_xsputnc(
	char_type c, streamsize n)
{
	streamsize nwritten = 0;

	if ((_M_mode & ios_base::out) && n > 0)
	{
		if (this->pbase() == _M_str.data())
		{
			ptrdiff_t avail = _M_str.data() + _M_str.size() - this->pptr();
			if (avail > n)
			{
				memset(this->pptr(), c, n);
				this->pbump((int)n);
				return n;
			}
			else
			{
				memset(this->pptr(), c, avail);
				nwritten += avail;
				n -= avail;
				this->setp(_M_Buf, _M_Buf + (int)_S_BufSiz);
			}
		}

		if (this->_M_mode & ios_base::in)
		{
			ptrdiff_t get_offset = this->gptr() - this->eback();
			_M_str.append(n, c);

			char *data_ptr = (char *)_M_str.data();
			size_t data_size = _M_str.size();
			this->setg(data_ptr, data_ptr + get_offset, data_ptr + data_size);
			this->setp(data_ptr, data_ptr + data_size);
			this->pbump((int)data_size);
		}
		else
		{
			_M_append_buffer();
			_M_str.append(n, c);
		}

		nwritten += n;
	}

	return nwritten;
}

}

template class _STL::basic_stringbuf<char, _STL::char_traits<char>, _STL::allocator<char> >;
