// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva007304A0
{
public:
	int getDword() const;

private:
	char m_pad00[0x24];
	int m_value24;
};

int Rva007304A0::getDword() const
{
	return m_value24;
}
