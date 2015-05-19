#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>

#include "Player.h"


int main()
{
	srand( time( NULL ) );
	
		try
	{
		Game game;
		game.Run(); 
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
		_getch();
	}

	/*std::map<int,std::string> kontener;
	kontener[0]="a";
	kontener[1]="b";
	for (auto a : kontener)
		std::cout<<a.second<<std::endl;	*/
	//tmx::MapLoader fff("abc/d");
	
    return 0;
}