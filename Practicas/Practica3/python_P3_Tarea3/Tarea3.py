import serial
import csv

def main():
    # Configura el puerto serie, ajusta el nombre del puerto y la velocidad (baudrate) según tu configuración
    puerto_serie = serial.Serial('COM7', 9600)  # Reemplaza 'COM1' con el nombre de tu puerto serie

    # Abre un archivo para escribir los datos
    with open('../datos_puerto_serie.csv', 'w', newline='') as archivo:
        try:
            print("Leyendo datos en tiempo real desde el puerto serie y guardándolos en datos_puerto_serie.txt...")
            while True:
                writer = csv.writer(archivo)
                # Lee un línea de datos desde el puerto serie
                linea = puerto_serie.readline().decode('utf-8').strip()
                datossensor = linea.split(';')
                # Muestra la línea de datos en la pantalla
                print(linea)

                # Escribe la línea de datos en el archivo
                writer.writerow(datossensor)

        except KeyboardInterrupt:
            # Maneja la interrupción del teclado (Ctrl+C) para cerrar el puerto serie y el archivo correctamente
            print("Cerrando el programa y guardando los datos...")
            puerto_serie.close()


if __name__ == "__main__":
    main()
