// cl: /O2 /Ob0

// Open-BFME5: one-shot forwarding of a small drawable event record.  The
// record supplies a position payload and two byte-sized selectors; the
// drawable contributes its stable DrawableID.

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

class Drawable
{
public:
	DrawableID getID(void) const;
};

struct BfmeDrawableEventRecord
{
	char m_unused[8];
	char m_position[4];
	unsigned char m_firstSelector;
	unsigned char m_secondSelector;
};

class BfmeDrawableEventManager
{
public:
	void forwardDrawableEvent(DrawableID id, const void *position,
		unsigned char secondSelector, unsigned char firstSelector);
};

extern BfmeDrawableEventManager *g_bfmeDrawableEventManager;

class BfmeDrawableEventForwarder
{
public:
	void forwardOnce(int, int, int);

private:
	char m_unused[4];
	BfmeDrawableEventRecord *m_record;
	Drawable *m_drawable;
	char m_unused0C[4];
	unsigned char m_forwarded;
};

void BfmeDrawableEventForwarder::forwardOnce(int, int, int)
{
	BfmeDrawableEventForwarder *forwarder = this;
	unsigned char forwarded = forwarder->m_forwarded;
	Drawable *drawable = forwarder->m_drawable;
	if (!forwarded)
	{
		forwarder->m_forwarded = 1;
		BfmeDrawableEventRecord *record = forwarder->m_record;
		if (record)
		{
			g_bfmeDrawableEventManager->forwardDrawableEvent(
				drawable->getID(), record->m_position,
				record->m_secondSelector, record->m_firstSelector);
		}
	}
}
