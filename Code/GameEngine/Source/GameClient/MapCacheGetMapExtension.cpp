// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

private:
	void *m_data;
};

class MapCache
{
public:
	AsciiString getMapExtension() const;
};

AsciiString MapCache::getMapExtension() const
{
	return AsciiString("map");
}
