# Identificação

* Página do repositório do trabalho ([link GitHub](https://github.com/ninguem26/teaching)) 

* Discente 1
	* Anthony Emanoel de Albuquerque Jatobá
	* 15111580
* Discente 2
	* Júlio César Ferreira Silva de Holanda
	* 15111981

# Discussão 

## Utilização intensa da UCP

No primeiro caso, avalia-se o comportamento do programa enquanto é executado um código exigente em termos de processamento. O código, que consiste apenas de um loop infinito, mantém o processador em estado ativo durante sua execução:

```c
void consumeCPU() {
	for (;;) {}
}
```

A execução do programa com o parâmetro ```cpu``` gerou a seguinte saída:

![Saída no terminal para o primeiro experimento](images/cpu-terminal.png)

Foi gerado um gráfico com o pacote [PyPlot](https://github.com/stevengj/PyPlot.jl) para [Julia](http://julialang.org/). O gráfico permite uma melhor análise dos resultados obtidos:

![Gráfico referente ao primeiro experimento](images/cpu-plot.png)

### Uso de memória

Percebe-se que o uso de memória manteve-se constante do início ao fim da execução do código. Isso se deve ao fato de que o programa não realiza alocações de memória durante sua execução.

### Uso de UCP

Já o uso de UCP tem um comportamento mais interessante:

No instante 0 o uso da UCP pelo processo filho é de 0%, pois o mesmo ainda não executou a função ```consumeCPU()```.

Após um segundo de execução, o processador atinge a marca de aproximados 25%. O processador usado no experimento possui 4 núcleos lógicos, dos quais apenas um é completamente usado pelo programa, daí o valor.

Essa porcentagem é mantida até o final da execução, o que indica que houve poucas ou nenhuma interrupção durante a execução do programa. Caso houvesse outros processos CPU-bound em execução, o sistema operacional poderia escalonar o uso dos recursos, apresentando um comportamento distinto do apresentado.

## Utilização intensa da UCP e memória
![CPU-MEMÓRIA](src/plot CPU-MEM.png)
