# Computation and Visualization of Non-Trivial Zeros of the Riemann Zeta Function

This project allows you to:
- Numerically compute non-trivial zeros of the Riemann zeta function on the critical line using an optimized C++ program (Riemann-Siegel formula).
- Visualize the zeta function in the complex plane and overlay the computed zeros using a Python script.

## Usage

### 1. Compute Zeros (C++)

Compile:
```sh
g++ -O3 -fopenmp riemann_zero.cpp -o riemann_zero.exe
```

Run with default parameters:
```sh
./riemann_zero.exe
```

Or specify interval, step, and tolerance:
```sh
./riemann_zero.exe <t_start> <t_end> [step] [tolerance]
```
Example:
```sh
./riemann_zero.exe 14 30 0.005 1e-15
```
The found zeros are saved in `zeros.txt` and Z(t) values in `zeta_plot.csv`.

### 2. Visualization (Python)

Install dependencies:
```sh
pip install numpy matplotlib mpmath pandas
```

Run the visualization script:
```sh
python zeta_2d_with_zeros.py
```
This script displays a color map of |ζ(s)| in the complex plane and marks the zeros computed in C++ on the critical line.

## Main Files

- `riemann_zero.cpp`: Computes zeros and exports CSV.
- `zeta_2d_with_zeros.py`: Advanced visualization in Python.
- `.gitignore`: Ignores generated and temporary files.

## Notes

- Computation off the critical line is done in Python (mpmath library).
- The C++ code uses only standard libraries for portability and mathematical clarity.