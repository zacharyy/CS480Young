
#include "engine.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
	direction = 1;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
	direction = 1;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
 			ImGui_ImplSDL2_ProcessEvent(&m_event);
      KeyboardAndMouse();
    }

    // Update and render the graphics
    m_graphics->Update(m_DT, direction);
    m_graphics->Render();

		m_window->GUIFrame(direction);
    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::KeyboardAndMouse()
{
	static int previousDirection;
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else if (m_event.type == SDL_KEYDOWN)
  {
    // handle key down events here
    if (m_event.key.keysym.sym == SDLK_ESCAPE)
    {
      m_running = false;
    }
		if (m_event.key.keysym.sym == SDLK_1)
		{
			direction = -direction;
		}
		if (m_event.key.keysym.sym == SDLK_2)
		{
			if(direction == 0) direction = previousDirection;
			else {
				previousDirection = direction;
				direction = 0;
			}
		}
		if (m_event.key.keysym.sym == SDLK_LEFT)
		{
			direction = -1;			
		}
		if (m_event.key.keysym.sym == SDLK_RIGHT)
		{
			direction = 1;
		}		
  } else if (m_event.type == SDL_MOUSEBUTTONDOWN)
  {
    /* If the left button was pressed. */
		if (m_event.button.button == SDL_BUTTON_LEFT)
		{
			direction = -direction;
		}
		if (m_event.button.button == SDL_BUTTON_RIGHT)
		{
			if(direction == 0) direction = previousDirection;
			else {
				previousDirection = direction;
				direction = 0;
			}
		}
	}		
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
