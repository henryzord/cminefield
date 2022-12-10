# C Minefield

Seu objetivo neste trabalho é implementar o jogo [campo minado](https://pt.wikipedia.org/wiki/Campo_minado) na linguagem 
de programação C.

Você pode ver o funcionamento do jogo neste link: https://campo-minado.com/

O trabalho deverá ser apresentado ao professor. Durante a apresentação, o processo de desenvolvimento do código-fonte
será discutido. Você será solicitado a fazer pequenas modificações no código-fonte, de maneira que o comportamento do 
jogo seja alterado, e será perguntado dos motivos que levaram a estas alterações.

Portanto, é **fortemente desaconselhado** copiar o código-fonte do jogo campo minado da Internet. Trabalhos plagiados
terão sua nota reduzida à zero.


## Requisitos

Abaixo estão elencados os requisitos obrigatórios e opcionais do jogo campo minado, bem como a nota que será dada para
cada um dos itens, caso sejam completados.

### Obrigatórios

#### Requisitos funcionais

* [ ] O tamanho do mapa do jogo é variável
* [ ] O número de linhas do mapa pode ser diferente do número de colunas
* [ ] O mapa possui minas
* [ ] O jogo se encerra quando o jogador acerta uma mina (condição de derrota)

#### Requisitos não-funcionais

* [ ] As coordenadas foram implementadas usando `struct`
* [ ] As células foram implementadas usando `struct`
* [ ] **Nenhuma função foi utilizada** (todo o código deve estar na função `main`)

### Opcionais

#### Requisitos funcionais

* [ ] É garantido que a primeira jogada não resultará em uma mina
* [ ] O algoritmo de descoberta de mapa foi implementado
* [ ] Um relógio foi implementado
* [ ] O mapa é colorido
* [ ] O algoritmo que calcula quantas minas existem perto de uma célula foi implementado
* [ ] O jogo se encerra quando o jogador descobriu todas as células que **não** possuem minas (condição de vitória)

#### Requisitos não-funcionais

* [ ] Um `enum` foi utilizado para decidir o tipo da célula (se é mina ou se é campo)
* [ ] Um tipo foi detinido a partir da `struct` de coordenadas
* [ ] Um tipo foi detinido a partir da `struct` de células