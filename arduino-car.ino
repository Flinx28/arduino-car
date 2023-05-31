#include <Servo.h> // Incluir la libreria del servomotor, para manejar el servo (codigo ya hecho)
Servo dicembre;    // Es una instancia de la clase servo (es la forma que tengo para controlar el codigo ya hecho)
const int M1 = 2;  // De la linea 3 a la 13 estamos haciendo una declaracion de variables
const int M2 = 3;  // M2 tiene un valor de 3 que representa al pin que esta conectado (igual con el resto)
const int M3 = 4;
const int M4 = 7;
const int ENA = 5;       // Pines PWM
const int ENB = 6;       // Pines PWN
const int tig = 8;       // Disparador del ultrasonido
const int echo = 9;      // Receptor del ultrasonido
const int servo = 10;    // Señal para el servo
const int pwm = 200;     // se utiliza para establecer el valor del ancho de pulso modulado (Es el ancho de la señal analogica)
float d, t, f, der, izq; // Variables reales d=distancia, t=tiempo, f=frente, der=derecha, izq=izquierda

void setup()
{
    Serial.begin(9600);  // Baudios byte/segundos (9600) bytes en un segundo, serial begin inicializamos el uso del monitor serie
    dicembre.attach(10); // De donde sale la señal, pin 10, inicialezando el Servo, le asignamos el pin de la señal (10)
    pinMode(M1, OUTPUT); // El pinMode determinar si son salidas o entradas
    pinMode(M2, OUTPUT); // Output sale voltaje
    pinMode(M3, OUTPUT); // En las lineas 18 a 26 determinamos si esos pines van a tener señales de entrada (input) o de salida (output) en el input recibira informacion del carrito y en el output del computador
    pinMode(M4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(tig, OUTPUT);
    pinMode(echo, INPUT); // Input recibe voltaje
    pinMode(servo, OUTPUT);
    detener(); // No se mueva   //
}

void loop()
{
    calcular();
    if (f <= 15)
    {
        detener();
        delay(200);
        atras();
        delay(800);
        detener();
        calcular();
        if ((der <= 15) and (izq <= 15))
        {
            atras();
            delay(800);
        }
        else if ((der > izq) and (der > 15))
        {
            giroder();
            delay(200);
        }
        else if ((izq > der) and (izq > 15))
        {
            giroizq();
            delay(200);
        }
    }
    else if (f > 15)
    {
        adelantar();
        delay(200);
    }
}

void atras()
{
    digitalWrite(M1, LOW);  // derecha atras
    digitalWrite(M2, HIGH); // derecha adelante
    digitalWrite(M3, HIGH); // izquierd  adelante
    digitalWrite(M4, LOW);  // izquierda  atras
    analogWrite(ENA, 150);  // aqui estamos mandando x cantidad de señales a los pines que nesecitamos para el movimiento que queremos a hacer
    analogWrite(ENB, 150);
}

void detener()
{
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    digitalWrite(M3, LOW);
    digitalWrite(M4, LOW);
    digitalWrite(ENA, 150);
    digitalWrite(ENB, 150);
}

void adelantar()
{
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    digitalWrite(M3, LOW);
    digitalWrite(M4, HIGH);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
}

void giroizq()
{
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    digitalWrite(M3, LOW);
    digitalWrite(M4, LOW);
    digitalWrite(ENA, 150);
    digitalWrite(ENB, 150);
}

void giroder()
{
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    digitalWrite(M3, LOW);
    digitalWrite(M4, HIGH);
    digitalWrite(ENA, 150);
    digitalWrite(ENB, 150);
}

void lectura()
{

    digitalWrite(tig, LOW); // de la linea 98 a 102 lo que hace es poner en funcion el ultrasonido en este primero lo apagas al ultrasonido y luego lo enciendes y despues lo apagas de nuevo el delay es necesario para que le de tiempo al ultrasonido de analizar el entorno y le de tiempo de respuesta
    delayMicroseconds(4);
    digitalWrite(tig, HIGH);
    delayMicroseconds(10);
    digitalWrite(tig, LOW);
    t = pulseIn(echo, HIGH); // guardar el tiempo que tardo en llegar el pulso
    d = 0.03438 * t / 2;     // calcular la distancia
    Serial.print(d);         //
    Serial.println("cm");
}

void calcular()
{ // este es el metodo para realizar la lectura de distancia en las distintas posiciones y ademas las guarda en las variables anteriormente declaradas
    detener();
    // Lectura de la  distancia de frente
    dicembre.write(90);
    lectura();
    f = d; // f es frente, d distancia
    // Lectura de la distancia a la 180
    dicembre.write(180);
    lectura();
    der = d;
    // Lectura de la distancia a la izquierda 0
    dicembre.write(0);
    lectura();
    izq = d;
}