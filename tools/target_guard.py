"""Keep explicit-target workers from accidentally operating the game ledger."""
import os
import sys


def require_game_cli(tool):
    bound = [key for key in ("BFME_TARGET", "BFME_TARGET_SHA256") if key in os.environ]
    explicit = any(arg == "--target" or arg.startswith("--target=") for arg in sys.argv[1:])
    if bound or explicit:
        reason = f"{', '.join(bound)} is set" if bound else "--target is unsupported"
        raise SystemExit(
            f"{tool}: legacy BFME1-only command refused: {reason}. "
            "For WorldBuilder use python3 tools/worldbuilder.py --help; "
            "run game work in a separate session without explicit-target bindings.")
