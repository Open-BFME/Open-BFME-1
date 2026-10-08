// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00C715C0 (10 B) is a singleton forwarder: it loads the address of the
// global TheBfmeObject_00C70C00 (VA 0x0130A45C) into ECX and tail-jumps to the
// member bfmeForward (ILT 0x0000EAFC). It is the same body as bfmeForward_00C70C00.

class Gen_00C70C00Target
{
public:
	void bfmeForward(void);
};

extern Gen_00C70C00Target TheBfmeObject_00C70C00;

void bfmeForward_00C715C0(void)
{
	TheBfmeObject_00C70C00.bfmeForward();
}
