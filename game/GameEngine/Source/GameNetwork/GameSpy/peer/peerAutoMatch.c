// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy
/* GameSpy Peer SDK -- peerIsAutoMatching, retail 0x00858120, 26 bytes,
   reconstructed from the retail bytes; the declarations are local for the same
   reason peerHost.c's next door are.

   The identification is not a guess.  The body reads exactly one member,
   [peer+0x18d4], and peerCallbacks.c reaches that same slot from
   piAddAutoMatchStatusCallback, where its value becomes the params of a
   PI_AUTO_MATCH_STATUS callback -- so the member is the auto-match status and
   this predicate is "is an auto-match still running".  The constant it
   compares against is 5, the last of the six PEERAutoMatchStatus values, which
   is what makes the comparison a completion test rather than an arbitrary one.

   A zero status returns straight out on the register the load left, without a
   fresh zeroing: retail's `ret` at 0x0085812E is that path.  */

typedef void *PEER;

typedef enum
{
	PEERFalse,
	PEERTrue
} PEERBool;

typedef enum
{
	PEERFailed,
	PEERSearching,
	PEERWaiting,
	PEERStaging,
	PEERReady,
	PEERComplete
} PEERAutoMatchStatus;

typedef struct piConnection
{
	unsigned char pad0[0x18d4];
	PEERAutoMatchStatus autoMatchStatus;		/* +0x18D4 */
} piConnection;

PEERBool peerIsAutoMatching(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if(!connection->autoMatchStatus)
		return PEERFalse;

	return (PEERBool)(connection->autoMatchStatus != PEERComplete);
}
