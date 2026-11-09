// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// STLport 4.5.3

namespace _STL
{

class __Named_exception
{
public:
	virtual ~__Named_exception();
};

class ios_base
{
public:
	class failure : public __Named_exception
	{
	public:
		virtual ~failure();
	};
};

ios_base::failure::~failure()
{
}

} // namespace _STL
