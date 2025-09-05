"""
Factory for creating CEC benchmark executors.
"""

from pathlib import Path
from typing import Dict, Type

from .base import FunctionExecutor
from .cec2005 import CEC2005Executor
from .cec2006 import CEC2006Executor


class ExecutorFactory:
    """Factory for creating year-specific executors."""
    
    _executors: Dict[int, Type[FunctionExecutor]] = {
        2005: CEC2005Executor,
        2006: CEC2006Executor,
        # Add more years as implemented:
        # 2007: CEC2007Executor,
        # 2008: CEC2008Executor,
        # 2009: CEC2009Executor,
    }
    
    @classmethod
    def create_executor(cls, year: int, implementation_dir: str) -> FunctionExecutor:
        """Create an appropriate executor for the CEC year.
        
        Args:
            year: The CEC year (e.g., 2005, 2006)
            implementation_dir: Path to the implementation directory
            
        Returns:
            A FunctionExecutor instance for the specified year
            
        Raises:
            ValueError: If no executor is implemented for the specified year
        """
        executor_class = cls._executors.get(year)
        if not executor_class:
            raise ValueError(f"No executor implemented for CEC{year}")
        
        return executor_class(Path(implementation_dir))
    
    @classmethod
    def register_executor(cls, year: int, executor_class: Type[FunctionExecutor]) -> None:
        """Register a new executor for a specific year.
        
        This allows dynamic registration of new executors without modifying this file.
        
        Args:
            year: The CEC year
            executor_class: The executor class to register
        """
        cls._executors[year] = executor_class
    
    @classmethod
    def supported_years(cls) -> list[int]:
        """Get list of supported CEC years.
        
        Returns:
            Sorted list of years with implemented executors
        """
        return sorted(cls._executors.keys())