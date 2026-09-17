// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class UnicodeString
{
public:
	void set(const UnicodeString &source);

private:
	void *m_data;
};

struct Gen_t_003b5310_p40cd
{
	int m_unknown00;
	UnicodeString m_name04;
	UnicodeString m_name08;
	UnicodeString m_name0c;
	int m_value10;
	int m_value14;
	UnicodeString m_name18;
	unsigned char m_flag1c;
	unsigned char m_flag1d;
	unsigned char m_padding1e[2];
	int m_value20;
	int m_value24;

	Gen_t_003b5310_p40cd &operator=(const Gen_t_003b5310_p40cd &source)
	{
		m_name04.set(source.m_name04);
		m_name08.set(source.m_name08);
		m_name0c.set(source.m_name0c);
		m_value10 = source.m_value10;
		m_value14 = source.m_value14;
		m_name18.set(source.m_name18);
		m_flag1c = source.m_flag1c;
		m_flag1d = source.m_flag1d;
		m_value20 = source.m_value20;
		m_value24 = source.m_value24;
		return *this;
	}
};

namespace _STL
{

struct random_access_iterator_tag {};

template <class Input, class Output, class Distance>
inline Output __copy(Input first, Input last, Output result,
	const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0; --count)
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}

template Gen_t_003b5310_p40cd *
	__copy<const Gen_t_003b5310_p40cd *, Gen_t_003b5310_p40cd *, int>(
		const Gen_t_003b5310_p40cd *, const Gen_t_003b5310_p40cd *,
		Gen_t_003b5310_p40cd *, const random_access_iterator_tag &, int *);

}
