"""Example module that adds two integers in C++."""

import os
import typing

if not typing.TYPE_CHECKING and os.getenv("PYBIND11_PROJECT_PYTHON_DEBUG"):
    from ._pyRTSS_d import *  # noqa: F403
    from ._pyRTSS_d import __version__  # noqa: F401, RUF100
else:
    from ._pyRTSS import *  # noqa: F403
    from ._pyRTSS import __version__  # noqa: F401, RUF100
