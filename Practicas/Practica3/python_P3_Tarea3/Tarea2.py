import serial


def main():
    # Configura el puerto serie, ajusta el nombre del puerto y la velocidad (baudrate) según tu configuración
    puerto_serie = serial.Serial('COM7', 9600)  # Reemplaza 'COM1' con el nombre de tu puerto serie

    try:
        print("Leyendo datos en tiempo real desde el puerto serie...")
        while True:
            # Lee un línea de datos desde el puerto serie
            linea = puerto_serie.readline().decode('utf-8').strip()

            # Muestra la línea de datos en la pantalla
            print(linea)

    except KeyboardInterrupt:
        # Maneja la interrupción del teclado (Ctrl+C) para cerrar el puerto serie correctamente
        print("Cerrando el programa...")
        puerto_serie.close()


if __name__ == "__main__":
    main()
