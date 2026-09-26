// cl: /DNDEBUG /MD /GX /Od /GZ /GS

extern "C" void *memcpy(void *destination, const void *source, unsigned int count);
extern "C" void *memset(void *destination, int value, unsigned int count);

__declspec(dllimport) void *__stdcall CreateThread(
	void *security, unsigned int stackSize, void *start,
	void *parameter, unsigned int flags, unsigned int *identifier);
__declspec(dllimport) int __stdcall CloseHandle(void *handle);

extern "C" void *Rva007F0000Alloc(int size);
extern "C" void Rva007FE200(const int *value);
extern "C" void Rva007FE210(void *object);
extern "C" int Rva007FE250(void *request);

struct Rva007FDFF0Request
{
	int status;
	unsigned int address;
	void *worker;
	void *cleanup;
	char pad10[0x44];
};

// ?Rva007FDFF0Connect@@YAPAXPBDH@Z
// The resolver accepts dotted numeric addresses directly and starts the
// DirtySock name-resolution worker for every other host string.
void *Rva007FDFF0Connect(const char *host, int timeout)
{
	int octet;
	int value;
	char *cursor;
	Rva007FDFF0Request *request;
	unsigned int threadId;
	void *thread;

	if (timeout < 0)
		return 0;

	request = (Rva007FDFF0Request *)Rva007F0000Alloc(0x5c);
	memset(request, 0, 0x5c);
	request->worker = (void *)Rva007FE200;
	request->cleanup = (void *)Rva007FE210;

	cursor = (char *)host;
	for (; *cursor != 0; ++cursor)
	{
		if (*cursor != '.' && (*cursor < '0' || *cursor > '9'))
			break;
	}
	if (*cursor == 0)
	{
		cursor = (char *)host;
		octet = 0;
		for (; octet < 4; ++octet)
		{
			value = 0;
			while (*cursor >= '0' && *cursor <= '9')
			{
				value = value * 10 + (*cursor & 0xf);
				++cursor;
			}
			if (*cursor != (octet >= 3 ? 0 : '.') || value > 0xff)
			{
				request->status = -2;
				request->address = 0;
				goto numeric_return;
			}
			request->address = (request->address << 8) | value;
			request->status = 1;
			++cursor;
		}
	numeric_return:
		return request;
	}

resolve:
	memcpy((char *)request + 0x10, host, 0x40);
	((char *)request)[0x4f] = 0;
	thread = CreateThread(0, 0, (void *)Rva007FE250, request, 0, &threadId);
	if (thread != 0)
		CloseHandle(thread);
	return request;
}
