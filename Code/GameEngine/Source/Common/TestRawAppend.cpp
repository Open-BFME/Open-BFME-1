// Open-BFME5 conversion for the raw-buffer diagnostic writer at 0x009AAC30.

extern "C" __declspec(dllimport) void *__cdecl fopen(const char *name, const char *mode);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(
	const void *buffer, unsigned int size, unsigned int count, void *stream);
extern "C" __declspec(dllimport) int __cdecl fclose(void *stream);

class BfmeRawBuffer
{
public:
	char m_pad0[0x208];
	unsigned int m_rowBytes;
	unsigned int m_extraWords;
	char m_pad210[0x44];
	void *m_data;
};

void appendTestRaw(BfmeRawBuffer *buffer)
{
	void *file = fopen("test.raw", "ab");
	fwrite(buffer->m_data, buffer->m_rowBytes + buffer->m_extraWords * 2, 1, file);
	fclose(file);
}
