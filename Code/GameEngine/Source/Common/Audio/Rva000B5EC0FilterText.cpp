// cl: /DNDEBUG /MD /EHsc

// BFME's three-bit filter formatter.  The adjacent AudioAffect formatter
// proves this text sink's overloaded virtual ABI: MSVC 7.1 places append(int)
// at +0x34 and append(const char *) at +0x38.
class Rva000B5EC0TextOutput
{
public:
	virtual void reserved0() = 0;
	virtual void reserved1() = 0;
	virtual void reserved2() = 0;
	virtual void reserved3() = 0;
	virtual void reserved4() = 0;
	virtual void reserved5() = 0;
	virtual void reserved6() = 0;
	virtual void reserved7() = 0;
	virtual void reserved8() = 0;
	virtual void reserved9() = 0;
	virtual void reserved10() = 0;
	virtual void reserved11() = 0;
	virtual void reserved12() = 0;
	virtual Rva000B5EC0TextOutput *append(const char *text) = 0;
	virtual Rva000B5EC0TextOutput *append(int value) = 0;
};

Rva000B5EC0TextOutput *Rva000B5EC0FilterText(
	Rva000B5EC0TextOutput *output, const unsigned int *flags)
{
	if (*flags == 0)
	{
		output->append("NONE");
		return output;
	}

	if (*flags & 1)
	{
		output->append("TACTICAL");
		if (*flags & ~1u)
			output->append("|");
	}
	if (*flags & 2)
	{
		output->append("WORLD");
		if (*flags & ~3u)
			output->append("|");
	}
	if (*flags & 4)
	{
		output->append("SHELL");
		if (*flags & ~7u)
			output->append("|");
	}
	if (*flags & ~7u)
	{
		output->append("UKNOWN (")->append((int)(*flags & ~7u))->append(")");
	}

	return output;
}
