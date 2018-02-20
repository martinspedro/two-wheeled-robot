\maketitle

# Introdução
Este documento pretende descrever de forma sucinta, mas completa, um projeto laboratorial para a unidade curricular de Eletrónica IV. Neste documento será descrita a proposta do projeto, incluindo o seu objetivo, funcionalidades previstas e uma breve descrição da sua implementação. Será ainda indicada uma lista dos materiais necessários e discutido o enquadramento do projeto com os conteúdos programáticos de Eletrónica IV.

# Descrição sumária do projeto
O projeto a desenvolver consiste num robô com tração às 2 rodas e com um _ball caster_[^1] como terceiro ponto de apoio. Este robô terá como principal objetivo a capacidade de se deslocar em 2 dimensões num ambiente controlado, sem embater em nenhum obstáculo.

## Funcionalidades
O robô deverá possuir as seguintes funcionalidades: 

- Deslocar-se segundo um dos seus eixos coordenados;
- Rodar em torno do seu centro geométrico[^2];
- Detetar obstáculos;
- Monitorizar e atuar caso os motores entrem em _stall_;
- Comunicação com o computador, usando uma interface por linha série.

# Implementação
 
## Estrutura Mecânica
A estrutura mecânica, a ser construída, terá a forma circular e permitirá suportar toda a estrutura de locomoção, as baterias, os vários sensores e o sistema do robô (microcontrolador + circuitos eletrônicos envolventes).

Na figura \ref{up_view} é apresentado um esboço da estrutura mecânica do robô, sendo também identificadas as várias zonas funcionais do mesmo (rodas, sistema, sensores e baterias), bem como o seu posicionamento relativo[^3].

Como mostra a figura, na lateral do robô serão colocadas as duas rodas e na sua traseira um _ball caster_. As duas rodas serão movimentadas usando motores DC com _encoders_. Estes motores serão responsáveis pela locomoção enquanto o ball caster servirá como ponto extra de apoio.

A estrutura terá no máximo as dimensões de $30 cm \times 30 cm \times 30 cm$

\begin{figure}[H]
\centering
\includegraphics[width=0.5\textwidth]{images/robot_up_view.png}
\caption{Divisão estrutural dos vários componentes do robô, vista de cima.}
\label{up_view}
\end{figure}

Na figura \ref{up_view}, os números representam as seguintes entidades funcionais.

1. Espaço dedicado à implementação do sistema (microcontrolador +  circuitos eletrónicos envolventes);
2. Botões de _start_ e _stop_, usados para controlar o funcionamento do robô;
3. Bateria;
4. O _ball caster_;
5. Rodas e o seu sistema de fixação ;
6. Os 5 sensores de obstáculos que usam tecnologia _time of flight_.

## Visão global do funcionamento do sistema
O diagrama de instrumentação de nível 0 é apresentado na imagem \ref{diagram0}.

O funcionamento do robô pode ser descrito, de forma sucinta, da seguinte forma: primeiro, o robô recebe comandos do utilizador, tais como, distância a percorrer, velocidade, direção e sentido do movimento, e posteriorment à sua interpretação, irá atuar nos motores para realizar a ação especificada. 

Além disso, ao longo de todo o processo, irá proporcionar _feedback_ do estado da sua operação de forma luminosa (LEDs) e por mensagem para o utilizador, usando a interface pc-microcontrolador.

![Diagrama de blocos de nível 0\label{diagram0}](images/diagram_level_0.png)

## Instrumentação
O diagrama de blocos de nível 1 pode ser consultado na imagem \ref{diagram1}. Neste diagrama são identificados os sensores previstos para este projeto e os atuadores. Os sensores usados são:

- Sensores de Obstáculos
- Giroscópio/Acelerómetro
- Monitorização do consumo de corrente dos motores
- Encoders

e os atuadores serão apenas os motores.

\begin{figure}[H]
\centering
\includegraphics[width=\textwidth]{images/diagram_level_1.png}
\caption{Diagrama de blocos de nível 1}
\label{diagram1}
\end{figure}


### Sensor de obstáculos
Os sensores de obstáculos serão serão colocados estrategicamente na superfície lateral do robô para permitir uma detetação eficiente de obstáculos e permitir a navegação num ambiente 2D controlado e adequado às dimensões físicas do robô.
A cadeia de instumentação deste sensor pode ser consultada na figura \ref{cadeia_obs}. Nesta cadeia o sensor de obstáculos comunicará com microcontrolador através de usando um mecanismo de pedido/envio de daods, através do protocolo I2C, sendo esses dados posteriormente tratados por _software_ a desenvolver para efetuar a transdução para uma distância.

![Cadeia de instrumentação prevista para o sensor de obstáculos \label{cadeia_obs}](images/diagramas_instrumentacao_obstacle_sensor.png) 

### Giroscópio/Acelerómetro
Apesar de não representado no esboço (figura \ref{up_view}), será utilizado um giroscópio/acelerômetro. Este sensor será integrado num módulo que se pretende capaz de indicar a posição e orientação do robô relativamente à sua posição e orientação inicial, fornecendo informação que será usada para auxiliar a locomoção do robô.

A cadeia de instrumentação, representada na figura \ref{cadeia_gyro}, evidencia o protocolo de comunicação a ser usado com o sensor, I2C, e que os dados serão posteriormente tratados em _software_, para serem posteriormente utilizados no algoritmo de controlo do robô.


![Cadeia de instrumentação prevista para o giroscópio/acelerómetro \label{cadeia_gyro}](images/diagramas_instrumentacao_gyroscope.png) 

### Monitorização de sobre corrente nos motores
Este sensor tem como funcionalidade garantir que a corrente nos motores, devido a fenónemos de _stall_, não ultrapassa valores considerados seguros, evitando a possível destruição dos motores. A cadeia de instrumentação é representada na figura \ref{cadeia_curr}. 

O sinal elétrico que contém a informação da corrente é de reduzida excursão (no máximo algumas dezenas de miliVolt), sendo necessário acondicionar de forma adequada, como demonstrado na imagem, para puder extrair informação relevante.

![Cadeia de instrumentação prevista para o giroscópio/acelerómetro \label{cadeia_curr}](images/diagramas_instrumentacao_current_monitoring.png )

# Material Necessário

# Enquadramento com os objetivos de E4

[^1]: Um _ball caster_ é uma estrutura de apoio constituída por uma bola esférica de baixo atrito que serve de ponto de apoio e permite a locomoção do robô em qualquer direção

[^2]: A rotação segundo o centro geométrico do robô poderá não ser exata, devendo ser considerada uma rotação aproximada em torno do seu centro geométrico.

[^3]: Esta imagem deve ser analisada considerando que representa apenas um esboço da estrutura do robô, com o intuito de facilitar a visualização dos assuntos descritos no texto. A imagem não deve ser entendida como uma versão preliminar da estrutura, mas apenas como uma "ideia" do que poderá virá a ser.


