                                TABLA COMPARATIVA SENSORES INERCIALES (ACELERÓMETRO Y GIRÓSCOPO)
![image](https://github.com/alexx2811/redes-sensores/assets/157799271/6d2f4c9d-d242-472b-aba8-032bc7fb97cb)

Una vez analizados los tres dispositivos se llega a la conclusión de que son bastante similares, por lo que se elegirán dependiendo de las prioridades y necesidades de la aplicación. 
En general, si el presupuesto y consumo de energía son los factores más relevantes, se podría utilizar el dispositivo LSM6DSLTR cumpliendo con todos los requisitos. Por otra parte, si 
se requiere un amplio rango de aceleración y alta precisión del giróscopo, el dispositivo ASM330LHBGT1R sería el más adecuado.

Sin embargo, para esta aplicación en concreto, los tres dispositivos serían posibles candidatos para ser utilizados. 


                                        TABLA COMPARATIVA CHIPSET DE ADAPTACIÓN DE ALIMENTACIÓN
![image](https://github.com/alexx2811/redes-sensores/assets/157799271/eb84df39-ee80-4d99-8188-d93bba716083)

Para alimentar al microcontrolador y el sensor IMU se usarán 1.8V, bajando un escalón respecto a los típicos 3.3V ya que ambos permiten este nivel de alimentación. Se decide bajar ya que las pérdidas en un circuito digital son proporcionales a la tension de alimentacion (Vdd) y frecuencia de operacion (fCLK). 

Se han comparado los siguientes convertidores DC-DC de tipo Buck que cumplen con las especificaciones de rango de tensión entrada que impone la batería, y se ha elegido el XCL202B181ER-G por su precio y bajo consumo en modo reposo, que aumentará la duración de la batería. La corriente máxima que puede proporcionar (400 mA) es suficiente para el consumo del microcontrolador y el sensor IMU. Por último, al tratarse de un convertidor conmutado, su eficiencia es bastante alta (máximo 92%).
  
