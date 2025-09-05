"""
Base classes and common types for CEC benchmark executors.
"""

from abc import ABC, abstractmethod
from enum import Enum
from pathlib import Path
from typing import List, Optional


class TestType(Enum):
    """Types of test vectors for validation."""
    MIN = "min"
    MAX = "max"
    OPTIMAL = "optimal"
    ZEROS = "zeros"
    RANDOM = "random"


class FunctionExecutor(ABC):
    """Abstract base class for CEC function executors."""
    
    @abstractmethod
    def __init__(self, implementation_dir: Path):
        """Initialize the executor with implementation directory."""
        pass
    
    @abstractmethod
    def build(self) -> bool:
        """Build the implementation if necessary."""
        pass
    
    @abstractmethod
    def run(self, func_id: int, dimension: int, input_vector: List[float]) -> float:
        """Execute a benchmark function and return the result."""
        pass
    
    @abstractmethod
    def cleanup(self) -> None:
        """Cleanup any resources."""
        pass