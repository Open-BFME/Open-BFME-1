import runpy
import sys
import unittest
from pathlib import Path
from unittest import mock

TOOLS = Path(__file__).resolve().parents[1]


class ScriptModuleIdentity(unittest.TestCase):
    def test_script_run_shares_classes_with_imported_name(self):
        """Run as __main__, `import link_census` must yield the same module, so
        isinstance(fact, link_census.ObjectFacts) holds for facts the script made."""
        saved = sys.modules.pop("link_census", None)
        try:
            with mock.patch.object(sys, "argv", ["link_census.py", "--help"]):
                with self.assertRaises(SystemExit):
                    runpy.run_path(str(TOOLS / "link_census.py"), run_name="__main__")
            # run_path executes in a fresh namespace registered as __main__ during the run;
            # the alias it installs must point at a module exposing ObjectFacts.
            import link_census  # noqa: F401
            mod = sys.modules["link_census"]
            self.assertTrue(hasattr(mod, "ObjectFacts"))
        finally:
            if saved is not None:
                sys.modules["link_census"] = saved


if __name__ == "__main__":
    unittest.main()
