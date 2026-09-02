// cl: /DNDEBUG /MD /EHs-c- /Oy-
// Open-BFME: three guarded strncpy(dst, src, 0x3f) into this+0x9E84 / +0x9EC4
// / +0x9F04. IAT is CSE'd into edi. Likely Debug::SetBuildInfo.

extern "C" __declspec(dllimport) char *strncpy(char *dest, const char *src, unsigned count);

class Debug
{
	unsigned char m_pad[0x9E84];
	char m_version[0x40];
	char m_intVersion[0x40];
	char m_buildDate[0x40];

public:
	void SetBuildInfo(const char *version, const char *internalVersion, const char *buildDate);
};

// ?SetBuildInfo@Debug@@QAEXPBD00@Z
void Debug::SetBuildInfo(const char *version, const char *internalVersion, const char *buildDate)
{
	if (version)
		strncpy(m_version, version, 0x3f);
	if (internalVersion)
		strncpy(m_intVersion, internalVersion, 0x3f);
	if (buildDate)
		strncpy(m_buildDate, buildDate, 0x3f);
}
