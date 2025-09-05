"""
CEC Benchmark Executors Package

Provides executor implementations for different CEC benchmark years.
Each executor handles the specific interface and requirements of its year's benchmark suite.
"""

from .base import FunctionExecutor, TestType
from .cec2005 import CEC2005Executor
from .cec2006 import CEC2006Executor
from .factory import ExecutorFactory

__all__ = [
    'FunctionExecutor',
    'TestType', 
    'CEC2005Executor',
    'CEC2006Executor',
    'ExecutorFactory'
]