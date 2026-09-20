// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AsciiString;

class QuickMatchPreferences
{
public:
	void setLastLadder(const AsciiString& address, unsigned short port);
};

class Rva00029B36QuickMatchPreferencesThunk : public QuickMatchPreferences
{
public:
	void forward(const AsciiString& address, unsigned short port);
};

// ?forward@Rva00029B36QuickMatchPreferencesThunk@@QAEXABVAsciiString@@G@Z
void Rva00029B36QuickMatchPreferencesThunk::forward(
	const AsciiString& address, unsigned short port)
{
	QuickMatchPreferences::setLastLadder(address, port);
}
