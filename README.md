# Projeto-PIF
Projeto da matéria de Programação Imperativa Funcional, do segundo período de Ciência da Computação na Cesar School. 

PASSOS PARA JOGAR O CHICK RUNNING

Primeiro é necessário verificar que as bibliotecas e o arquivo main.c que estão presentes no GitHub estão no mesmo arquivo diretório da sua máquina e rodar a seguinte linha de comando:
```
gcc –o chickrunning main.c keyboard.c screen.c timer.c
```
Logo em seguida, digitar essa segunda linha:
```
./chickrunning
```
- INICIANDO O JOGO

1. O chick running irá abrir e será iniciado automaticamente com a cerca indo em direção ao chick.

2. E a função do usuário é desviar desta cerca dando pulos precionando a tecla "ESPAÇO".

3. Enquando o usuário pular a cerca e ela tocar na parede do lado esquerdo do jogo o jogador ganhará um ponto somado no "SCORE".
- A cada vez que a cerca tocar na parede do lado esquerdo a pontuação aumentará 1 ponto no "SCORE" e a cerca retornará para o inicio do looping.

4. Quando está cerca esbarrar de alguma maneira com o chick o jogo vai parar imediatamente e vai mostrar na tela um "GAME OVER".
- Dando a entender que o jogador perdeu.

5. Se o jogador quiser recomeçar e jogar novamente é necessario que ele aperte a tecla "R" e o jogo recomeçará zerando o "SCORE" e salvando este score no HighScore.
- o HighScore salva e mostra as melhores pontuações em sequência da maior para a menor, para ver elas é necessário digitar a telha "ENTER" ao final da rodada.

6. Para encerrar o chick running é necessário digitar a tecla "ENTER" no "GAME OUVER" e ele irá sair do jogo mostrando o HighScore.
