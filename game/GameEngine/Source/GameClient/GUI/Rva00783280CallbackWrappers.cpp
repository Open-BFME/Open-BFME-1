// cl: /DNDEBUG /MD /EHsc
extern void j_0001df43(void);
class WindowManager
{
public:
	void invokeCallback(const char *name, void *unused);
	void invokeCallbackWithArg_0046CE60(const char *name, void *context);
	void method_0046CF80(const char *name);
};

extern WindowManager *Rva00579160TheManager;

// ?Rva00783280InvokeCallback@@YAXPBDPAX@Z
void Rva00783280InvokeCallback(const char *name, void *unused)
{
	Rva00579160TheManager->invokeCallback(name, unused);
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
	(((Rva0046CF80Thunk *)Rva00579160TheManager)->*functionCast.asMember)(name);
}

// ?Rva007832B0InvokeCallbackWithArg@@YAXPBDPAX@Z
void Rva007832B0InvokeCallbackWithArg(const char *name, void *context)
{
	Rva00579160TheManager->invokeCallbackWithArg_0046CE60(name, context);
}
