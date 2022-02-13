# ¿Qué Probabilidad Hay?
Juego con Arduino, display LCD y 7 segmentos. Enlace a la presentación: https://www.youtube.com/watch?v=yWKSluvfk8g

------------

# Miembros
- Jerry Landívar
- Sebastián Ruiz
- Jorge Herrera
- Gabriel Anton

------------

## Detalles

------------

### Descripción del proyecto:
El dispositivo permite experimentar el juego de azar ¿Qué probabilidad hay? Desde el punto de vista del funcionamiento, el dispositivo permite al usuario seleccionar un número mediante 3 pulsadores que a través de un decodificador BCD a 7segmentos permite mostrar en un display de 7 segmentos el número seleccionado, asi mismo el Arduino selecciona un numero aleatorio correspondiente a un lanzamiento de dado que se muestra en otro display de 7 segmentos. Finalmente, el Arduino compara ambos números y si estos son iguales se asigna un reto aleatorio que se muestra en el display LCD, caso contrario indica en el display LCD que no se debe realizar el reto.

### Lista de materiales

| Nombre            | Cantidad    | Precio (c/u) | Imagen|
|:-------------------:|:-------------:|:---------------:|:--------------:|
| Arduino Nano   | 1   | $5             | ![Arduino Nano](https://340ebb34-0a2d-4f84-89c1-df7c55751e77.id.repl.co/imgPartes/Arduino%20Nano.png "Arduino Nano")         |
| Decodificador BCD a 7 segmentos (7448)         | 2       | $1             | ![Decodificador BCD a 7 segmentos (7448)](https://340ebb34-0a2d-4f84-89c1-df7c55751e77.id.repl.co/imgPartes/Decodificador%20BCD%20a%207%20segmentos.png "Decodificador BCD a 7 segmentos (7448)")        |
| Cable jumper de 13 pines 20cm | 1 | $2            | ![Cable jumper de 13 pines 20cm](https://340ebb34-0a2d-4f84-89c1-df7c55751e77.id.repl.co/imgPartes/Cable%20jumper%20de%2013%20pines%2020%20cm.png "Cable jumper de 13 pines 20cm")        |
| Cables machos hembra          | 4  | $2             | ![Cables machos hembra](https://340ebb34-0a2d-4f84-89c1-df7c55751e77.id.repl.co/imgPartes/Cables%20machos%20hembra.png "Cables machos hembra")            |
| Display 7 segmentos          | 2  | $1.50             | ![Display 7 segmentos](https://340ebb34-0a2d-4f84-89c1-df7c55751e77.id.repl.co/imgPartes/Display%207%20segmentos.png "Display 7 segmentos")            |
| Display LCD  I2C     | 1  | $7             |  ![Display LCD](https://340ebb34-0a2d-4f84-89c1-df7c55751e77.id.repl.co/imgPartes/Display%20LCD.png "Display LCD")           |

### Posibles mejoras:
- Soldar parte del circuito en una baquelita para evitar errores debido a contactos de mala calidad en la protoboard.
- Procurar que el diseño final sea rápido y sencillo de desmontar para mostrar las conexiones internas de manera didáctica.
- Añadir una característica inclusiva para las personas con problemas de vista, por ejemplo, que suene una cantidad de veces respecto al número que sale.
- Que se pueda configurar el rango numérico para los distintos tipos de juegos u otros ambientes en los que se emplee la aleatoriedad.
- Mejorar el diseño para que sea más atractivo a la vista y de esta manera llame el interés de los usuarios.

### Resumen de contenido:

El código funciona mediante una sucesión de 3 estados dentro del loop: pantalla de inicio, selección de número y pantalla final. En cada iteración del loop, se ejecuta únicamente un solo estado. Esto permite la lectura constante de los botones para así poder responder inmediatamente a la acción del usuario.
```cpp
void loop(){
  if (state == 0) {  // Código de la pantalla de inicio
  }
  else if (state == 0) {  // Código mostrar pregunta y seleccionar número
  }
  else if (state == 0) {  // Código de la pantalla de inicio
  }
}
```

Para detectar el accionamiento de un botón sin contarlo repetidas veces, se utilizó una variable boolena para cada botón que permite responder solamente cuando el botón es SOLTADO (flanco de bajada).
```cpp
if (digitalRead(pinBtn)){
  btn = true;
} else if (btn){
  btn = false;
  // Aquí va el código que se ejecuta al soltar el botón
}
```

Para no usar siempre la misma semilla del random se utilizó la librería time.h
```cpp
srand(time(NULL));
```

| Conexiones de la placa  | Placa  | Prototipo completo  |
| :------------: | :------------: | :------------: |
| ![Conexiones de la placa](https://imagenes-que-probabilidad-hay.jorgeshn28.repl.co/imgCircuito/Conexiones%20de%20la%20placa.jpg "Conexiones de la placa")  | ![Placa](https://imagenes-que-probabilidad-hay.jorgeshn28.repl.co/imgCircuito/Placa.jpg "Placa")  | ![Prototipo completo](https://imagenes-que-probabilidad-hay.jorgeshn28.repl.co/imgCircuito/Prototipo%20completo.jpg "Prototipo completo")  |

En el display LCD se visualizará un reto de los que estén en la memoria del programa y también si debe cumplir el reto o no.
El display de 7 segmentos que tiene 2 pulsadores a su lado será el que el usuario use para escoger un número entre 0 y 9, un pulsador sumará y el otro restará una unidad al número que se visualice.
El display de 7 segmentos que tiene un solo pulsador a su lado es en el que se visualizará un número escogido aleatoreamente.
Del lado contrario a los pulsadores se encuentran los decodificades BCD (Binary Coded Decimal) a 7 segmentos, lo que permite es como su nombre lo dice, decodificar el número binario lanzado por el programa y este se muestre eel número decimal en el display de 7 segmentos.
El programa compara los números y finalmente si estos son iguales se mostrar en el display LCD que el usuario debe cumplir el reto, caso contrario se ostrará que no lo debe cumplir.
