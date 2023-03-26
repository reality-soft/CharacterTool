#include "CharacterTool.h"

int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	ENGINE->OnInit(hinstance, L"CharacterTool", { 1280, 720 });

	CharacterTool charcter_tool;

	SCENE_MGR->SetScene<CharacterTool>();
	ENGINE->Run();

	ENGINE->OnRelease();

	return 0;
}