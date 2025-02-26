# Trabajo Practico - Eliminación Gausseana

_Este trabajo fue realizado por alumnos de Metodos Numéricos_

## Despliegue 📦

El codigo que resuelve el problema se encuentra en la carpeta python, en el notebook experimentos.

## Ejecución de los notebooks ⚙️
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

El proyecto se compone de 3 archivos:
- Generar Instancias
- Experimentos
- Análisis

Si se desea se pueden generar las instancias corriendo el notebook entero de generar instancias.
Para hacer las pruebas se ejecuta el notebook experimentos. En la sección de los experimentos llamada Ejercicio 4 se puede elegir cuales de las instancias generadas ejecutar, en relación a la carpeta donde han sido creadas. Estas son:
- 4a: "tr_edd", "tr_random", "tr_sdp"
- 4b: "tr_edd_l", "tr_random_l", "tr_sdp_l"

Se coloca o quita la carpeta del arreglo de casos.

Una vez generados los experimentos, los valores resultantes se guardan en archivos CSV en la carpeta _resultados_, luego, si se ejecuta el notebook análisis se cargan primero los CSV y luego se generan los gráficos correspondientes.

## Expresiones de Gratitud 🎁

* ¡Que lo disfruten! 📢
