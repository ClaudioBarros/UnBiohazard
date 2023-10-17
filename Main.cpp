#include <SDL/SDL.h>
#include <Game.h>

int main(int argc, char *argv[])
{
    Game &g = Game::GetInstance();
    g.Run();

	return 0;
}
