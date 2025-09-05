"""
CEC2006 Benchmark Executor

Handles execution of CEC2006 constrained optimization benchmark functions via the C implementation.
"""

import os
import subprocess
import tempfile
from pathlib import Path
from typing import List

from .base import FunctionExecutor


class CEC2006Executor(FunctionExecutor):
    """Executor for CEC2006 constrained optimization problems."""
    
    def __init__(self, implementation_dir: Path):
        self.implementation_dir = implementation_dir
        self.executable = "./main"
        
    def build(self) -> bool:
        """Build the C implementation using make."""
        try:
            subprocess.run(
                ["make", "clean"], 
                cwd=self.implementation_dir, 
                capture_output=True, 
                check=False
            )
            result = subprocess.run(
                ["make"], 
                cwd=self.implementation_dir, 
                capture_output=True, 
                check=True
            )
            return result.returncode == 0
        except subprocess.CalledProcessError:
            return False
    
    def run(self, func_id: int, dimension: int, input_vector: List[float]) -> float:
        """Execute a CEC2006 function via C binary.
        
        Note: CEC2006 functions have fixed dimensions, so the dimension parameter
        is ignored and -1 is passed to use the default dimension for each function.
        """
        with tempfile.NamedTemporaryFile(mode='w', suffix='.txt', delete=False) as f:
            for val in input_vector:
                f.write(f"{val}\n")
            temp_file = f.name
        
        try:
            # CEC2006 uses -1 for default dimension
            result = subprocess.run(
                [self.executable, str(func_id), "-1", temp_file],
                capture_output=True,
                text=True,
                cwd=str(self.implementation_dir)
            )
            
            if result.returncode != 0:
                raise RuntimeError(f"Function execution failed: {result.stderr}")
            
            return self._parse_output(result.stdout)
            
        finally:
            os.unlink(temp_file)
    
    def _parse_output(self, output: str) -> float:
        """Parse the objective value from C program output."""
        for line in output.strip().split('\n'):
            if line.startswith("Objective value = "):
                value_str = line.split("=")[1].strip()
                return float(value_str.replace("E", "e"))
        raise ValueError(f"Could not parse output: {output}")
    
    def cleanup(self) -> None:
        """No cleanup needed for C implementation."""
        pass