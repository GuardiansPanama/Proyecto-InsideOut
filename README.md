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



**PROJECT SUMMARY**

OUR PROJECT IS BASED ON THE USE OF A  SYSTEM WITH ARTIFICIAL INTELLIGENCE FOR THE RECOGNITION OF EMOTIONAL GESTURES (HAPPINESS, SADNESS, ANGER, DISGUST), WHICH CONTROLS THE ROBOTS AND THE SHOW. USING THE OPENCV PROGRAM, THE LIVE VIDEO IS PROCESSED, WITH GOOGLE MEDIA PIPE WE IDENTIFY FACES, WE USE THE DEEPFACE PROGRAM, A LIGHTWEIGHT PROGRAM IN PHYTON WITH THE ABILITY TO RECOGNIZE GESTURES. WHEN RECOGNIZING THE EMOTION, IT SENDS A COMMAND THROUGH THE PYSERIAL PROGRAM TO AN ARDUINO CONTROLLER, AND THIS SENDS INSTRUCTIONS THROUGH AN XBEE SYSTEM TO THE DIFFERENT ROBOTS TO EXECUTE THE PRESENTATION. THE SYSTEM IT ALSO SYNCHRONIZES THE VIDEO THAT IS PRESENTED, THE ROBOTS ALSO HAVE FUNCTIONS SUCH AS FACE RECOGNITION, GESTURE RECOGNITION AND OBJECT TRACKING.


**AUGUST 2024**

Decisions were made regarding the project. The theme chosen was the movie Inside-Out 2. Among the pending tasks:

* Building the robot structure
* The possibility of designing an AI system that recognizes emotions such as joy, sadness, and anger to control the robots
*Building the entire electronic system for the robots, such as motor control systems, sensors, and servos

**Robot Construction**

The decision was made to build three robots for the main emotions: Joy, Sadness, and Anger. The materials used were 3 mm and 6 mm white wood. The design was created in Inkscape, where it was vectorized and then transferred to Lightburn to cut the shapes.

![ira](https://github.com/user-attachments/assets/0278664d-e177-4d89-97c0-9d7091f8aadf)

All shapes were cut on the workshop's CNC Laser.

![IMG_20241007_095517](https://github.com/user-attachments/assets/2ee32f96-3f6f-486e-8b63-064292253769)



![IMG_20241007_100638](https://github.com/user-attachments/assets/814c65b4-c7cb-4d5e-92c4-e7852facfaed)


![IMG_20250318_131557](https://github.com/user-attachments/assets/007491a6-0945-41ea-8e43-7a6ace0f926a)

3D parts were also printed, such as the bases for the mechanical part and boxes for the electronic part of the robots.
![3d (1)](https://github.com/user-attachments/assets/ab8b0ce8-3bac-40f1-bd8d-199703edefb0)



![IMG_20241005_120647](https://github.com/user-attachments/assets/1562888d-902d-478b-94c3-e2defdec3806)


![IMG_20250324_173958](https://github.com/user-attachments/assets/475018c2-6e28-4903-a5d0-c7ad640a30f7)


It should be mentioned that in the film each emotion has its color: Joy is yellow, Sadness is blue, and Anger is red, which is why the pieces were printed so that each robot had its own color. PLA filament was used to print all these pieces.
**CONSTRUCCION MECANICA**

The base of the robots  were made with aluminum profiles to which the motors and wheels were screwed, a 3D printed plate was added where a base was placed to put a 1-inch PVC pipe, which holds the figures, 12v DC motors and high-power motor controllers were used, omnidirectional wheels were used in the front, since it gives greater mobility to the robot.

![IMG_20250322_103829](https://github.com/user-attachments/assets/eae8cb28-8068-4a89-8271-3b48224d07fe)

**FEBRUARY 2025**


The base of the robots was changed, the aluminum profiles were removed and replaced with a 6mm wooden base, this makes the base more compact and lighter.
![IMG_20250403_125326](https://github.com/user-attachments/assets/27ac8d28-8132-4322-a25d-0b9c61de829d)

![IMG_20250403_125311](https://github.com/user-attachments/assets/c5b01a92-0c6a-4fc9-8ad9-fcf9b8ffeea3)

**MARCH 2025**
  
Added new  robot: DISGUST
  ![IMG_20250324_174041](https://github.com/user-attachments/assets/10daf45a-2ffb-4049-be8b-fc2af3cb3a25)


Each figure was detailed and hand-painted. For presentation, each figure has a different color:

Happiness: Yellow
Sadness: Blue
Anger: Red
Disgust: Green

  ![IMG_20250325_140325](https://github.com/user-attachments/assets/012c20cc-1f3e-4b2a-a5de-05fb68852c4a)

  ![IMG_20250322_103802](https://github.com/user-attachments/assets/583ed56c-57a3-4950-9c16-01f0266343c8)

ELECTRONICA

**AUGUST 2024**


For the control part of the systems, the Arduino family was chosen, with the Aduino Mega microprocessor.
![mega](https://github.com/user-attachments/assets/9eabf93b-f26a-4250-8607-de0f335cad59)

We considered using other microcontrollers like the ESP-32, which had advantages such as being smaller, having built-in Bluetooth and more power than the Arduino Mega, but we didn't have enough and it will be for future improvements.
![esp32_wroom_32e](https://github.com/user-attachments/assets/9ff923d9-eb95-42fa-8842-a310f0af2679)



Operation diagram

![Presentación1](https://github.com/user-attachments/assets/69960e72-6712-4887-8808-15b40c2ec09e)

The operation of the four systems is very similar: the information coming from the communication systems or sensors is sent to the Arduino, which processes this information, sending commands to the motor controllers that make the wheels move and direct the robot's movements.

![IMG_20250404_140245](https://github.com/user-attachments/assets/88aab5d5-4bd4-48b7-b610-1338ca91c082)

![IMG_20250403_125347](https://github.com/user-attachments/assets/5a435580-555c-4ced-9ffb-1c70fad7ac01)



REV 12 VOLT MOTORS are used, they are very reliable and high power.
![rev](https://github.com/user-attachments/assets/e2bc18ad-0849-4a4c-8dcd-675133eb4416)


In the Happiness and Sadness robots, commands are received through the communication system; Anger and Disgust are managed through sensors and are autonomous.

The communication system used is the DIGI Xbee. It has many advantages over Bluetooth, such as greater range, stability, and automatic connection without the need for pairing. The disadvantage is that we only have four systems, which limits the number of robots we can connect.
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

SOFTWARE

Todos los robots estan programados en el IDE de Arduino, el Sistema de Reconocimiento de Emociones S.R.E esta programado en Phyton

El SRE es el software que mas ha tenido desarrollo y trabajo, el programa utiliza OpenCV para procesar la señal de video que llega de una camara en tiempo real, Mediante Google Media Pipe se identifica un rostro y utilizando la libreria de emociones de Deepface se identifica la emoción, se manda un comando serial por medio del app Pyserial que conecta con un Arduino y luego este envia un mensaje por un sistema inalambrico Xbee a los diferentes robots

![programa](https://github.com/user-attachments/assets/fee273e5-a8ed-499b-a788-c1c52027076b)


El programa se ejecuta desde una computadora ya que requiere ciertas caracteristicas de hardware, minimo un procesador I3 con 8Gb de RAM

![sre](https://github.com/user-attachments/assets/0e831f4b-197f-43d5-8a88-d4907936d69c)


