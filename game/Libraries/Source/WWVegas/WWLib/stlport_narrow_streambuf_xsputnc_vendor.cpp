// cl: /O2 /MD
// stlport

#include <stl/_streambuf.h>

namespace _STL
{

streamsize basic_streambuf<char, char_traits<char> >::_M_xsputnc(char_type c, streamsize n)
{
	streamsize result = 0;
	const int_type eofv = traits_type::eof();

	while (result < n)
	{
		if (_FILE_O_avail(_M_put) > 0)
		{
			size_t chunk = (min)((size_t)_FILE_O_avail(_M_put), (size_t)(n - result));
			traits_type::assign(_FILE_O_next(_M_put), chunk, c);
			result += chunk;
			_FILE_O_bump(_M_put, (int)chunk);
		}
		else if (!traits_type::eq_int_type(this->overflow(traits_type::to_int_type(c)), eofv))
			++result;
		else
			break;
	}
	return result;
}

} // namespace _STL
