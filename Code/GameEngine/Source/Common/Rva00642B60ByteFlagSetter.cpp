// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva00642B60Owner
{
public:
	void setFlag();
};

void Rva00642B60Owner::setFlag()
{
	*(unsigned char *)((char *)this + 0x3c8) = 1;
}
