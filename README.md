# Triângulo de Sierpinski

Este é um código em linguagem C que utiliza a biblioteca SDL2 para renderizar o famoso Triângulo de Sierpinski. O Triângulo de Sierpinski é uma figura fractal que pode ser construída a partir de um triângulo equilátero inicial, dividindo-o em subtriângulos menores e repetindo o processo.

## Pré-requisitos

Certifique-se de ter a biblioteca SDL2 instalada em seu sistema antes de executar o código. Você pode instalá-la usando os seguintes comandos em sistemas baseados em Debian/Ubuntu:

```bash
sudo apt-get update
sudo apt-get install libsdl2-dev
```

## Compilação e execução

Você pode compilar o código e passar a profundidade desejada diretamente na linha de comando. Por exemplo, para uma profundidade de 5, utilize o seguinte comando:

```bash
gcc sierpinski.c -o sierpinski -lSDL2
./sierpinski 5
```
Isso abrirá uma janela gráfica exibindo o Triângulo de Sierpinski com a profundidade especificada.
