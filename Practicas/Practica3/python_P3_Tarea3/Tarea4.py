import serial
import csv
import time
import statistics
import matplotlib.pyplot as plt

def main():
    # Configura el puerto serie, ajusta el nombre del puerto y la velocidad (baudrate) según tu configuración
    puerto_serie = serial.Serial('COM7', 9600)

    # Variables para acumular datos
    datosX_acumulados = []
    datosY_acumulados = []
    datosZ_acumulados = []
    tiempo_inicio = time.time()
    tiempo_limite = 10  # 10 segundos

    # Variables para graficar en tiempo real
    tiempos = []
    promediosX = []
    promediosY = []
    promediosZ = []
    desviacionesX = []
    desviacionesY = []
    desviacionesZ = []
    desviacionesX.append(0)
    desviacionesY.append(0)
    desviacionesZ.append(0)

    try:
        print("Acumulando datos durante 5 segundos y representando el promedio y la desviación estándar en tiempo real...")

        while (time.time() - tiempo_inicio) < tiempo_limite:
            # Lee un línea de datos desde el puerto serie
            linea = puerto_serie.readline().decode('utf-8').strip() #UTF-8 String
            datossensor= linea.split(';') #separa los datos de linea detectando ;

            #if (len(datossensor) > 2): #poner solo si se lee 0 indeseados por el puerto serie

            # Convierte la línea a un número
            datoX = float(datossensor[0])
            datoY = float(datossensor[1])
            datoZ = float(datossensor[2])

            # Muestra la línea de datos en la pantalla
            print(linea)

            # Acumula los datos
            datosX_acumulados.append(datoX)
            datosY_acumulados.append(datoY)
            datosZ_acumulados.append(datoZ)

            # Obtiene el tiempo actual
            tiempo_actual = time.time()

            # Actualiza las listas
            tiempos.append(tiempo_actual - tiempo_inicio)
            promedioX_actual = statistics.mean(datosX_acumulados)
            promedioY_actual = statistics.mean(datosY_acumulados)
            promedioZ_actual = statistics.mean(datosZ_acumulados)
            promediosX.append(promedioX_actual)
            promediosY.append(promedioY_actual)
            promediosZ.append(promedioZ_actual)
            if( len(datosX_acumulados) >=2):
                desviacionX_actual = statistics.stdev(datosX_acumulados)
                desviacionY_actual = statistics.stdev(datosY_acumulados)
                desviacionZ_actual = statistics.stdev(datosZ_acumulados)
                desviacionesX.append(desviacionX_actual)
                desviacionesY.append(desviacionY_actual)
                desviacionesZ.append(desviacionZ_actual)



            # Grafica en tiempo real
            plt.plot(tiempos, promediosX, label='PromedioX')
            plt.plot(tiempos, promediosY, label='PromedioY')
            plt.plot(tiempos, promediosZ, label='PromedioZ')
            plt.plot(tiempos, desviacionesX, label='DesviaciónX')
            plt.plot(tiempos, desviacionesY, label='DesviaciónY')
            plt.plot(tiempos, desviacionesZ, label='DesviaciónZ')
            plt.xlabel('Tiempo (s)')
            plt.ylabel('Valor')
            plt.legend()
            plt.pause(0.1)  # Pausa para actualizar la gráfica

        # Imprime el promedio y la desviación final
        print(f'\nPromedioX: {promedioX_actual}')
        print(f'\nPromedioY: {promedioY_actual}')
        print(f'\nPromedioZ: {promedioZ_actual}')
        #print(f'Desviación estándar final: {desviacion_estandar_actual}')

    except KeyboardInterrupt:
        # Maneja la interrupción del teclado (Ctrl+C) para cerrar el puerto serie y la gráfica correctamente
        print("\nCerrando el programa...")
        puerto_serie.close()
        plt.show()

if __name__ == "__main__":
    main()
