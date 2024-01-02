# Trabajo Practico - Page Rank

_Este trabajo fue realizado por alumnos de Metodos Numéricos_

## Despliegue 📦

El codigo que resuelve el problema se encuentra en la carpeta /codigo del directorio fuente, en el archivo main.cpp

Para correr los experimentos es necesario primero compilar el codigo fuente de las implementaciones de los algoritmos. Para ello dejamos preparado un Makefile que se encarga de hacer la compilación con optimización. Para ejecutarlo se ejecuta por consola dentro del directorio /codigo:
```
make
```

Para realizar la ejecución del mismo se debe tener presente que hay que enviarle al programa 2 parametros:
* archivo: es la ruta del archivo .txt de la matriz
* p: es el valor p (probabilidad) que se usará en la ejecución del algoritmo para el calculo del ranking

De esta forma, un ejemplo para correr el programa viene a ser:
```
./page_rank ./test_matriz.txt 0.5
```

## Ejecución de los notebooks ⚙️
Una vez compilado el programa y tener el ejecutable tenemos que moverlo a la carpeta python del proyecto.
Para ello, si estamos en el directorio /codigo entonces ejecutamos desde consola el siguiente comando:
```
cp page_rank ./../python
```

Para la ejecución de los notebooks, es recomendable utilizar un entorno virtual. El código de python usado para la experimentación de este proyecto fue compilado usando `Python 3.8.0`
La creación del entorno se puede realizar utilizando los comandos:
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

## Expresiones de Gratitud 🎁

* ¡Que lo disfruten! 📢
