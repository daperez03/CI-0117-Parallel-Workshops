# Ejemplo 16. Exclusión mutua con semáforos [sem_mutex]

Agregue semáforos al pseudocódigo siguiente para forzar a que los incrementos
en los hilos se hagan con exclusión mutua.
	
```
procedure main:
  shared count := 0
  create_thread(thread_a)
  create_thread(thread_b)
end procedure

procedure thread_a:
  count := count + 1
end procedure

procedure thread_b:
  count := count + 1
end procedure
```

Corrija la red de Petri para que los incrementos se realicen con exclusión mutua.

![img1](https://jeisson.ecci.ucr.ac.cr/concurrente/2022b/material/taskc/sem_mutex/sem_mutex_given.pnml)

