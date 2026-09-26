// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva00383F90Field10
{
public:
	int get() const;

private:
	unsigned char m_beforeField10[ 0x10 ];
	int m_field10;
};

int Rva00383F90Field10::get() const
{
	return m_field10;
}
