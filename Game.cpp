#include "Game.h"

#define WIN_WIDTH 800.f
#define WIN_HEIGHT 640.f
#define FEN_NAME "RPG de Loan"
#define GAME_FPS 60
#define PKM_APPARITION .1f
#define PAS 255/(GAME_FPS*PKM_APPARITION)

using namespace sf;
using namespace std;



Game::Game() :mWindow(VideoMode(WIN_WIDTH, WIN_HEIGHT), FEN_NAME), TimePerFrame(seconds(1.f / (float)GAME_FPS)) {

	m_core = new Core;
	m_data = new Package;
	m_data = m_core->launchState(GAME_BEGIN, WIN_WIDTH, WIN_HEIGHT);
	m_state = m_data->state;
	// m_data->sound[0].play();

}

Game::~Game()
{
	delete m_data;
}

void Game::run()
{


	Clock clock;


	Time timeSinceLastUpdate;
	timeSinceLastUpdate = Time::Zero;


	while (mWindow.isOpen())
	{


		processEvent();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{

			timeSinceLastUpdate -= TimePerFrame;
			processEvent();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvent()
{
	Event event;
	while (mWindow.pollEvent(event))
	{

		switch (event.type)
		{

		case Event::KeyReleased: break;
		case Event::KeyPressed:
			switch (event.key.code)
			{
			case Keyboard::Up:
				if(m_state == GAME_BEGIN)
					if (m_data->flag[1])
						m_data->yesNo->up();
				break;
			case Keyboard::Down:
				if (m_state == GAME_BEGIN)
					if (m_data->flag[1])
						m_data->yesNo->down();
				break;

			case Keyboard::Return:
				if (m_state == GAME_BEGIN)
				{
					if (m_data->flag[0] && !m_data->flag[1])//si la boite existe et que la yesno est desactivée
						if (!m_data->msgBox->next_frame())  // la boite de dialogue n a plus de suivant?
						{
							m_data->flag[2] = true;
							break;
						}
					if (!m_data->flag[0] && m_data->flag[1])
					{
						m_data->yesNo->setResult();
						break;
					}

					if (m_data->flag[5] && !m_data->flag[6])
						if (!m_data->msgBox->next_frame())
						{
							m_data->flag[6] = true;
							break;
						}
				}
				
				break;


			}
			break;


		case Event::Closed: mWindow.close(); break;
		}
	}

}

void Game::update(Time deltaTime)
{
	m_core->handleState(m_state, m_data);
	// switch?
	if (m_state == GAME_BEGIN)
	{

		if (m_data->flag[0]) // msgbox draw?
			if (!m_data->msgBox->haveBeenVisible()) // en gros, si on a pas deja la fenetre visible, on la met, sinon on ne la réaffiche pas (sinon quand
				m_data->msgBox->setVisible(true);		// on a fini le dialogue la fenetre ne se ferme pas			

		if (!m_data->flag[3]) {
			double p = m_data->v_double[0] + PAS;
			if (p < 255) {
				m_data->v_double[0] += PAS;
				m_data->sprite[0].setColor(Color(255, 255, 255, round(m_data->v_double[0])));
			}
			else
			{
				m_data->flag[0] = true;
				m_data->flag[3] = true;
			}

		}

	}
}

void Game::render()
{
	mWindow.clear();
	switch (m_state)
	{
	case GAME_BEGIN:
		mWindow.draw(m_data->sprite[0]);
		if (m_data->flag[0] || m_data->flag[4]) // msgbox draw?
			mWindow.draw(*m_data->msgBox);

		if (m_data->flag[1]) // yesno draw?
			mWindow.draw(*m_data->yesNo);
		break;
	}
	
	mWindow.display();
}


double distanceEuclidienne(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt(pow(a.x - b.x, 2) +
		pow(a.y - b.y, 2));
}



