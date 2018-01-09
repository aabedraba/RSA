# Implementación del algoritmo RSA
Una implementación profunda de RSA en C++. Digo profunda porque implemento la mayoría de las funciones en lugar de usar las disponibles en 
las diferentes librerías. Esto se ha hecho así para que se pueda tener un ejemplo de cómo se implementaría cada paso, desde la obtención de
los números primos a usar con las claves hasta la encriptación por bloques.

## Motivación
Esta implementación es parte de un ejercicio de las prácticas de Seguridad en mi universidad. Mi profe, Manuel Lucena, me dijo que me pondría
un diez si hago una buena implementación, así que iré informando de si me ha puesto o no el diez :P

## Diseño
Tenemos tres clases cuyos métodos iré explicando uno a uno a continuación:

### Números primos
En esta clase se generan los números primos que después se utilizarán para la obtención de las claves públicas y privadas. He preferido
hacerlo en una clase aparte para que se pueda tener una idea clara de cómo se generan los números primos de gran longitud (en este caso
utilizo primos de longitud en el rango de 1024bits).

Para comprobar que un número es o no primo, habría que comprobar que no sea divisible por todos los primos menores que ese número.
Para ello, tendría que guardar todos los números primos que hay por debajo de ese número en una lista e ir comprobando uno por uno.
En el caso de números pequeños, sería relativamente manejable. Pero como en este caso los números son de 1024 bits (aproximadamente una
cifra de 700 dígitos) guardar todos los números primos sería imposible y en caso de poder guardarse en un disco duro, a palabras de mi profesor, éste podría hacer que un agujero negro colapse. 

Poooor lo tanto, hay que hacer una comprobación probabilística, en lugar de determinista, de si un número es o no probable de ser primo, valga la redundancia.

Para poder hacerlo se ha decidido utilizar el test de **Miller-Rabin**, que reduce a una magnitud aceptable la probabilidad de que un número no sea primo. Sin embargo, el test de Miller-Rabin es poco eficiente y hacer muchas comprobaciones no sería lo más adecuado. 

Por ello hago una lista de todo los números primos que hay en el rango [2, 1000]. Comprobando que mi número no sea divisible por esa lista hace que aumente la probabilidad al 90% de que el número eligido sea primo. Por lo tanto con esto y con una pocas iteraciones del test de Miller-Rabin, conseguimos hacer eficiente la determinación probabilística de que un número aleatorio de tamaño grande no sea primo.

El test de Miller-Rabin reduce la probablidad en el orden de 4^-k , siendo k el número de iteraciones que se realizan de este test. Por tanto, junto con el 90% que ya hemos descartado, 10 iteraciones de este test hacen que la probabilidad de que un número no sea primo sea de **99.9999915736%**. Enough.

En el código se puede ver la implementación del test usando GMP, lo cual lo hace un poco-bastante menos legible.

### Claves
La clase de claves tiene la implementación trivial de la generación de claves de RSA. Aunque en la parte de calcular d (la inversa de e módulo phi) he utilizado una función implementada en GMP para su resolución ya que mi implementación del *Método de Euclides* implicaba una recursividad y GMP no tiene soporte para ello, por ahora. 



**En desarrollo...**
### RSA
Este proyecto tiene una rama donde estoy trabajando en cifrar y descifrar archivos de texto.