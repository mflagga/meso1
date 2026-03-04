import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

dane = np.loadtxt('psi.dat')

tu = np.unique(dane[:,0])

cwd = Path.cwd()
frame_dir = cwd / "frames"
frame_dir.mkdir(parents=True, exist_ok=True)

plt.figure(figsize=(8,6))

n=0

for t in tu:
    mask = dane[:,0]==t
    plt.plot(dane[mask,1],dane[mask,2])
    #plt.tight_layout()
    plt.title(f't={t:.3f}')
    filename = frame_dir / f"frame_{n:04d}.png"
    n+=1
    plt.savefig(filename)
    plt.clf()
plt.close()