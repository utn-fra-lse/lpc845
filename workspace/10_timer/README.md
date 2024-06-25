# 10_timer

Se configura el CTimer para generar interrupciones periodicas de 250 ms.

El LED rojo se conecta al evento de match 0 del CTimer para conmutarlo a esa frecuencia.

En el callback del match del CTimer se conmutan el LED verde y el LED azul cada dos y cuatro interrupciones.
