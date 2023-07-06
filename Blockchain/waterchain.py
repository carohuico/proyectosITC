import hashlib
import statistics

class Bloque:   #Clase para crear los bloques 
    def __init__(self, previo="", informacion=""):    
        self.previo = previo
        self.informacion = informacion

        #une en un mismo string los datos junto 
        self.block_data = informacion + previo #juntarlo en un mismo string
        self.block_hash = hashlib.sha256(self.block_data.encode()).hexdigest()  #genera el hash de dicho bloque
    def __str__(self):
        return f"Block hash: {self.block_hash}\n{self.informacion}\n"


print("¿Por cuantos puntos pasara el agua?")
num_pruebas = int(input())
d = [0, ]
cont_lineas = num_pruebas

for i in range(num_pruebas):
    prueba = []
    for j in range(cont_lineas):
        #llenar por prueba las 4 variables
        litros_iniciales, litros_finales, perdida_agua, velocidad_flujo = input().split()
        prueba.append([litros_iniciales, litros_finales, perdida_agua, velocidad_flujo])

    #tomar valores de cada prueba
    litros_iniciales = [float(l[0]) for l in prueba]
    litros_finales = [float(l[1]) for l in prueba]
    perdida_agua = [float(l[2]) for l in prueba]
    velocidad_flujo = [float(l[3]) for l in prueba]

    #calcular promedios
    promedio_iniciales = round(statistics.mean(litros_iniciales), 3)
    promedio_finales = round(statistics.mean(litros_finales), 3)
    promedio_perdida = round(statistics.mean(perdida_agua), 3)
    promedio_velocidad = round(statistics.mean(velocidad_flujo), 3)

    #calcular medianas
    mediana_iniciales = round(statistics.median(litros_iniciales), 3)
    mediana_finales = round(statistics.median(litros_finales), 3)
    mediana_perdida = round(statistics.median(perdida_agua), 3)
    mediana_velocidad = round(statistics.median(velocidad_flujo), 3)


    if len(litros_iniciales) > 1 or len(litros_finales) > 1 or len(perdida_agua) > 1 or len(velocidad_flujo) > 1: #si hay mas de un dato, calcular varianza y desviacion estándar
        #calcular varianzas
        varianza_iniciales = round(statistics.variance(litros_iniciales), 3)
        varianza_finales = round(statistics.variance(litros_finales), 3)
        varianza_perdida = round(statistics.variance(perdida_agua), 3)
        varianza_velocidad = round(statistics.variance(velocidad_flujo), 3)

        #calcular desviaciones estándar
        desviacion_iniciales = round(varianza_iniciales**.5, 3)
        desviacion_finales = round(varianza_finales**.5, 3)
        desviacion_perdida = round(varianza_perdida**.5, 3)
        desviacion_velocidad = round(varianza_velocidad**.5, 3)
    else:
        varianza_iniciales = 0
        varianza_finales = 0
        varianza_perdida = 0
        varianza_velocidad = 0
        desviacion_iniciales = 0
        desviacion_finales = 0
        desviacion_perdida = 0
        desviacion_velocidad = 0
    


    #guardar resultados en un string
    resultado = f"\n"
    resultado += f"Promedio de litros iniciales: {promedio_iniciales}\n"
    resultado += f"Promedio de litros finales: {promedio_finales}\n"
    resultado += f"Promedio de pérdida de agua: {promedio_perdida}\n"
    resultado += f"Promedio de velocidad de flujo: {promedio_velocidad}\n"

    resultado += f"Mediana de litros iniciales: {mediana_iniciales}\n"
    resultado += f"Mediana de litros finales: {mediana_finales}\n"
    resultado += f"Mediana de pérdida de agua: {mediana_perdida}\n"
    resultado += f"Mediana de velocidad de flujo: {mediana_velocidad}\n"

    resultado += f"Varianza de litros iniciales: {varianza_iniciales}\n"
    resultado += f"Varianza de litros finales: {varianza_finales}\n"
    resultado += f"Varianza de pérdida de agua: {varianza_perdida}\n"
    resultado += f"Varianza de velocidad de flujo: {varianza_velocidad}\n"

    resultado += f"Desviación estándar de litros iniciales: {desviacion_iniciales}\n"   
    resultado += f"Desviación estándar de litros finales: {desviacion_finales}\n"
    resultado += f"Desviación estándar de pérdida de agua: {desviacion_perdida}\n"
    resultado += f"Desviación estándar de velocidad de flujo: {desviacion_velocidad}\n"
    resultado += f"\n"

    d.append(resultado)
    cont_lineas -= 1
    print("")

bloques = []    #lista de bloques
#bloque inicial "genesis"
bloque_genesis = Bloque("Bloque génesis")
bloques.append(bloque_genesis)

for i in range (1, len(d)):
    siguiente_Bloque = Bloque(d[i], bloques[i-1].block_hash)
    bloques.append(siguiente_Bloque)
    print(siguiente_Bloque.block_data)
    print(siguiente_Bloque)
