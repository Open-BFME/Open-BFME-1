// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift PropagandaTowerBehavior dtor __emit thunk to clean C++.
// Retail destroys the member subobject at this+0x18 under an SEH frame, then
// runs the inlined base dtor (base vtable store) on the normal and unwind
// paths. The derived class emits no vtable store of its own.

class PropagandaTowerBehaviorMember
{
public:
    ~PropagandaTowerBehaviorMember();
};

class PropagandaTowerBehaviorBase
{
public:
    virtual ~PropagandaTowerBehaviorBase() {}

private:
    unsigned char m_pad[0x14];
};

class __declspec(novtable) PropagandaTowerBehavior : public PropagandaTowerBehaviorBase
{
public:
    virtual ~PropagandaTowerBehavior();

private:
    PropagandaTowerBehaviorMember m_18;
};

// ??1PropagandaTowerBehavior@@UAE@XZ
PropagandaTowerBehavior::~PropagandaTowerBehavior()
{
}
