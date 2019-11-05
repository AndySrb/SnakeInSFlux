#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <deque>
#include <random>

template <class T>
bool hasDupicates(const std::deque<T> &vec)
{
	auto it = vec.begin();
	while (it != vec.end())
	{
		for (auto it2 = vec.begin(); it2 != vec.end(); ++it2)
		{
			if (it == it2)
				continue;

			if ((it2->x == it->x) && (it2->y == it->y))
			{
				return true;
			}
		}
		++it;
	}

	return false;
}

class SnakePlayer
{
	private:
		std::deque<sf::Vector2u> m_snakeNodes;
		

		sf::Vector2u m_startingSnakePos;
		sf::Vector2u m_currentSnakePos;

		int m_snakeSize = 3;

		bool f_isMovingUp = false;
		bool f_isMovingDown = false;
		bool f_isMovingLeft = false;
		bool f_isMovingRight = false;

		bool f_GameOver = false;

		inline void moveUp()
		{
			m_currentSnakePos.y -=1;
			m_snakeNodes.push_back(sf::Vector2u(m_currentSnakePos.x,m_currentSnakePos.y));
		}

		inline void moveDown()
		{
			m_currentSnakePos.y +=1;
			m_snakeNodes.push_back(sf::Vector2u(m_currentSnakePos.x,m_currentSnakePos.y));
		}

		inline void moveLeft()
		{
			m_currentSnakePos.x -=1;
			m_snakeNodes.push_back(sf::Vector2u(m_currentSnakePos.x,m_currentSnakePos.y));
		}

		inline void moveRight()
		{
			m_currentSnakePos.x +=1;
			m_snakeNodes.push_back(sf::Vector2u(m_currentSnakePos.x,m_currentSnakePos.y));
		}

	public:
		SnakePlayer()
		{
			m_currentSnakePos.x=15;
			m_currentSnakePos.y=15;
		}

		void SetStartingSnakePos(sf::Vector2u pos)
		{
			m_startingSnakePos = pos;
			m_currentSnakePos = pos;
			m_snakeNodes.push_back(pos);
		}

		std::deque<sf::Vector2u>* GetSnakeNodes()
		{
			return &m_snakeNodes;
		}

		void ScoreUp()
		{
			m_snakeSize++;
		}

		int GetScore()
		{
			return m_snakeSize-3;
		}

		bool isGameOver()
		{
			return f_GameOver;
		} 

		void HandleInput(sf::Keyboard::Key key)
		{
			if (key == sf::Keyboard::Up)
			{
				f_isMovingUp =true;
				f_isMovingDown = false;
				f_isMovingLeft = false;
				f_isMovingRight = false;
			}
			if (key == sf::Keyboard::Down)
			{
				f_isMovingUp = false;
				f_isMovingDown = true;
				f_isMovingLeft = false;
				f_isMovingRight = false;
			}
			if (key == sf::Keyboard::Left)
			{
				f_isMovingUp = false;
				f_isMovingDown = false;
				f_isMovingLeft = true;
				f_isMovingRight = false;
			}
			if (key == sf::Keyboard::Right)
			{
				f_isMovingUp = false;
				f_isMovingDown = false;
				f_isMovingLeft = false;
				f_isMovingRight = true;
			}

		}

		void Update()
		{

			if (!f_GameOver)
			{

			if (hasDupicates(m_snakeNodes))
			{
				f_GameOver= true;
			}

			if ( m_snakeNodes.size() > m_snakeSize)
			{
				m_snakeNodes.pop_front();
			}


			if (f_isMovingUp)
				moveUp();
			else if(f_isMovingDown)
				moveDown();
			else if (f_isMovingLeft)
				moveLeft();
			else if (f_isMovingRight)
				moveRight();
			}
		}



};
