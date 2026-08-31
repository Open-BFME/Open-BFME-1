// ?getFileLengthMS@MilesAudioManager@@UBEMVAsciiString@@@Z
// partial score=0.995 date=2026-08-31
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME's AsciiString uses an eight-byte header: refcount, length, capacity.

#include "mss.h"

typedef void *HSTREAM;
extern "C" __declspec(dllimport) HSTREAM __stdcall AIL_open_stream(
	HDIGDRIVER driver, const char *filename, int stream_mem);
extern "C" __declspec(dllimport) void __stdcall AIL_stream_ms_position(
	HSTREAM stream, long *total_milliseconds, long *current_milliseconds);
extern "C" __declspec(dllimport) void __stdcall AIL_close_stream(HSTREAM stream);

typedef bool Bool;
typedef float Real;

class AsciiString
{
private:
	struct Data
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
	};

	Data *m_data;

public:
	~AsciiString();

	Bool isEmpty() const
	{
		return m_data == 0 || m_data->length == 0;
	}

	const char *str() const
	{
		return reinterpret_cast<const char *>(m_data + 1);
	}
};

// Only the digital-driver offset is observed by this body. The prefix includes
// the vptr already present in the retail MilesAudioManager object.
class MilesAudioManager
{
private:
	// The compiler supplies the four-byte vptr before this explicit prefix.
	unsigned char m_retailPrefix[0x95c];
	HDIGDRIVER m_digitalHandle;

public:
	virtual Real getFileLengthMS(AsciiString strToLoad) const;
};

Real MilesAudioManager::getFileLengthMS(AsciiString strToLoad) const
{
	if (strToLoad.isEmpty()) {
		return 0.0f;
	}

	const char *filename = strToLoad.str();
	HSTREAM stream = AIL_open_stream(m_digitalHandle, filename, 0);
	if (stream == 0) {
		return 0.0f;
	}

	long result;
	AIL_stream_ms_position(stream, &result, 0);
	AIL_close_stream(stream);

	Real answer;
	answer = (Real)(result);
	return answer;
}
