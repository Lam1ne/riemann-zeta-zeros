import numpy as np
import matplotlib.pyplot as plt
from mpmath import zeta
import pandas as pd

# Grid parameters
sigma_min, sigma_max = -2, 2
t_min, t_max = 0, 35
dsigma, dt = 0.01, 0.05

sigma = np.arange(sigma_min, sigma_max + dsigma, dsigma)
t = np.arange(t_min, t_max + dt, dt)
S, T = np.meshgrid(sigma, t)
Z = np.zeros_like(S, dtype=np.float64)

# Compute |zeta(sigma + it)| using mpmath
for i in range(S.shape[0]):
    for j in range(S.shape[1]):
        s = complex(S[i, j], T[i, j])
        Z[i, j] = abs(zeta(s))

# Load zeros from zeros.txt (one zero per line)
try:
    zeros_t = np.loadtxt('zeros.txt')
    if np.isscalar(zeros_t):
        zeros_t = [float(zeros_t)]
    print("Loaded zeros from zeros.txt:", zeros_t)
except Exception as e:
    zeros_t = []
    print("Could not load zeros.txt:", e)

plt.figure(figsize=(12, 6))
plt.imshow(
    np.log10(Z + 1e-12),
    extent=[sigma_min, sigma_max, t_min, t_max],
    aspect='auto',
    origin='lower',
    cmap='magma'
)
plt.colorbar(label='log10|zeta(sigma + it)|')
plt.xlabel('Re(sigma)')
plt.ylabel('Im(t)')
plt.title('Riemann Zeta Function |zeta(sigma + it)| with C++ Zeros Highlighted')

# Overlay the critical line
plt.axvline(0.5, color='cyan', linestyle='--', label='Critical line Re(s)=0.5')

# Overlay zeros from zeros.txt
for idx, zero in enumerate(zeros_t):
    plt.plot(0.5, zero, 'ro', markersize=6, label='C++ zero' if idx == 0 else "")

plt.legend()
plt.tight_layout()
plt.show()