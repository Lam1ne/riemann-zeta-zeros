import numpy as np
import matplotlib.pyplot as plt

# Load data
data = np.genfromtxt('zeta_plot.csv', delimiter=',', names=True)
t = data['t']
Zt = data['Zt']

# Load zeros
zeros = np.loadtxt('zeros.txt')

plt.figure(figsize=(12,6))
plt.plot(t, Zt, label='Z(t)', color='blue')
plt.axhline(0, color='black', linewidth=0.8)

# Highlight zeros
for zero in zeros:
    plt.axvline(zero, color='red', linestyle='--', alpha=0.5)
    plt.plot(zero, 0, 'ro')

plt.title('Riemann-Siegel Z(t) along the critical line')
plt.xlabel('t')
plt.ylabel('Z(t)')
plt.legend()
plt.tight_layout()
plt.show()