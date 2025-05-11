 Proyecto-InsideOut

**EQUIPO GUARDIANS IPT ARNULFO ARIAS MADRID- DAVID CHIRIQUI**

**INTEGRANTES**
- JUAN MONTENEGRO

 ![juan](https://github.com/user-attachments/assets/fb4ba51b-489d-49df-bdb0-fb9c558fa154)


- ANGEL RIOS

 ![angel](https://github.com/user-attachments/assets/49f96b38-90ad-4c52-8be2-0aa33cfc2696)

- ALHANA PINEDA

  ![alhana (1)](https://github.com/user-attachments/assets/5d7390e0-ac7b-42d5-9c84-e68c2db1f929)


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

![3d (1)](https://github.com/user-attachments/assets/ab8b0ce8-3bac-40f1-bd8d-199703edefb0)



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


Diagrama de funcionamiento


![Presentación1](https://github.com/user-attachments/assets/69960e72-6712-4887-8808-15b40c2ec09e)

El funcionamiento de los  cuatro sistemas es muy parecido, la informacion que viene de los sistemas de comunicacion o de los sensores es enviada al Arduino que procesa esta informacion, enviando comandos los controladores de motor que hacen mover a las ruedas y dirigen los movimientos del robot.

![IMG_20250404_140245](https://github.com/user-attachments/assets/88aab5d5-4bd4-48b7-b610-1338ca91c082)

![IMG_20250403_125347](https://github.com/user-attachments/assets/5a435580-555c-4ced-9ffb-1c70fad7ac01)


Se utilizan motores REV son muy confiables y de alta potencia

![rev](https://github.com/user-attachments/assets/e2bc18ad-0849-4a4c-8dcd-675133eb4416)

En los robots Felicidad y Tristeza los comandos se reciben mediante el sistema de comunicacion, Ira y Desagrado se manejan mediante el uso de sensores y son autonomos

El sistema de comunicación utilizado es el DIGI Xbee, tiene muchas ventajas sobre el Bluethoot, como mayor alcance, estabilidad, conexion automatica sin necesidad de emparejamiento, la desventaja es que tenemos solo 4 sistemas, lo que limita la cantidad de robots que podemos conectar.

![XBEE](https://github.com/user-attachments/assets/9784618b-7fba-4cca-9ec6-bc02bce4116b)


**ROBOT IRA**

Para el movimiento del robot Ira se utilizo un sensor de vision con Inteligencia Artificial DFROBOT Huskilens, se utiliza em dos modos, reconocimiento de cara y deteccion de coordenadas del objeto.

![huskylens](https://github.com/user-attachments/assets/764633aa-19f7-486e-a88e-03b8ba9daf82)


Diagrama de Funcionamiento

![huskilens](https://github.com/user-attachments/assets/f3a69412-d70f-4fb3-a841-67304d68f6ca)

El robot Ira funciona con un programa de seguimiento de objeto, si la cara que ve la camara corresponde con la cara guardada en la memoria el sistema, empieza el programa de seguimiento de objeto, se busca las coordenadas horizontal y vertical donde esta el objeto, estas coordenadas con el valor X pueden decir si el objeto esta a la derecha o a la izquierda, la posicion en Y nos puede decir la altura del objeto, un objeto mas alto esta cerca, un objeto mas pequeño esta mas alejado, toda esa información es procesada por el Arduino Mega, este manda los comandos a los controladores de motores y esto hace que el robor siga al objeto

![IMG_20250509_133730](https://github.com/user-attachments/assets/12c1f47d-817a-4542-bcc1-224ccb0ee1dc)


**ROBOT DISGUSTO**

Este robot tambien se diseño con un sistema de navegacion autonoma, utilizando un programa de seguimiento de objeto, en este caso usando un detector de distancia, al principio se uso un sensor de distancia de ultrasonido, pero despues se probo con un sensor LIDAR  TinyLIDAR, este utiliza un LASER, en practica se observo que es muy exacto y mas pequeño que un sensor de ultrasonido, se coloco en un servo, en el programa se toman lecturas de distancia a 0 , 90 y 180 grados, si detecta objetos a 0 grados, gira a la izquierda, si detecta un objeto a 90 grados sigue de frente y si detecta un objeto a 180 grados gira a la izquierda, si el objeto esta a menos de 300 mm el robot retrocede.


![tinyLIDAR](https://github.com/user-attachments/assets/a83ae3c5-4d70-4a57-95bc-b136be1836df)

Diagrama de Funcionamiento


![desagrado cuadro](https://github.com/user-attachments/assets/64204a93-0a1d-4d57-8353-47e52d8432cf)


![IMG_20250430_172807](https://github.com/user-attachments/assets/9108add2-1612-4688-9226-46c2753acaa7)

Sensor LIDAR TinyLidar

![IMG_20250430_172816](https://github.com/user-attachments/assets/c02ef8f8-fd36-4ee4-8eb5-6d0cb00e0710)

Montaje de LIDAR en Servo


**Robot Alegría**

El robot Alegría esta controlado por el Sistema de Reconocimiento de Emociones SRE, tiene comunicacion inalambrica por medio de Xbee, su principal controlador es un Arduino Mega,con controladores de motor de alta potencia, las ruedas delanteras son Omnidireccionales para mayor presición y agilidad en los movimientos.

![IMG_20250509_133827](https://github.com/user-attachments/assets/5447de26-39bc-4800-b65a-c67d436a5baf)

![IMG_20250509_133832](https://github.com/user-attachments/assets/73518b2f-1e1a-460c-bb8f-988fcc4b1bc3)

Montaje de Servos

![alegria](https://github.com/user-attachments/assets/06a160b8-c053-4986-b8f7-7141ef6e0cba)

Robot Tristeza

A diferencia de los demas robots, Tristeza utiliza un sistema de 3 ruedas omnidireccionales, utiliza 3 controladores de motor conectado a un Arduino Mega, controlando la rotacion de cada motor de puede lograr que se mueva hacia adelante, atras, horizontal y diagonal. La comunicación es mediante Xbee con el SRE.

![tristeza](https://github.com/user-attachments/assets/8833464f-df31-4161-acbd-90496b206fd8)

