#include <iostream>
#include <SFML/Graphics.hpp>
#include "SnakePlayer.h"

class Snake : public sf::Drawable, public sf::Transformable
{
	private:
		std::default_random_engine generator; //RNG

		struct Tile
		{
			bool m_occupied;
			bool m_point;
			sf::RectangleShape m_shape;
		};

		SnakePlayer m_player;

		Tile **m_table;
		sf::Vector2u m_screenSize;

		int m_tilesX;
		int m_tilesY;

		sf::Time m_deltaMove = sf::Time::Zero;

		bool f_isPointSpawned = false;
		sf::Vector2u m_tilePoint;


		void updateGameTable()
		{
			for (int i = 0; i < m_tilesY; i++)
			{
				for (int j =0; j < m_tilesX;j++)
				{
					m_table[i][j].m_occupied = false;
				}
			}

			std::deque<sf::Vector2u> *snakeNodes = m_player.GetSnakeNodes();

			for (auto it = snakeNodes->begin(); it != snakeNodes->end() ; ++it)
			{
				if(it->x < m_tilesX && it->y < m_tilesY)
					m_table[it->y][it->x].m_occupied = true;
			}
		} //updateGameTable

		void updateGamePoint()
		{
			if (m_table[m_tilePoint.x][m_tilePoint.y].m_occupied)
			{
				m_table[m_tilePoint.x][m_tilePoint.y].m_point = false;
				spawnPoint();
				m_player.ScoreUp();
			}
		}

		void initializeDrawing()
		{
			for (int i = 0; i < m_tilesY; i++)
			{
				for (int j =0; j < m_tilesX;j ++)
				{
					if (m_table[i][j].m_occupied)
						m_table[i][j].m_shape.setFillColor(sf::Color::Blue);
					else if (m_table[i][j].m_point)
						m_table[i][j].m_shape.setFillColor(sf::Color::Red);
					else
					{
						m_table[i][j].m_shape.setFillColor(sf::Color::Black);
						m_table[i][j].m_shape.setOutlineThickness(2);
						m_table[i][j].m_shape.setOutlineColor(sf::Color::Green);
					}

				}
			}

		} //initializeDrawing()

		void spawnPoint()
		{
			std::uniform_int_distribution<int> tileXRandom(0,m_tilesX-1);
			std::uniform_int_distribution<int> tileYRandom(0,m_tilesY-1);

			m_tilePoint.x = tileXRandom(generator); 
			m_tilePoint.y = tileYRandom(generator); 
			
			m_table[m_tilePoint.x][m_tilePoint.y].m_point = true;
			f_isPointSpawned = true;
		}//spawnPoint()

	public:
		Snake(int sizeX, int sizeY)
		{
			std::cout << "Snake.h: Snake:Snake(int sizeX, int sizeY)\n";
			
			m_screenSize.x= sizeX;
			m_screenSize.y= sizeY;

			m_tilesY = sizeY/20;
			m_tilesX = m_tilesY;

			std::cout << "Snake.h: m_tilesY:" << m_tilesY << "\n";
			std::cout << "Snake.h: m_tilesX:" << m_tilesX << "\n";

			m_table = new Tile*[m_tilesY];
			for (int i = 0; i < m_tilesX; i++)
			{
				m_table[i] = new Tile[m_tilesX];
			}

			int posX = 0;
			int posY = 0;
			for (int i = 0; i < m_tilesY; i++)
			{
				for (int j =0; j < m_tilesX;j++)
				{
					m_table[i][j].m_occupied = false;
					m_table[i][j].m_point = false;
					//m_table[i][j].m_shape.setFillColor(sf::Color::White);
					//m_table[i][j].m_shape.setOutlineColor(sf::Color::White);
					m_table[i][j].m_shape.setSize(sf::Vector2f(20,20));
					m_table[i][j].m_shape.setPosition(posX,posY);
					posX += 20;
				}
				posX = 0;
				posY +=20;
			}

			spawnPoint(); //TODO: ADD Startup function
		}


		void Update(sf::Time dt)
		{
			updateGameTable();
			updateGamePoint();
			initializeDrawing();

			m_deltaMove += dt;
			
			if (m_deltaMove.asSeconds() > 0.5)
			{
			m_player.Update();
			m_deltaMove = sf::Time::Zero;
			}

		}

    	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    	{
			for (int i = 0; i < m_tilesY; i++)
			{
				for (int j =0; j < m_tilesX;j ++)
				{
					target.draw(m_table[i][j].m_shape);
				}
			}
		}


		SnakePlayer* getPlayerPtr()
		{
			return &m_player;
		}

		void HandleInput(sf::Keyboard::Key key)
		{
			if (key == sf::Keyboard::Enter)
			{
				if(m_player.isGameOver())
				{
					m_player = SnakePlayer();
				}
			}

			if (key == sf::Keyboard::Up)
			{
				m_player.HandleInput(key);
			}

			if (key == sf::Keyboard::Down)
			{
				m_player.HandleInput(key);
			}

			if (key == sf::Keyboard::Left)
			{
				m_player.HandleInput(key);
			}

			if (key == sf::Keyboard::Right)
			{
				m_player.HandleInput(key);
			}
		}

};
