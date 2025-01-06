To compile the code:
1. Navigate to src : cd src
2. This command :  g++ -g -Wall -Wextra -o prog *.cpp $(pkg-config --cflags --libs sdl2)
3. To display: ./prog.exe