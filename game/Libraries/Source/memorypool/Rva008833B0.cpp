// cl: /DNDEBUG /MD
// Retail008833B0 is a single RET, followed by15 INT3 bytes. The matched
// C70EB0 forwarding caller loads ECX=0130EA10 and jumps here. Retain its
// existing opaque callee identity; this is not the distinct275B tracker
// destructor at00883220 and does not acquire that destructor's name.
class Gen_00C70EB0Target
{
public:
    void bfmeForward();
};
void Gen_00C70EB0Target::bfmeForward() {}
