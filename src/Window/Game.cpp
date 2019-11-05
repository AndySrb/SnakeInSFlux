#include "Game.h"


Game::Game(): m_window("Pong", sf::Vector2u(800,600)),
m_AssetMenager(new AssetMenager())
{
// Setting up class members.
	std::cout << "Game::Game()" << std::endl;
	m_window.setFrameRate(60);

	if (!font.loadFromFile("sansation.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
	}

	snake = new Snake(m_window.GetWindowSize().x,m_window.GetWindowSize().y);


	m_score.setFont(font);
	m_score.setCharacterSize(15);
	m_score.setPosition(610,0);

	m_score.setString("Score:\n" + std::to_string(snake->getPlayerPtr()->GetScore()));


}

Game::~Game() {}

void Game::Update()
{
m_window.Update(); // Update window events.
HandleInput();
snake->Update(delta);
updateScore();
delta = m_window.GetDeltaTime();
}


void Game::Render()
{
m_window.BeginDraw(); // Clear.
m_window.Draw(*snake);
m_window.Draw(m_score);
m_window.EndDraw();
}

void Game::updateScore()
{

	std::string str= "Score:\n" + std::to_string(snake->getPlayerPtr()->GetScore()) + "\nPress F5 for fullscreen";

	if (snake->getPlayerPtr()->isGameOver())
		str+= "\nGame Over\nPress Enter Restart";

	m_score.setString(str);
}

void Game::HandleInput()
{
	if (m_InputHandler.isKeyboardKeyPressed(sf::Keyboard::Enter))
	{
		snake->HandleInput(sf::Keyboard::Enter);
	}
	if (m_InputHandler.isKeyboardKeyPressed(sf::Keyboard::Up))
	{
		snake->HandleInput(sf::Keyboard::Up);
	}

	if (m_InputHandler.isKeyboardKeyPressed(sf::Keyboard::Left))
	{
		snake->HandleInput(sf::Keyboard::Left);
	}

	if (m_InputHandler.isKeyboardKeyPressed(sf::Keyboard::Right))
	{
		snake->HandleInput(sf::Keyboard::Right);
	}
	
	if (m_InputHandler.isKeyboardKeyPressed(sf::Keyboard::Down))
	{
		snake->HandleInput(sf::Keyboard::Down);
	}

}

Window* Game::GetWindow()
{
	Window *ptr = &m_window;
	return ptr;
}

