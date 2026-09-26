// cl: /DNDEBUG /MD /EHsc
class WindowManager
{
public:
	void invokeCallback(const char *name, void *unused);
	void invokeCallbackWithArg_0046CE60(const char *name, void *context);
};

extern WindowManager *Rva00579160TheManager;

// ?Rva00783280InvokeCallback@@YAXPBDPAX@Z
void Rva00783280InvokeCallback(const char *name, void *unused)
{
	Rva00579160TheManager->invokeCallback(name, unused);
}

// ?Rva007832B0InvokeCallbackWithArg@@YAXPBDPAX@Z
void Rva007832B0InvokeCallbackWithArg(const char *name, void *context)
{
	Rva00579160TheManager->invokeCallbackWithArg_0046CE60(name, context);
}
