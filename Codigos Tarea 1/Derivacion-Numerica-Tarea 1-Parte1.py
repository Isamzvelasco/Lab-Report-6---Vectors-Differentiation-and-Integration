import pandas as pd
import matplotlib.pyplot as plt

# Leer archivos generados por C++
datos = pd.read_csv("datos_derivadas.csv")
errores = pd.read_csv("errores_vs_h.csv")

# Usamos h grande para que las curvas se diferencien visualmente
h_elegido = 0.5
datos_h = datos[datos["h"] == h_elegido]


# Gráfica 1: comparación de derivadas


plt.figure(figsize=(10,6))

plt.plot(datos_h["t"], datos_h["exacta"],
         label="Exacta",
         linewidth=4)

plt.plot(datos_h["t"], datos_h["forward"],
         label="Forward",
         linestyle="--",
         linewidth=2)

plt.plot(datos_h["t"], datos_h["central"],
         label="Central",
         linestyle=":",
         linewidth=4)

plt.plot(datos_h["t"], datos_h["extrapolada"],
         label="Extrapolada",
         linestyle="-.",
         linewidth=2)

plt.xlabel("t")
plt.ylabel("Derivada")
plt.title("Comparación de derivadas para la función gaussiana, h = 0.5")
plt.legend()
plt.grid()
plt.savefig("gaussiana_derivadas.png", dpi=300)
plt.show()



# Gráfica 2: error absoluto


plt.figure(figsize=(10,6))

plt.plot(datos_h["t"], datos_h["error_forward"],
         label="Error Forward",
         linewidth=2)

plt.plot(datos_h["t"], datos_h["error_central"],
         label="Error Central",
         linewidth=2)

plt.plot(datos_h["t"], datos_h["error_extrapolada"],
         label="Error Extrapolada",
         linewidth=2)

plt.xlabel("t")
plt.ylabel("Error absoluto")
plt.title("Error absoluto para la función gaussiana, h = 0.5")
plt.yscale("log")
plt.legend()
plt.grid()
plt.savefig("gaussiana_error_t.png", dpi=300)
plt.show()


# Gráfica 3: h vs error promedio


plt.figure(figsize=(10,6))

plt.plot(errores["h"], errores["error_forward_promedio"],
         marker="o",
         label="Forward")

plt.plot(errores["h"], errores["error_central_promedio"],
         marker="o",
         label="Central")

plt.plot(errores["h"], errores["error_extrapolada_promedio"],
         marker="o",
         label="Extrapolada")

plt.xlabel("h")
plt.ylabel("Error promedio")
plt.title("Relación entre h y el error promedio")
plt.xscale("log")
plt.yscale("log")
plt.legend()
plt.grid()
plt.savefig("gaussiana_h_vs_error.png", dpi=300)
plt.show()