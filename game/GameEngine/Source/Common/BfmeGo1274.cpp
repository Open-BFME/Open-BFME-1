// cl: /DNDEBUG /MD

__forceinline void *operator new(unsigned int, void *p) throw()
{
	return p;
}

class BfmeB1166
{
public:
	BfmeB1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04,
		unsigned int a05, unsigned int a06, unsigned int a07, unsigned int a08,
		unsigned int a09, unsigned int a10);
	unsigned int m_bfme00[10];
};

template <int N> class BitFlags;

class Object
{
public:
	void clearAndSetModelConditionFlags(const BitFlags<320> &clear,
		const BitFlags<320> &set);
};

class Gen_002A6DE0
{
public:
	void bfmeGo1274(void);

private:
	unsigned char m_bfmeGap[8];
	Object *m_object;
};

// ?bfmeGo1274@Gen_002A6DE0@@QAEXXZ
void Gen_002A6DE0::bfmeGo1274(void)
{
	Object *object = m_object;
	unsigned char clearStorage[sizeof(BfmeB1166)];
	BfmeB1166 *clear = new (clearStorage) BfmeB1166(
		0, 0x5f, 0x5d, 0x28, 0x6f, 0x5e, 0x7c, 0x60, 0x61, 0x62);
	unsigned int setStorage[10] = {};
	object->clearAndSetModelConditionFlags(
		reinterpret_cast<const BitFlags<320> &>(*clear),
		reinterpret_cast<const BitFlags<320> &>(setStorage));
}
