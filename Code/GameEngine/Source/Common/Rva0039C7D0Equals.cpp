// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// This wrapper asks the same owner to compare its argument with the payload
// beginning eight bytes into the object.  Keeping the worker as a member is
// material: retail preserves the incoming this pointer in ecx for the call.
struct Rva0039C7D0Payload
{
	unsigned char m_storage;
};

class Rva0039C7D0Owner
{
public:
	bool equals(const Rva0039C7D0Payload &other) const;

private:
	bool compare(const Rva0039C7D0Payload *left,
		const Rva0039C7D0Payload *right) const;

	unsigned char m_prefix[8];
	Rva0039C7D0Payload m_payload;
};

bool Rva0039C7D0Owner::equals(const Rva0039C7D0Payload &other) const
{
	return compare(&m_payload, &other);
}
