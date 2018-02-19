\maketitle

# Introdução
Este documento pretende descrever de forma sucinta, mas completa, um projeto laboratorial para a unidade curricular de Eletrónica IV. Neste documento será descrita a proposta do projeto, incluíndo os seus objetivos, funcionalidades previstas e uma breve descrição da implementação. Será ainda indicada uma lista dos materiais necessários e discutido o enquadramento do projeto com os conteúdos programáticos de Eletrónica IV.

# Autores
A seguinte proposta é elaborada pelos alunos da turma prática P5:

|Nome           |  Nº mec |   Email            |
|:--------------|:-------:|:------------------:|
|André Gradim   | 76476   | a.gradim@ua.pt     |
|Pedro Martins	 | 76374	  | martinspedro@ua.pt |

: Dados dos alunos

# Descrição sumária do projeto
O projeto a desenvolver é um robô com tração às 2 rodas e com um _ball caster_ como terceiro ponto de apoio. Este robô terá como principais objetivos a capacidade de se deslocar de forma precisa num ambiente plano e localizar-se relativamente ao meio que o rodeia. Estas duas funcionalidades permitir-lhe-ão a resolução de labirintos semelhantes aos do concurso ["Micro-Rato"](http://microrato.ua.pt/)[^1], nos moldes definidos para a competição realizada anualmente na Universidade de Aveiro.

O robô possuirá dois modos de funcionamento distintos:

1. Resolução de um labirinto autónomamente
2. Modo telecomando

No 1º modo, o robô será totalmente autónomo, não possuindo comunicação para o exterior. Autonomamente deverá localizar-se num labirinto semelhante aos do concurso "Micro-Rato", descobrir o farol e deslocar-se até ele, voltando de seguida para a sua posição de partida.

No 2º modo, o robô deverá permitir ser controlado remotamente por um comando infravermelhos, quer recebendo coordenadas para onde se deslocar, quer recebendo instruções genéricas, tais como: `andar para a frente`, `virar à direita`, `parar`, etc.


## Funcionalidades
O robô deverá incluir as seguintes funcionalidades

- Deslocar-se segundo um dos eixos coordenados
- Rodar em torno do seu centro geométrico[^2]
- Mapear o espaço envolvente, caso esteja inserido num labirinto com as condições da competição "Micro-Rato"
- Monitorizar a sua bateria
- Detetar obstáculos
- Monitorizar e atuar caso os motores entrem em _stall_

# Implementação

## Estrutura Mecânica
A estrutura mecânica, a ser construída, terá a forma circular e permitirá suportar toda a estrutura de locomoção, as baterias, os vários sensores e o sistema do robô (microcontrolador + circuitos eletrónicos envolventes).

Na figura \ref{up_view} é apresentado um esboço da estrutura mecânica do robô, sendo também identificadas as várias zonas funcionais do robô (rodas, sistema, sensores e bateriais) e o seu posicionamento relativo[^3].

Como mostra a figura, na lateral do robô serão colocadas duas rodas e na sua traseira um _ball caster_. As duas rodas serão movimentadas usando motores DC (com _encoders_ e _extended shaft_) eserão responsáveis pela locomoção do robô, enquanto o ball caster servirá como ponto extra de apoio.

\begin{figure}
\centering
\includegraphics[width=0.5\textwidth]{images/robot_up_view.png}
\caption{Divisão estrutural dos vários componentes do robô, vista de cima. BC são as iniciais de \textit{Ball Caster}}
\label{up_view}
\end{figure}

## Instrumentação
Como demonstra a figura \ref{up_view}, serão utilizados 5 sensores de _Time of Flight (TOF)_. Estes sensores serão colocados estrategicamente na superfície lateral do robô para, através dos dados adquiridos, permitirem a reconstrução de um ambiente 2D adequado ao posicionamento relativo do robô dentro de um espaço delimitado por paredes, semelhante a um labirinto do concurso "Micro-Rato".

Para além dos sensores de TOF, será ainda utilizado um sensor de linha, posicionado na parte inferior da frente do robô, com a função de detetar uma zona preta na superfície onde o robô se desloca, que simboliza o farol[^4]. 

Serão ainda utilizados, apesar de não representados no esboço (figura \ref{up_view}), um giroscópio/acelerómetro, um sensor IR e um sensor de luminosidade. 

O giroscópio/acelerómetro será integrado num módulo capaz de indicar a posição absoluta do robô relativamente à sua posição inicial. O sensor de IR será utilizado para implementar o controlo remoto do robô e o sensor de luminosidade servirá para melhorar a qualidade das leituras efetuadas pelos sensores de TOF.


## Módulo de Distribuição de Potência
O robô incorporará a sua própria fonte de energia, usando baterias LIPO. Adjacente a este módulo (não representado na figura) existirá um circuito de distribuição de potência, que será responsável por fornecer as diferentes tensões e correntes necessárias aos vários módulos existentes no robô.

Adicionalmente serão também implementados três circuitos de proteção/monitorização:

1. Circuito de proteção contra curto-circuito na alimentação do circuitos de baixa potência
2. Monitorização da tensão da bateria;
3. Proteção contra _stall_ dos motores

## Módulo de Comunicação 
O robõ possuirá as seguintes plataformas de comunicação:

1. Comando IV _(apenas no modo de funcionamento 2)_
2. Porta Série (entre o computador e o micro-controlador)
3. LEDs (em ambos os modos, providenciando _feedback_ visual)


## Módulo de Locomoção

## Módulo de Localização


# Material Necessário

# Enquadramento com os Objetivos da UC



[^1]: À data da elaboração deste documento, 18 de Fevereiro de 2018, o site oficial do Micro-Rato da Universidade de Aveiro encontra-se _offline_.

[^2]: A rotação segundo o centro geométrico do robô poderá não ser exata, devendo ser considerada uma rotação aproximada em torno do seu centro geométrico.

[^3]: Esta imagem deve ser analisada considerando que representa apenas um esboço da estrutura do robô, com o intuito de facilitar a visualização dos assuntos descritos no texto. A imagem não deve ser entendida como uma versão preliminar da estrutura, mas apenas como uma "ideia" do que poderá virá a ser.

[^4]: O farol representa a meta, sendo o fim do labirinto, num labirinto semelhante aos usados na competição "Micro-Rato", nas condições em que é realizada na Universidade de Aveiro,
