@page filter Filtro Digital.

@section IntroFiltro Introducción.

Un filtro digital, es un lo mismo que un filtro analogico pasa bajo, pasa banda, pasa alto... Pero con la caracteristica que trabaja con señales digitales. \n
No es mas que unas series de operaciones matematicas que toman como datos unos valores a la entrada del filtro y devuelven la misma señal modificada ampliando o atenuando ciertas caracteristicas de la señal digital.


@section AplicationFiltro Aplicaciones.
Dado que la mayoria de veces que obtenemos una señal de un sensor o simplemente transmitiendola de un dispositivo a otro, la señal que obtenemos no siempre es la que deseamos obtener, ya sea porque se le ha acoplado ruido, o interferencias de otros sistemas, o simplemente que queramos modular una señal como hacemos a diario equalizando el audio de nuestro reproductor de musica.

@subsection Separacion Separacion de señales:
Hay veces que simplemente por un mal aislamiento del cable o un campo magnetico que no sabemos que esta ahi, puede introducir ruido en la señal, por lo tanto deberemos analizar la señal, separandola en la señal originaria y el ruido, pudiendose desechar este.\n
![Separacion de señales](E:\Repositorios\Github\INSTRUMENTACION-AVANZADA\IOT\Doc_Images\fir.jpg "Separacion de Ruido")

@subsection Recuperacion Recuperacion de señales:
Cuando transmitimos una señal es deformada, para ello necesitamos desmoldearla para obtener la señal transmitida:\n
![Separacion de señales](E:\Repositorios\Github\INSTRUMENTACION-AVANZADA\IOT\Doc_Images\recuperacion1.jpg "Recuperación de Señales parte 1")
![Separacion de señales](E:\Repositorios\Github\INSTRUMENTACION-AVANZADA\IOT\Doc_Images\recuperacion2.jpg "Recuperación de Señales parte 2")

@subsection Sonido Sintesis de Sonido:
* Creacion de señales con espectros complejos a partir del filtrado de señales simples con señales simples.
* Efectos de audio (Reverb)

@section TiposFiltros Tipos de filtros.
Dada la gran cantidad de tipos de filtros, nosotros nos vamos a centrar en los filtros FIR que son los que hemos utilizado en esta practica.

@subsection FIR Filtro FIR *Finite Impulse Response* (Respuesta al Impulso Finita):
Es un tipo de filtro digital que si su entrada es un impulso (una *delta de Kronecker*) la salida será un número limitado de términos no nulos. Para obtener la salida sólo se emplean valores de la entrada actual y anteriores. También se llaman filtros digitales no-recursivos. Su expresión en el dominio discreto es:\n
![Dominio discreto FIR](E:\Repositorios\Github\INSTRUMENTACION-AVANZADA\IOT\Doc_Images\FIR-DISC.jpg "Dominio Discreto filtro FIR")
\n
El orden del filtro está dado por N, es decir, el número de coeficientes. También la salida puede ser expresada como la convolución de una señal de entrada x[n] con un filtro h[n]:\n
![Convolucion FIR](E:\Repositorios\Github\INSTRUMENTACION-AVANZADA\IOT\Doc_Images\convolucion-fir.jpg "Convolucion FIR")
\n
La estructura de un filtro FIR es la siguiente:\n
![Estructura FIR](E:\Repositorios\Github\INSTRUMENTACION-AVANZADA\IOT\Doc_Images\Estructura-FIR.jpg "Estructura FIR")
\n
la cual como podemos observar se asemeja a la transformada Z:\n
![Z FIR](E:\Repositorios\Github\INSTRUMENTACION-AVANZADA\IOT\Doc_Images\Z.jpg "Z FIR")\n
Podemos observar que es la misma entrada retardada cada vez mas en el tiempo, multiplicada por ciertos coeficientes y sumada al final. Si tenemos una respuesta en frecuencia como objetivo, conseguiremos que la respuesta del filtro se asemeje a dicha frecuencia cuanto mas coeficientes tenga.\n \n
Los *filtros FIR* son muy estables ya que solo tienen polos. Tambien tienen la ventaja que se pueden diseñar de fase lineal, por lo que no introducen desfases en la señal, a diferencia de los *filtros IIR(Infinite Impulse Response o Respuesta infinita al impulso)* o *analógicos*. \n \n
Sin embargo, tienen el inconveniente de ser más largos al tener más coeficientes que los *filtros IIR* capaces de cumplir similares características. Esto requiere un mayor tiempo de cálculo que puede dar problemas en aplicaciones en tiempo real, como estudios de grabación o conciertos en directo.\n \n
La desventaja de los *filtros IIR* la respuesta de fase es no lineal. Si la aplicación no requiere información de la fase, como una señal de monitorización, los filtros IIR podrían ser apropiados. Se deben usar los filtros FIR para esas aplicaciones que requieran respuesta de fase lineal. La naturaleza recursiva de los filtros IIR hace que sean más difíciles de diseñar e implementar. \n \n



* [Documentacion](@ref doc)
* [ESP-32](@ref ESP)
* [Lenguaje MQTT](@ref MQTT)