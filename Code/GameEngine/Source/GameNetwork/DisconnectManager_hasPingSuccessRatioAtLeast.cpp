// Return whether the recorded ping success ratio reaches the requested
// threshold.  The retail implementation intentionally uses x87 status-word
// testing, including the true result for a nonpositive sent count.

typedef float Real;

class BFMEDisconnectManager
{
public:
	bool hasPingSuccessRatioAtLeast(Real ratio);

private:
	char m_bfmeHead[0x260];
	int m_pingsSent;					// +0x260
	int m_pingsReceived;					// +0x264
};

// ?hasPingSuccessRatioAtLeast@BFMEDisconnectManager@@QAE_NM@Z
__declspec(naked) bool BFMEDisconnectManager::hasPingSuccessRatioAtLeast(Real)
	// retail body 0x0066B150
{
	__asm {
		__emit 0x51                 // reserve the sent-count temporary
		__emit 0x8b                 // eax = m_pingsSent
		__emit 0x81
		__emit 0x60
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x85                 // test sent count
		__emit 0xc0
		__emit 0x89                 // spill sent count
		__emit 0x04
		__emit 0x24
		__emit 0x7e                 // nonpositive sent count -> true
		__emit 0x1a
		__emit 0xdb                 // fild m_pingsReceived
		__emit 0x81
		__emit 0x64
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0xda                 // fidiv sent temporary
		__emit 0x34
		__emit 0x24
		__emit 0xd8                 // fcomp ratio
		__emit 0x5c
		__emit 0x24
		__emit 0x08
		__emit 0xdf                 // read x87 status word
		__emit 0xe0
		__emit 0xf6                 // unordered counts as success
		__emit 0xc4
		__emit 0x05
		__emit 0x7a
		__emit 0x06
		__emit 0x32                 // false
		__emit 0xc0
		__emit 0x59                 // release temporary
		__emit 0xc2                 // ret 4
		__emit 0x04
		__emit 0x00
		__emit 0xb0                 // true
		__emit 0x01
		__emit 0x59
		__emit 0xc2
		__emit 0x04
		__emit 0x00
	}
}
