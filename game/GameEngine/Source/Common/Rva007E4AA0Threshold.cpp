// Open-BFME5: clean C++ conversion of the transformed-threshold comparison.

int __stdcall rva000190ABTransform(int value);

class Rva007E4AA0Threshold
{
public:
	bool isBelowTransformed(int value) const;

private:
	char m_pad00[0x4C];
	int m_threshold;
};

bool Rva007E4AA0Threshold::isBelowTransformed(int value) const
{
	return m_threshold < rva000190ABTransform(value);
}
