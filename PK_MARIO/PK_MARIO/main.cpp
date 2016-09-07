#include "StdAfx.h"
#include "App.h"
#include "Player.h"
//#include "Engine.h"

int main(int argc, char *argv[])
{
	Player osoba(8,0,true, TYPES::Players, TYPES::Background, 10, 1);
	//Engine::Get().Load();

	App app(600, 400, false);
	app.Run();
	return 0;
}
