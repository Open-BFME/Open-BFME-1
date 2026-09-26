// cl: /DNDEBUG /MD /EHsc

class GameLogicFrameSlice
{
public:
	unsigned char m_unmodelled_000[0x3c];
	unsigned int m_frame;
};

extern GameLogicFrameSlice *TheGameLogic;

class Rva000F72D0FrameCachedValue
{
public:
	float value(float range);

private:
	void refresh(float range);

	unsigned char m_unmodelled_000[0xf4];
	float m_value;
	unsigned int m_frame;
};

float Rva000F72D0FrameCachedValue::value(float range)
{
	if (m_frame < TheGameLogic->m_frame)
		refresh(range);
	return m_value;
}
