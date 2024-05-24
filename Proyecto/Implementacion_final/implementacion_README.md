Para diseñar el diagrama de flujo, se ha partido de una gráfica que representa el movimiento dónde se identifican los distintos tramos para llevar a cabo el ejercicio (subir, mantener y bajar).
A la hora de identificar los diferentes movimientos, ha sido necesario añadir unas posiciones intermedias (umbrales) para detectar los movimientos de subida y bajada. 

![grafica puntillas](https://github.com/alexx2811/redes-sensores/assets/157799271/7fc89c1c-644b-4dc4-b0a1-98d8f3c3a5e9)

Finalmente, quedaría añadir un estado de procesado, antes de pasar al estado de reposo, encargado de realizar todos los cálculos de tiempos (subida, bajada, total) y ángulos (máximo, mínimo y medio). 

A continuación, se muestra el diagrama de flujo que se ha implementado en el código de arduino: 
![diagrama flujo](https://github.com/alexx2811/redes-sensores/assets/157799271/cbf2d412-003b-4e98-aaa1-e1f507cd2797)
