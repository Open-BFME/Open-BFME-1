// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

void Gen0082E5F0(void *memory, unsigned int bytes);

class Rva0069C710Owner
{
public:
	void releaseSmall(void *memory);
};

void Rva0069C710Owner::releaseSmall(void *memory)
{
	if (memory != 0) {
		Gen0082E5F0(memory, 8);
	}
}
