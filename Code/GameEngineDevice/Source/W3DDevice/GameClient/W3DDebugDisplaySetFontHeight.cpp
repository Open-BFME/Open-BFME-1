// ?setFontHeight@W3DDebugDisplay@@QAEXH@Z
// cl: /DNDEBUG /MD /EHsc

// The vendored inline setter is otherwise no longer emitted from W3DDisplay.cpp
// after its BFME init body moved to W3DDisplayInit_Bfme.cpp. Retail stores the
// height at W3DDebugDisplay+0x28.
typedef int Int;

class W3DDebugDisplay
{
private:
	char m_prefix[0x28];
	Int m_fontHeight;

public:
	void setFontHeight(Int height);
};

void W3DDebugDisplay::setFontHeight(Int height)
{
	m_fontHeight = height;
}
