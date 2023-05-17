O projeto utiliza bibliotecas de 64 bits, não funcionará com sistemas ou compiladores de 32 bits.
Você pode descobrir como instalar o MingW-64 aqui: https://www.youtube.com/watch?v=Zcy981HhGw0&ab_channel=GhostTogether
Aqui está um passo a passo para compilar o programa:
1. Clone ou baixe o repositório e abra na sua IDE de escolha
2. Abra o terminal e garanta que ele está na localização da pasta do projeto
3. Após isso, execurte o comando:
    make
4. Caso não seja possível utilizar o comando make, cole a seguinte linha no terminal:
    g++ -std=c++11 -Wall -O0 -g -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
5. Após isso, será gerado um executável na pasta do projeto, você pode executá-lo normalmente ou utilizar o comando ./main
6. Espero que goste!

O programa pode ser compilado em qualquer sistema operacional, porém a linha de comando disponibilizada e utilizada na makefile funciona somente em sistemas Windows (e talvez Linux)


The project uses 64-bit libraries, it will not work with 32-bit compilers/systems.
You can find how to install MingW-64 here: https://www.youtube.com/watch?v=Zcy981HhGw0&ab_channel=GhostTogether
Here is a guide to compile the program:
1. Clone or download the repository and open it in your preferred IDE
2. Open the terminal and make sure it is in the project's folder location
3. Use the command:
    make
4. If that didn't work, you can paste the following line in the terminal:
    g++ -std=c++11 -Wall -O0 -g -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
5. After that, an executable will be generated in the project's folder, you can execute it normally or use the command ./main
6. I hope you enjoy!

The program can be compiled in any operational system, but the command line given and used in the makefile only works for Windows (and maybe Linux)
