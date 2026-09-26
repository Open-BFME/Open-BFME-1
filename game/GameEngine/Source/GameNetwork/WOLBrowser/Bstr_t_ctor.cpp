// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

namespace _com_util
{
	unsigned short *__stdcall ConvertStringToBSTR(const char *value);
}

void __stdcall _com_issue_error(long error);

class _bstr_t
{
private:
	struct Data
	{
		unsigned short *m_wstr;
		long m_refs;
		long m_len;

		Data(const char *value)
		{
			m_refs = 0;
			m_len = 1;
			m_wstr = _com_util::ConvertStringToBSTR(value);
		}
	};

	Data *m_data;

public:
	_bstr_t(const char *value);
};

_bstr_t::_bstr_t(const char *value)
{
	Data *data = new Data(value);
	m_data = data;
	if (!m_data)
		_com_issue_error(0x8007000e);
}
