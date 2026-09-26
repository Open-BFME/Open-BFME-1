// cl: /DNDEBUG /MD /EHsc
// Entry and exit roles come from the trigger-area caller; original owner and method spellings are unknown.
class Object;

struct Rva0018F050TriggerArea
{
	void notifyObjectEntered(Object *object);
	void notifyObjectExited(Object *object);
	unsigned char m_prefix[0x80];
	void (__cdecl *m_callback)(Object *object, void *context, int entered);
	void *m_context;
};

void Rva0018F050TriggerArea::notifyObjectEntered(Object *object)
{
	void (__cdecl *callback)(Object *, void *, int) = m_callback;
	if (callback)
	{
		void *context = m_context;
		if (context)
			callback(object, context, 1);
	}
}

void Rva0018F050TriggerArea::notifyObjectExited(Object *object)
{
	void (__cdecl *callback)(Object *, void *, int) = m_callback;
	if (callback)
	{
		void *context = m_context;
		if (context)
			callback(object, context, 0);
	}
}
