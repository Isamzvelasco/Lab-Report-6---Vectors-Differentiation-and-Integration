import pandas as pd
import matplotlib.pyplot as plt

# Leer archivos generados por C++
datos = pd.read_csv("datos_segunda_derivada.csv")
errores = pd.read_csv("errores_vs_h_segunda.csv")

# Elegimos un valor de h
h_elegido = 0.1

# Filtrar datos para ese h
datos_h = datos[datos["h"] == h_elegido]

# GRÁFICA 1:
# Segunda derivada exacta vs numérica


plt.figure(figsize=(10,6))

# Exacta
plt.plot(
    datos_h["t"],
    datos_h["exacta"],
    label="Exacta",
    linewidth=4,
    color="blue"
)

# Numérica
plt.plot(
    datos_h["t"],
    datos_h["segunda_derivada"],
    label="Segunda derivada numérica",
    linestyle="--",
    linewidth=3,
    color="red"
)

plt.xlabel("t")
plt.ylabel("Segunda derivada")
plt.title("Comparación de segunda derivada para h = 0.1")

plt.legend()
plt.grid()

plt.savefig("segunda_derivada_comparacion.png", dpi=300)

plt.show()


# GRÁFICA 2:
# Error absoluto


plt.figure(figsize=(10,6))

plt.plot(
    datos_h["t"],
    datos_h["error"],
    label="Error absoluto",
    linestyle="-.",
    linewidth=3,
    color="green"
)

plt.xlabel("t")
plt.ylabel("Error absoluto")

plt.title("Error absoluto de la segunda derivada para h = 0.1")

# Escala logarítmica
plt.yscale("log")

plt.legend()
plt.grid()

plt.savefig("segunda_derivada_error.png", dpi=300)

plt.show()


# GRÁFICA 3:
# h vs error promedio


plt.figure(figsize=(10,6))

plt.plot(
    errores["h"],
    errores["error_promedio"],
    marker="o",
    linestyle="--",
    linewidth=2,
    markersize=8,
    color="purple",
    label="Error promedio"
)

plt.xlabel("h")
plt.ylabel("Error promedio")

plt.title("Relación entre h y el error promedio")

# Escalas logarítmicas
plt.xscale("log")
plt.yscale("log")

plt.legend()
plt.grid()

plt.savefig("segunda_derivada_h_vs_error.png", dpi=300)

plt.show()