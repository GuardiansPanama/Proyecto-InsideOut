 Proyecto-InsideOut

**EQUIPO GUARDIANS IPT ARNULFO ARIAS MADRID- DAVID CHIRIQUI**

**INTEGRANTES**
- JUAN MONTENEGRO
- ANGEL RIOS
- ALHANA PINEDA

  ![IMG_20241017_120232](https://github.com/user-attachments/assets/2d837fe1-5565-41c2-895f-1ab21c6b1a96)


**RESUMEN DEL PROYECTO**

NUESTRO PROYECTO SE BASA EN EL USO DE LA INTELIGENCIA ARTIFICIAL PARA EL RECONOCIMIENTO DE GESTOS DE EMOCIONES (ALEGRIA, TRISTEZA, IRA, DISGUSTO), PARA CONTROLAR LOS ROBOTS. UTILIZAMOS EL PROGRAMA DEEPFACE, UN PROGRAMA LIGERO EN PHYTON CON LA CAPACIDAD DE RECONOCER ROSTROS Y GESTOS, ENTRE ELLOS EMOCIONES, MEDIANTE EL PROGRAMA OPENCV SE PROCESA EL VIDEO EN VIVO, AL RECONOCER LA EMOCION MANDA UN COMANDO POR MEDIO DEL PROGRAMA PYSERIAL A UN CONTROLADOR ARDUINO Y ESTE MANDA LA INFORMACION A LOS DIFERENTES ROBOTS


**AGOSTO 2024**

Se tomaron las desiciones sobre el proyecto, el tema que se escogio fue la pelicula Inside-Out 2, entre las tareas pendientes:
- Construccion de la estructura de los robots
- La posibilidad de diseñar un sistema de IA que reconozca emociones como alegria, tristeza, ira para controlar los robots
- Construir todo el sistema electronico de los robots, como sistemas de control de motores, sensores y servos

** Construccion de Robots**

Se tomo la decisión de construir 3 robots para las emociones principales: Alegría, Tristeza e Ira, los materiales utilizados fue madera blanca de 3 mm y de 6mm, el diseño se hizo en el programa Inkscape, donde se vectorizo y luego se pasó al programa Lightburn para hacer el corte de las formas

![ira](https://github.com/user-attachments/assets/0278664d-e177-4d89-97c0-9d7091f8aadf)

Todas las formas se cortaron en la CNC Laser del salón de multimedia 

![IMG_20241007_095517](https://github.com/user-attachments/assets/2ee32f96-3f6f-486e-8b63-064292253769)



![IMG_20241007_100638](https://github.com/user-attachments/assets/814c65b4-c7cb-4d5e-92c4-e7852facfaed)


![IMG_20250318_131557](https://github.com/user-attachments/assets/007491a6-0945-41ea-8e43-7a6ace0f926a)


Tambien se procedio a imprimir piezas en 3D como las bases para la parte mecanica, bases de tubo de 1 pulgada para sostener las formas, cajas para la parte electronica de los robots

![IMG_20241005_120647](https://github.com/user-attachments/assets/1562888d-902d-478b-94c3-e2defdec3806)


![IMG_20250324_173958](https://github.com/user-attachments/assets/475018c2-6e28-4903-a5d0-c7ad640a30f7)


Hay que mencionar que en la pelicula cada emoción tiene su color Alegria el color amarillo, Tristeza el color azul y Ira el rojo, por eso las pirezas fueron impresas para que cada robot quedara con su color, para la impresion de todas estas piezas se uso filamento PLA

**CONSTRUCCION MECANICA**

La base de los robots Alegria e Ira se hicieron con perfiles de aluminio a los cuales se atornillaban los motores y ruedas, se le añadio una placa impresa en 3D donde se puso una base para poner un tubo de PVC de 1 pulgada, que sostiene las figuras, se usaron motores de 12v DC y controladores de motor de alta potencia, se usaron ruedas del tipo omnidireccional en la parte delantera, ya que le da una mayor movilidad al robot.

![IMG_20250322_103829](https://github.com/user-attachments/assets/eae8cb28-8068-4a89-8271-3b48224d07fe)

**FEBRERO 2025**

Se cambio base de los robots, se eliminaron los perfiles de aluminio y se cambio por una base de madera de 6mm, esto hace que la base sea mas compacta y liviana

![IMG_20250403_125326](https://github.com/user-attachments/assets/27ac8d28-8132-4322-a25d-0b9c61de829d)

![IMG_20250403_125311](https://github.com/user-attachments/assets/c5b01a92-0c6a-4fc9-8ad9-fcf9b8ffeea3)

**MARZO 2025**
  
  Se añadio nuevo robot Disgusto

  ![IMG_20250324_174041](https://github.com/user-attachments/assets/10daf45a-2ffb-4049-be8b-fc2af3cb3a25)


  Cada figura se detallo y pinto a mano, para la presentacion cada figura tiene un color:

  Alegria : Amarillo
  Tristeza: Azul
  Ira: rojp
  Disgusto : verde

  ![IMG_20250325_140325](https://github.com/user-attachments/assets/012c20cc-1f3e-4b2a-a5de-05fb68852c4a)

  ![IMG_20250322_103802](https://github.com/user-attachments/assets/583ed56c-57a3-4950-9c16-01f0266343c8)

ELECTRONICA

**Agosto 2024**

Para la parte de control de los sistemas se escogio la familia de Arduino, con el microprocesador Aduino Mega 

![mega](https://github.com/user-attachments/assets/9eabf93b-f26a-4250-8607-de0f335cad59)


Se penso en utilizar otros microcontroladores como el ESP-32, que tenian ventajas como ser mas pequeños, tienen bluehooth incorporado y  mas de poder que el Arduino Mega, pero no teniamos suficientes y quedara para mejoras futuras

![esp32_wroom_32e](https://github.com/user-attachments/assets/9ff923d9-eb95-42fa-8842-a310f0af2679)


![Presentación1](https://github.com/user-attachments/assets/69960e72-6712-4887-8808-15b40c2ec09e)





