#include "AuthForm.h"
#include "exception.h"

using namespace GithubSimulation;

int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew GithubSimulation::AuthForm());
	return 0;
}


