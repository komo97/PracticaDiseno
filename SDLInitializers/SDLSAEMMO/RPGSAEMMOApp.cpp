#include "RPGSAEMMOApp.h"
#include "Physics2D.h"
#include <iostream>

std::queue<std::function<void()>> RPGSAEMMOApp::drawQueue;
SDL_bool RPGSAEMMOApp::appIsClosing = SDL_FALSE;
SDL_mutex* RPGSAEMMOApp::drawMutex = nullptr;
int RPGSAEMMOApp::frameLock = 11;
int RPGSAEMMOApp::windowSizeX = 0;
int RPGSAEMMOApp::windowSizeY = 0;
SDL_Renderer* RPGSAEMMOApp::renderer = nullptr;
SDL_Surface* RPGSAEMMOApp::renderSurface = nullptr;
SDL_Window* RPGSAEMMOApp::window = nullptr;
SDL_Texture* RPGSAEMMOApp::renderTexture = nullptr;
bool RPGSAEMMOApp::queueIsCleared = false;
std::chrono::milliseconds RPGSAEMMOApp::physicsTimeSinceStart;
std::chrono::milliseconds RPGSAEMMOApp::physicsTimeStart;
std::chrono::milliseconds RPGSAEMMOApp::deltaTime;
long long RPGSAEMMOApp::dT;

//La funcion App controla y destruye toda la aplicacion, se encarga de que la aplicacion se mantenga abierta y la destruya
void RPGSAEMMOApp::App(const int & sizeX, const int & sizeY,
	const char * WindowTitle, const uint32_t parameters, int fps,
	Scene* const& mainScene)
{
	physicsTimeStart = physicsTimeSinceStart =
		std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch());
	windowSizeX = sizeX;
	windowSizeY = sizeY;
	winParams = parameters;
	ChangeFrameLock(fps);
	Init();
	SDL_SetWindowTitle(window,WindowTitle);
	SceneManager::GetSceneManager()->ChangeScene(mainScene);;
	
	//ciclo main loop.
	while (1)
	{
		//consigue todos los eventos que ha llamado la ecena y los guarda en event
		SDL_PollEvent(&event);
		//Pregunta si se esta cerrando la ventana.
		if (event.type == SDL_QUIT)
		{
			//manda señal de que se esta cerrando la ventana.
			appIsClosing = SDL_TRUE;
			break;
		}
		physicsTimeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::system_clock::now().time_since_epoch()) - physicsTimeStart;
		//Semaforos, LockMutex evita los problemas de carrera, evita que se use un pedazo de informacion al mismo tiempo en dos lugares.
		SDL_LockMutex(drawMutex);
		//Son filas,como parametro esta haciendo un llamado a la direccion de memoria de un  bloque de codigo estatico, y despues lo puedo llamar cuando quiera.
		drawQueue.push(&DrawStep);
		//Semaforo verde de drawMutex
		SDL_UnlockMutex(drawMutex);
		//Actualiza la escena
		SceneManager::GetSceneManager()->GetCurrentScene()->Update();
		//Calcula cuanto va a durar un frame en milisegundos.
		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::system_clock::now().time_since_epoch()) - physicsTimeSinceStart - physicsTimeStart;
		_int64 f = frameLock - deltaTime.count();
		SDL_Delay((Uint32)f < (Uint32)frameLock ? (Uint32)f : frameLock);
		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::system_clock::now().time_since_epoch()) - physicsTimeSinceStart - physicsTimeStart;
		dT = (float)(deltaTime.count());
		
	}
	SceneManager::DeleteSceneManager();
	int threadStatus;
	if(SDL_GetThreadID(drawThread) == 0)
		SDL_WaitThread(drawThread, &threadStatus);
	if (SDL_GetThreadID(physicsThread) == 0)
		SDL_WaitThread(physicsThread, &threadStatus);
	SDL_DestroyMutex(drawMutex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_FreeSurface(renderSurface);
	SDL_DestroyTexture(renderTexture);
	IMG_Quit();
	int a;
	Uint16 b;
	int c;
	for(int i = Mix_QuerySpec(&a,&b,&c); i--;)
		Mix_CloseAudio();
	while (Mix_Init(0))
		Mix_Quit();
	SDL_Quit();
}

void RPGSAEMMOApp::ChangeFrameLock(const int & fps)
{
	frameLock = (1000 / fps);
}

int RPGSAEMMOApp::GetFrameLock()
{
	return (1000 / frameLock);
}

int RPGSAEMMOApp::getWidth()
{
	return windowSizeX;
}

int RPGSAEMMOApp::getHeight()
{
	return windowSizeY;
}

void RPGSAEMMOApp::PrintSurfacesToScreen(const std::vector<SDL_Surface*>& surfaces,
	const std::vector<SDL_Rect*>& srcRects, const std::vector<SDL_Rect*>& dstRects)
{
	for (Uint32 i = 0; i < surfaces.size();++i)
	{
		renderTexture = SDL_CreateTextureFromSurface(renderer, surfaces.at(i));
		SDL_RenderCopy(renderer, renderTexture,
			srcRects.at(i), dstRects.at(i));
		SDL_DestroyTexture(renderTexture);
	}
}

void RPGSAEMMOApp::ClearDrawQueue()
{
	queueIsCleared = false;
	while (!drawQueue.empty()) drawQueue.pop();
	queueIsCleared = true;
}

void RPGSAEMMOApp::AddToDrawQueue(std::function<void()> f)
{
	SDL_LockMutex(drawMutex);
	drawQueue.push(f);
	SDL_LockMutex(drawMutex);
}

//trabaja la mayoria de la aplicacion
void RPGSAEMMOApp::Init()
{
	//Inicializaciones, SDL se encarga de detectar la plataforma 
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		//Manejo de errores criticos, cierra la aplicacion al encontrar un error
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		exit(-1);
	}
	//Se encarga de comprobar si al inicializar la escenas hay un error 
	if (SDL_CreateWindowAndRenderer(windowSizeX, windowSizeY, winParams, &window, &renderer) == -1)
	{
		SDL_Log("Failed to initialize Window: %s", SDL_GetError());
		exit(-2);
	}
	drawThread = SDL_CreateThread((Draw), "Draw", (void*)NULL);
	physicsThread = SDL_CreateThread((Physics), "Physics", (void*)NULL);
	drawMutex = SDL_CreateMutex();
	if (drawThread == NULL)
	{
		SDL_Log("Failed to initialize DrawThread: %s", SDL_GetError());
		exit(-3);
	}
	if (drawMutex == NULL)
	{
		SDL_Log("Failed to initialize DrawQueue: %s", SDL_GetError());
		exit(-4);
	}
	renderSurface = SDL_GetWindowSurface(RPGSAEMMOApp::getWindow());
	renderTexture = SDL_CreateTextureFromSurface(renderer, renderSurface);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(-5);
	}
	const int flags = MIX_INIT_FLAC |
		MIX_INIT_MP3 |
		MIX_INIT_OGG;
	if ( (Mix_Init(flags) & flags) != flags)
	{
		SDL_Log("Failed to initialize audio library.");
		exit(-6);
	}
	if (TTF_Init() == -1)
	{
		SDL_Log("TTF failed to initialize.");
		exit(-7);
	}
	const int flagsI = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	if ((IMG_Init(flagsI) & flagsI) != flagsI)
	{
		SDL_Log("Failed to initialize Image Library: %s", IMG_GetError());
		exit(-8);
	}
	Mix_VolumeMusic(100);
	SDL_DetachThread(physicsThread);
	SDL_DetachThread(drawThread);
}

int RPGSAEMMOApp::Draw(void * ptr)
{
	while (!appIsClosing) {
		if (drawQueue.size() <= 0) {
			SDL_Delay(10);
			continue;
		}
		SDL_RenderClear(renderer);
		SDL_LockMutex(drawMutex);
		std::function<void()> f = drawQueue.front();
		drawQueue.pop();
		SDL_UnlockMutex(drawMutex);
		f();
		SDL_RenderPresent(renderer);
		queueIsCleared = false;
	}
	return 0;
}

void RPGSAEMMOApp::DrawStep()
{
	if(SceneManager::GetSceneManager()->GetCurrentScene() != nullptr)
		SceneManager::GetSceneManager()->GetCurrentScene()->Draw();
}

int RPGSAEMMOApp::Physics(void * ptr)
{
	Physics2D::getInstance()->UpdatePhysics();
	return 0;
}

