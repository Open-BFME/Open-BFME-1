// BFME subtitle update body at retail RVA 0x006EE520.
// The address-qualified class keeps the unresolved original method name
// explicit while the manager and sink access views preserve unresolved callee
// identities at their retail addresses.
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// stlport
#include <vector>

class Rva006EE520;

template <typename T>
class StringBase
{
	protected:
	~StringBase();

	void releaseBuffer();
	void *m_data;

	friend class Rva006EE520;
};

typedef StringBase<unsigned short> UnicodeString;

class SubtitleEntry;

class Rva006ED3D0TextAccess
{
public:
	UnicodeString getText(int index) const;
};

class SubtitleManager : public Rva006ED3D0TextAccess
{
public:
	int getStartFrame(int index) const;
	bool hasBeenDisplayed(int index) const;
	unsigned int getColor(int index) const;
	void setDisplayedStats(int index);

	char m_pad00[0x14];
	_STL::vector<SubtitleEntry *> m_entries;
};

class Rva00435A40Sink
{
public:
	void publish(const UnicodeString &text, unsigned int color);
};

class SubtitleSink : public Rva00435A40Sink
{
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

		self->m_sink->publish(self->m_manager->getText(i),
			self->m_manager->getColor(i));
		self->m_manager->setDisplayedStats(i);
	}
}
