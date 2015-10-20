#Instruções para o uso

##Compilação e execução

Dentro do diretório no qual se situa o código-fonte, executar o seguinte comando:

```gcc -pthread -o main main.c```

Para executar o código, executar o seguinte comando: 

```./main <arg>```

Sendo arg um dos dois possíveis parâmetros:
--```cpu```: alto uso de processamento
--```cpu-mem```: alto processamento e memória;

##Instalação do Julia e PyPlot

Para usar as funcionalidades de gráficos, é necessário ter as ferramentas Julia e PyPlot instaladas.

###[Julia](julialang.org)

```
sudo add-apt-repository ppa:staticfloat/juliareleases
sudo add-apt-repository ppa:staticfloat/julia-deps
sudo apt-get update
sudo apt-get install julia
```

###[Matplotlib](http://matplotlib.org/)

A bibliteca [Matplotlib](http://matplotlib.org/) é necessária para a geração dos gráficos. O sistema usado para o desenvolvimento (Ubuntu 14.04.3) já possui a biblioteca, mas caso seja necessária a instalação: 

  ```sudo apt-get install python-matplotlib```

###[PyPlot](https://github.com/stevengj/PyPlot.jl)

Dentro do terminal interativo Julia, executar o seguinte comando:

```Pkg.add("PyPlot")```

Após a configuração, o programa pode ser executado como no primeiro tópico.
