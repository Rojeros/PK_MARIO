#include "StdAfx.h"
#include "App.h"
#include "Player.h"

///-------------------------------------------------------------------------------------------------
/// <summary>	Main entry-point for this application. </summary>
///
/// <param name="argc">	The number of command-line arguments provided. </param>
/// <param name="argv">	An array of command-line argument strings. </param>
///
/// <returns>	Exit-code for the process - 0 for success, else an error code. </returns>
///-------------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{

	try
	{
	App app(600, 400, false);
	app.Run();
	}
	catch (std::string s) 
	{
	
		std::cerr <<"Error"<< s<<"\n";
	}
	catch (... ) 
	{
		std::cerr << "Critical Error" << "\n";
	}

	return 0;
}
