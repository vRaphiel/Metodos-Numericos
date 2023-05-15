# Trabajo Practico - Analisis de redes

_Este trabajo fue realizado por alumnos de Metodos Numéricos_

## Despliegue 📦

El codigo que resuelve el problema se encuentra en la carpeta /codigo del directorio fuente, en el archivo main.cpp

Para correr los experimentos es necesario primero compilar el codigo fuente de las implementaciones de los algoritmos. Para ello dejamos preparado un Makefile que se encarga de hacer la compilación con optimización. Para ejecutarlo se ejecuta por consola dentro del directorio /codigo:
```
make
```

Para realizar la ejecución del mismo se debe tener presente que hay que enviarle al programa 3 parametros:
* archivo: es la ruta del archivo .txt de la matriz
* iteraciones: la cantidad de iteraciones a realizar en el método de la potencia
* tolerancia: la tolerancia mínima que podemos aceptar, es un valor entre 0 y 1

De esta forma, un ejemplo para correr el programa viene a ser:
```
./metodo_potencia ./test_matriz.txt 10000 0.0001
```

Como output se van a obtener 2 archivos que tendrán en su nombre el del archivo que le pasamos para analizar. Ejemplo:
* test_matriz.txt-autovalores.out
* test_matriz.txt-autovectores.out

## Ejecución de los notebooks ⚙️
Una vez compilado el programa y tener el ejecutable tenemos que moverlo a la carpeta python del proyecto.
Para ello, si estamos en el directorio /codigo entonces ejecutamos desde consola el siguiente comando:
```
cp metodo_potencia ./../python
```

Para la ejecución de los notebooks, es recomendable utilizar un entorno virtual. El código de python usado para la experimentación de este proyecto fue compilado usando `Python 3.8.0`
Se recomeinda iniciar la creación del entorno desde la carpeta Python para que pueda ejecutarse todo correctamente: La creación del entorno se puede realizar utilizando los comandos:
```
pip install virtualenv
python -m virtualenv entorno
```
Desde Linux:
```
source entorno/bin/activate
```
Desde Windows
```
entorno/Scripts/activate
```
Cabe destacar que para el desarrollo de los notebooks se utilizó Jupyter.
Dentro del entorno ejecutamos:
```
pip install -r /path/to/requirements.txt
```
Y con ello tendremos todas las bibliotecas usadas para la ejecución de los notebooks. Para finalizar se levanta el entorno de jupyter utilizando
```
jupyter-notebook
```

Con todo esto, ya podemos hacer las pruebas necesarias.

El notebook experimentacion-metodo-potencia contiene distintas instancias de evaluación sobre el método con varias iteraciones y valores de convergencia.
El notebook analisis-matrices contiene todo el estudio realizado para el analisis del informa.

## Expresiones de Gratitud 🎁

* ¡Que lo disfruten! 📢
