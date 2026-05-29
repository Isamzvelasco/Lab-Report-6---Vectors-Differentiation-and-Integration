import pandas as pd
import matplotlib.pyplot as plt

# Leer el archivo CSV 
datos = pd.read_csv("resultados_punto_medio.csv")


# Grafica 1: h vs error
plt.figure()
plt.plot(datos["h"], datos["error_punto_medio"], marker="o")
plt.xlabel("h")
plt.ylabel("Error absoluto")
plt.title("Error absoluto en función de h")
plt.grid(True)
plt.savefig("grafica_h_vs_error.png", dpi=300)
plt.show()


# Grafica 2: n vs error
plt.figure()
plt.plot(datos["n"], datos["error_punto_medio"], marker="o")
plt.xlabel("Numero de rectangulos n")
plt.ylabel("Error absoluto")
plt.title("Error absoluto en función del numero de rectangulos")
plt.grid(True)
plt.savefig("grafica_n_vs_error.png", dpi=300)
plt.show()