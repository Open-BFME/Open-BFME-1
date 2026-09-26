// cl: /O2 /DNDEBUG /MD
// The carved body returns its this pointer without reading object state.

class Rva0075B220Self
{
public:
    void *identity();
};

void *Rva0075B220Self::identity()
{
    return this;
}
