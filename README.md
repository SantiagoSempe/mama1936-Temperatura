# Repositorio con programa ejemplo en C para PIC16F887 {#mainpage}
Para trabajar con el compilador XC8 v2.10 con MPLABX IDE v5.30
## Módulos ya disponibles
Nombre|Descripción
------|-----------
`uart`|Permite el manejo del puerto serie
`display`|Permite el manejo de un display de 7 segmentos
`tick`|Permite utilizar el contador de Tick para temporizaciones

Manual del PIC [PIC16F882/883/884/886/887 Data Sheet](https://ww1.microchip.com/downloads/en/DeviceDoc/40001291H.pdf)

## Datos del alumno :nerd_face:
Completa con tus datos la siguiente tabla:
Campo|Detalle
------|-----------
Nombre| Nnnn
Apellido| Aaaa
Curso| 6°Electrónica
Año| 20XX

## Programación con demoras por Contador de Tick
El objetivo de este TP es lograr la implementación varias demoras que funcionen simultáneamente y en forma no bloqueante utilizando las funciones que trabajan con el contador de Tick que se incrementa por interrupción.

## Pautas del TP :man_teacher:
Los siguientes puntos se deben resolver en forma individual codificando en C para que los programas obtenidos corran en el Circuito con PIC para TP. Se debe bajar al microcontrolador el firmware obtenido al compilar y luego realizar físicamente las pruebas funcionales para verificar que cumpla con lo pedido en cada enunciado. También se debe entregar este repositorio en GitHub

# TPSE06: Demoras por Contador de Tick :timer_clock:
## 1. Demoras por Contador de Tick ⏳
- [ ] Defina las etiquetas y constantes necesarias, inicialice entradas, salidas y los periféricos necesarios
- [ ] Codifica un programa principal muy simple que en su super lazo y en forma no bloqueante cada 600mS cuente del 1 a 4 en el display 7 segmentos volviendo a repetir indefinidamente
- [ ] También cada vez que cambia el display, destelle el led rojo (prenda y lego de 200mS vuelva a apagar en forma no bloqueante)
- [ ] En forma independiente a lo anterior toglee el led verde 1 vez por segundo indicando que la aplicación esta en marcha (Heaert Beat)
- [ ] al terminar esta parte identifícalo con commit: `punto1 listo`
## 2. Medición de Intervalo con contador de Tick ⏱
- [ ] Modifica el programa principal para que también mida el tiempo que transcurre entre que se presiona la tecla 1 y que se presiona la tecla 2, y guarde el resultado obtenido en la variable `tGolpe`. Recuerda al comienzo, inicializar esta variable en 600
- [ ] Si este tiempo que se esta midiendo luego de presionar la tecla 1, ya supera los 5 segundos descarta la medición
- [ ] Modifica para que el tiempo entre cuentas del display y destellos del led rojo, ahora sea igual al almacenado en la variable `tGolpe`
- [ ] También mida el tiempo que transcurre entre que se presiona la tecla 3 y que se presiona la tecla 4, y guarde el resultado obtenido en la variable `tToggle`, recuerda iniciarla en 1000
- [ ] Si este tiempo que se esta midiendo luego de presionar la tecla 3, ya supera los 5 segundos también descarta la medición
- [ ] Modifica para que toglee el led verde luego de transcurrido el tiempo almacenado en la variable `tToggle`
