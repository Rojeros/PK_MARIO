#include "StdAfx.h"
#include "App.h"
#include "Engine.h"

int main(int argc, char *argv[]) {

	Engine::Get().Load();

	App app(600, 400, false);
	app.Run();
	return 0;
}
