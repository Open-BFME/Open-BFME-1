// ?d_006ee520@@YAXXZ
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Structural BFME recovery, retail 0x006EE520 (223 bytes).

// stlport
#include <vector>

template <typename T>
class StringBase
{
	public:
	~StringBase();

	protected:
	void releaseBuffer();
	void *m_data;
};

typedef StringBase<unsigned short> UnicodeString;

class SubtitleEntry;

class SubtitleManager
{
public:
	int getStartFrame(int index) const;
	bool hasBeenDisplayed(int index) const;
	UnicodeString getText(int index) const;
	unsigned int getColor(int index) const;
	void setDisplayedStats(int index);

	char m_pad00[0x14];
	_STL::vector<SubtitleEntry *> m_entries;
};

class SubtitleSink
{
public:
	void publish(UnicodeString text, unsigned int color);
};

class Rva006EE520
{
public:
	void update(int frame);

private:
	char m_pad00[0x184];
	SubtitleManager *m_manager;
	SubtitleSink *m_sink;
};

void Rva006EE520::update(int frame)
{
	Rva006EE520 *self = this;
	SubtitleManager *manager = self->m_manager;
	if (!manager || !self->m_sink)
		return;

	unsigned int color;
	const int count = (int)manager->m_entries.size();
	for (int i = 0; i < count; ++i)
	{
		int startFrame = self->m_manager->getStartFrame(i);
		if (self->m_manager->hasBeenDisplayed(i) || frame < startFrame)
			continue;

		{
			UnicodeString text = self->m_manager->getText(i);
			color = self->m_manager->getColor(i);
			self->m_sink->publish(text, color);
		}
		self->m_manager->setDisplayedStats(i);
	}
}
