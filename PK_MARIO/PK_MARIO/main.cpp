#include "StdAfx.h"
#include "App.h"
#include "Player.h"
//#include "Engine.h"

int main(int argc, char *argv[])
{
	//SpriteData *cos=new SpriteData(5, 0.2, 0, 4 * 32, 32, 32, true, TYPES::PlayerLayer);
	
	//Engine::Get().Load();

	App app(600, 400, false);
	app.Run();
	return 0;
}
