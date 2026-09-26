// Retail 0x0043DED0 is the removed InGameUI message(AsciiString, ...) layer.
// The carved body loads the by-value string at +8 and tail-jumps to the retail
// AsciiString releaseBuffer body at 0x00887940.
class BFMERetailAsciiString
{
	friend void rva0043ded0( void *, BFMERetailAsciiString, ... );

private:
	void releaseBuffer();
};

void rva0043ded0( void *unused, BFMERetailAsciiString other, ... )
{
	(void)unused;
	other.releaseBuffer();
}
