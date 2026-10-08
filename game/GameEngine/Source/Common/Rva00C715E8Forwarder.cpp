// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00C715E8 (10 B) is a singleton forwarder with the same two instructions as
// the matched bfmeForward_00C70C00: it loads TheBfmeObject_00C70C00 (VA 0x0130A45C)
// into ECX and tail-jumps through ILT 0x0000EAFC.

class Gen_00C70C00Target
{
public:
	void bfmeForward(void);
};

extern Gen_00C70C00Target TheBfmeObject_00C70C00;

void bfmeForward_00C715E8(void)
{
	TheBfmeObject_00C70C00.bfmeForward();
}
