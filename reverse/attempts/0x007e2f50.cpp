// ?d_007e2f50@@YAXXZ
// partial score=0.75 date=2026-09-03
// ?readPacket@BfmeB996@@QAEDPAPAHPAH0PADD@Z [retail body 0x007E2F50]
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class BfmeDev996
{
public:
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual int consume(void *data, int size);
	virtual void v4(void);
	virtual void set996(int value, int enabled);
	virtual void v6(void);
	virtual void v7(void);
	virtual void v8(void);
	virtual void v9(void);
	virtual void v10(void);
	virtual void v11(void);
	virtual int available(void);
};

void *operator new[](unsigned int size);
extern "C" void *memset(void *destination, int value, unsigned int size);

class BfmeB996
{
public:
	char readPacket(int *output, int *first, int *second,
		char *stop, char flag);
	char bfmeTry996(int first, int second, char *stop);

private:
	char m_pad[4];
	BfmeDev996 *m_dev;
	int m_kind;
	int m_limit;
};

char BfmeB996::readPacket(int *output, int *first, int *second,
	char *stop, char flag)
{
	*stop = 0;
	*output = 0;
	int *firstPointer = first;
	int *secondPointer = second;
	BfmeB996 *reader = this;
	char *stopPointer = stop;
	int *outputPointer = output;

	if (!reader->bfmeTry996((int)firstPointer, (int)secondPointer, stopPointer))
		return 0;

	if (flag)
		goto packet;

	{
		int secondValue = *secondPointer;
		if (reader->m_dev->available() + secondValue - 8 > reader->m_limit) {
			*stopPointer = 1;
			return 0;
		}
		reader->m_dev->set996(secondValue - 8, 1);
		return 1;
	}

packet:
	{
		int secondValue = *secondPointer;
		int firstValue = *firstPointer;
		char *buffer = (char *)operator new[](secondValue);
		memset(buffer, 0, secondValue);

		*(int *)(buffer + 4) = secondValue;
		*(int *)buffer = firstValue;
		*outputPointer = (int)buffer;

		if (reader->m_dev->consume(buffer + 8, secondValue - 8) ==
			secondValue - 8)
			return 1;

		if (*outputPointer != 0) {
			delete [] (char *)*outputPointer;
			*outputPointer = 0;
		}
		*stopPointer = 1;
		return 0;
	}
}
