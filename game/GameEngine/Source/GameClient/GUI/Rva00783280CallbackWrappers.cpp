// cl: /DNDEBUG /MD /EHsc
extern void j_0001df43(void);
class WindowManager
{
public:
	void invokeCallback(const char *name, void *unused);
	void invokeCallbackWithArg_0046CE60(const char *name, void *context);
	void method_0046CF80(const char *name);
};

extern WindowManager *g_rva012F19E8WindowManager;	// retail [0x012F19E8]

// ?Rva00783280InvokeCallback@@YAXPBDPAX@Z
void Rva00783280InvokeCallback(const char *name, void *unused)
{
	g_rva012F19E8WindowManager->invokeCallback(name, unused);
}

// ?Rva007832D0@@YAXPBD@Z
void Rva007832D0(const char *name)
{
	struct Rva0046CF80Thunk
{
	void call(const char *name);
};
typedef void (Rva0046CF80Thunk::*Rva0046CF80Call)(const char *name);
	union
	{
		void (*asFunction)();
		Rva0046CF80Call asMember;
	} functionCast;
	functionCast.asFunction = j_0001df43;
	(((Rva0046CF80Thunk *)g_rva012F19E8WindowManager)->*functionCast.asMember)(name);
}

// ?Rva007832B0InvokeCallbackWithArg@@YAXPBDPAX@Z
void Rva007832B0InvokeCallbackWithArg(const char *name, void *context)
{
	g_rva012F19E8WindowManager->invokeCallbackWithArg_0046CE60(name, context);
}
