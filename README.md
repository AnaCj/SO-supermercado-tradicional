# supermercado-tradicional

### Declaramos las variables globales:
- Dos de tipo int, para contar el número de cajas y el número de clientes.
- Un array dinámico de cajas de tipo pthread.
- Un array dinámico de int para el tiempo de espera de clientes.

### Programa principal (función main): 
Primero declaramos las variables:
- Una de tipo int como contador.
- Un array dinámico para los identificadores de los clientes.
- Un array dinámico de threads que serán los clientes.
- Tres de tipo float para calcular la desviación típica, la media y un auxiliar.

Si el número de argumentos es 2 significa que solo nos han pasado el número de cajas y por lo tanto el número de clientes deberá ser 20 veces mayor.

Si el número de argumentos es 3 asignamos el valor a las variables. Si no es ninguno de eso casos mostrara por pantalla un error.

Reservamos memoria para los arrays dinámicos.

Inicializamos el array de mutex (la cola de cada caja del supermercado).

Entramos en un bucle para crear los threads que serán los clientes, que van a realizar la función cliente.

Sincronizamos los threads. Destruimos los mutex.

Inicializamos la variable media y la calculamos sacando los valores del tiempo de espera del array de espera de clientes y dividiendo la suma entre el número de clientes.

Se inicializa la variable desviación y se calcula. Liberamos la memoria que habíamos reservado.

Para finalizar se imprime un mensaje mostrando que el supermercado se ha cerrado, otro mostrando el tiempo medio de espera y otro para la desviación típica.
   
### Función que ejecutaran los threads( cliente):
Primero declaramos las variables:
- Cuatro variables de tipo int, una para la caja a la que irá el cliente, otra para el identificador del cliente, y dos para los cálculos del tiempo de espera.

Creamos una semilla con la hora del ordenador para que sea más aleatorio el uso de rand(). Imprimimos por pantalla que el cliente está comprando.

Hacemos que espere un tiempo mientras compra y le asignamos una caja aleatoria. Inicializamos una variable con el tiempo de inicio.

Imprimimos por pantalla que al cliente se le ha asignado una caja.

Entramos en la sección crítica.

El cliente hace un lock del mutex de la caja a la que se le ha asignado si puede, si no espera.

Cuando ya ha hecho lock, inicializamos una variable con el tiempo que ha esperado.

Imprimimos que el cliente ha sido atendido, por lo tanto estará en una caja pagando. El tiempo que espera es aleatorio.

Tras esperar se calcula el tiempo que ha esperado en la cola y se guarda en el array dinámico de espera_clientes.

Después se imprime que el cliente a salido después de esperar el tiempo calculado anteriormente.

Liberamos el mutex de la caja de ese cliente para que el siguiente pueda hacer uso de la caja. Y salimos de la sección crítica.
