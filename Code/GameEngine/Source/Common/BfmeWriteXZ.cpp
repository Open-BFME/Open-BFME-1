class StreamWriter
{
public:
	void separate(int value);
};

struct BfmeVecXZ
{
	char m_pad00[4];
	float m_at04;
	float m_at08;
};

StreamWriter *formatReal(StreamWriter *stream, double value);

StreamWriter *bfmeWriteXZ(StreamWriter *stream, BfmeVecXZ *value)
{
	float second = value->m_at08;
	float first = value->m_at04;
	StreamWriter *result = formatReal(stream, first);
	result->separate(0x20);
	formatReal(result, second);
	return stream;
}
