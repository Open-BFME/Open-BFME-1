// Retail body at RVA 0x0009ECA0.

typedef unsigned short WideChar;

extern "C" __declspec(dllimport) unsigned short __cdecl towlower(unsigned short value);

template <typename T>
class StringBase
{
	private:
	int compareNoCaseRaw(const T *left, const T *right, int length) const throw();
};

template <>
int StringBase<WideChar>::compareNoCaseRaw(const WideChar *left,
	const WideChar *right, int length) const throw()
{
	while (length > 0)
	{
		const WideChar leftLower = (WideChar)towlower(*left);
		const WideChar rightLower = (WideChar)towlower(*right);
		if (leftLower != rightLower)
			return (int)leftLower - (int)rightLower;
		++left;
		++right;
		--length;
	}
	return 0;
}
