// cl: /DNDEBUG /MD /EHsc
// The vendored GameWindowTransitions.h has the Zero Hour class layout; the
// BFME caller TU blocks it because that layout differs. This provider needs
// only the opaque pointer type, whose exact spelling is established by the
// matched GameWindowManager caller and the upstream definition.
class GameWindowTransitionsHandler;

GameWindowTransitionsHandler *TheTransitionHandler = 0;
