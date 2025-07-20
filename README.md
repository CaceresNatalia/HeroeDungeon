# HeroeDungeon
Juego de consola C++

Trabajo Práctico: Juego de Batalla por Turnos 
Objetivo: Aplicar los conceptos de Programación Orientada a Objetos (POO) 
desarrollando un juego sencillo de batalla por turnos entre un Héroe (controlado por el 
jugador) y un Enemigo (controlado por la computadora). 
Requisitos del juego: 

1. Clase Heroe: 
○ El nombre del héroe debe ser ingresado por el usuario. 
○ El héroe debe tener atributos como: salud, ataque, defensa y nivel. 
○ El héroe puede tener una lista de objetos que mejoran su ataque o defensa 
(por ejemplo: espada, escudo, pociones). 
○ Debe tener un método para atacar al enemigo y otro para recibir daño. 
○ Al ganar un combate, el héroe sube de nivel, y debe mostrarse un mensaje 
de victoria personalizado con su nombre. 

2. Clase Enemigo: 
○ El enemigo también debe tener atributos de salud, ataque y defensa. 
○ Pueden existir distintos tipos de enemigos (con diferentes estadísticas). 
○ Debe poder atacar y recibir daño al igual que el héroe. 

3. Sistema de Batalla: 
○ Se juega por turnos: primero ataca el héroe, luego el enemigo (o viceversa). 
○ El daño infligido debe considerar el ataque del atacante y la defensa del 
defensor. 
○ El combate continúa hasta que uno de los dos quede sin salud. 

4. Extra / Bonus (opcional): 
○ Agregar distintos niveles de dificultad. 
○ Implementar un sistema de objetos consumibles (como pociones que se usan 
durante la batalla). 
○ Guardar estadísticas de victorias/derrotas. 

Requisitos Técnicos: 
● Utilizar los conceptos de POO: clases, atributos, métodos, encapsulamiento, 
herencia (si agregan clases como EnemigoFinal o MiniJefe), y polimorfismo si 
hay variantes de comportamiento. 
