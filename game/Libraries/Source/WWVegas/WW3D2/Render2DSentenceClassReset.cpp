// cl: /DNDEBUG /MD /EHsc
// BFME Render2DSentenceClass::Reset at retail 0x0093EA60.

void __cdecl W3DRadarResetLock(void);
char __cdecl bfmeUnlock1179(void);

class W3DRadarResetGuard
{
public:
	W3DRadarResetGuard(void)
	{
		W3DRadarResetLock();
	}

	~W3DRadarResetGuard(void)
	{
		bfmeUnlock1179();
	}
};

class Render2DClass
{
public:
	~Render2DClass(void);
};

class SurfaceResource
{
public:
	virtual void __stdcall QueryInterface(void);
	virtual void __stdcall AddRef(void);
	virtual void __stdcall Release(void);
};

class SurfaceClass
{
public:
	void Unlock(void);

	SurfaceResource *m_surface;
};

struct CursorVector
{
	float x;
	float y;

	void Set(float newX, float newY)
	{
		x = newX;
		y = newY;
	}
};

template <class T>
class DynamicVectorClass
{
public:
	int Count(void) const
	{
		return m_activeCount;
	}

	T &operator[](int index)
	{
		return m_vector[index];
	}

	bool Delete(int index);

public:
	T *m_vector;
	int m_vectorMax;
	bool m_isValid;
	bool m_isAllocated;
	char m_pad0a[2];
	char m_pad0c[4];
	int m_activeCount;
	int m_growthStep;
};

class Render2DSentenceClass
{
public:
	struct RendererDataStruct
	{
		Render2DClass *Renderer;
		void *Surface;
	};

	virtual void Reset(void);

	int rendererCount(void) const
	{
		return m_rendererLayout.m_activeCount;
	}

private:
	char m_pad04[0x30];
	union
	{
		char m_renderers[0x18];
		struct
		{
			char m_pad00[4];
			RendererDataStruct *m_vector;
			char m_pad08[8];
			int m_activeCount;
			int m_growthStep;
		} m_rendererLayout;
	};
	char m_pad4c[0x14];
	CursorVector m_cursor;
	char m_pad68[0x14];
	SurfaceClass m_curSurface;
	bool m_monoSpaced;
	char m_pad81[0x2c];
	bool m_parseHotKey;
	char m_padae[2];
	void *m_lockedPtr;

	void Release_Pending_Surfaces(void);
	void Reset_Sentence_Data(void);
};

#define DELETE_RENDERER(owner, index) \
	(reinterpret_cast<DynamicVectorClass<Render2DSentenceClass::RendererDataStruct> *>( \
		reinterpret_cast<char *>(owner) + 0x34)->Delete(index))

void Render2DSentenceClass::Reset(void)
{
	W3DRadarResetGuard lock;
	if (m_lockedPtr != 0)
	{
		m_curSurface.Unlock();
		m_lockedPtr = 0;
	}

	SurfaceResource *surface = m_curSurface.m_surface;
	if (surface != 0)
	{
		surface->Release();
		m_curSurface.m_surface = 0;
	}

	while (rendererCount() > 0)
	{
		Render2DClass *renderer = m_rendererLayout.m_vector[0].Renderer;
		if (renderer != 0)
		{
			renderer->~Render2DClass();
			::operator delete(renderer);
		}
		DELETE_RENDERER(this, 0);
	}

	m_cursor.Set(0.0F, 0.0F);
	m_monoSpaced = false;
	m_parseHotKey = false;
	Release_Pending_Surfaces();
	Reset_Sentence_Data();
}
