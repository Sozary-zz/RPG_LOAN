#include "Core.h"

using namespace std;

Core::Core() :m_state(WAIT_FOR_BEGIN)
{
}

Package* Core::launchState(STATES s, float w, float h)
{
	m_state = s;
	Package* res = new Package;
	res->msgBox = NULL;
	res->yesNo = NULL;

	switch (m_state)
	{
	case GAME_BEGIN:
		cout << "Debut du jeu" << endl;
		res->state = GAME_BEGIN;

		res->texture.resize(1);
		res->sprite.resize(1);
		res->b_sound.resize(1);
		res->sound.resize(1);
		res->v_double.resize(1);
		res->flag.resize(7);

		res->texture[0].loadFromFile("data/pkm_deb.png");
		res->sprite[0].setTexture(res->texture[0]);
		res->sprite[0].setScale(sf::Vector2f((w / 4) / res->texture[0].getSize().x, (h / 4) / res->texture[0].getSize().y));
		res->sprite[0].setPosition(sf::Vector2f(w / 2 - (res->texture[0].getSize().x*res->sprite[0].getScale().x) / 2,
			h / 2 - (res->texture[0].getSize().y*res->sprite[0].getScale().y) / 2));
		res->sprite[0].setColor(sf::Color(255, 255, 255, 0));
		res->b_sound[0].loadFromFile("data/intro.ogg");
		res->sound[0].setBuffer(res->b_sound[0]);
		res->v_double[0] = 0;
		res->flag[0] = false; // on affiche la boite de dialogue 1? // a mettre a false
		res->msgBox = new MsgBox;
		res->msgBox->setString(getScriptById(0));
		res->yesNo = new YesNoBox(string("Garçon"), string("Fille"));
		res->flag[1] = false; // on n affiche pas la boite yesno des le debut // quoique le setVisible de yesno reste obligatoire ( cest une sécurité pas nécessaire)
		res->flag[2] = false; // on a fini de lire le msgbox avant le yesno?
		res->flag[3] = false; // intro fini?
		res->flag[4] = false; // on affiche la deuxieme msgbox?
		res->flag[5] = false; // yesno fini, on charge les questions suivante
		res->flag[6] = false; // msgbox 2 (choix classe ) fini?

		return res;

	}
}

void Core::handleState(STATES& s, Package* p) const// le prog sait pas quoi faire à un moment donné!
{
	//auto result_from_yesno = p->yesNo->getResult();

	switch (s)
	{
	case WAIT_FOR_BEGIN: // Bah rien on attend 
		break;
	case GAME_BEGIN: // le yesno de départ pour commencer
		if (p->flag[2] && !p->flag[1] && !p->flag[5])
		{
			p->flag[0] = false;
			p->flag[1] = true;
			p->yesNo->setVisible(true);
		}
		if (p->flag[3] && !p->flag[0] && p->yesNo->getResult() != -1 && !p->flag[4]) // un résultat donné par joueur?
		{
			p->yesNo->setVisible(false);
			p->flag[1] = false;
			delete p->msgBox;
			p->msgBox = new MsgBox;

			p->msgBox->setString(getScriptById(p->yesNo->getResult() + 1)); // pratik é util
			p->flag[4] = true;
			p->msgBox->setVisible(true);
			p->flag[5] = true; // on passe a la suite (cad choix des classes)
		}
		if (p->flag[6]) // NEXT
		{
			p->texture.clear(); // clean tout
			delete p->msgBox;
			delete p->yesNo;
			p->picture.clear();
			p->flag.clear();
			p->sprite.clear();
			p->v_double.clear();
			p->v_int.clear();
			p->v_str.clear();
		
			s = CLASSE_CHOICE;
		}

		break;

	case CLASSE_CHOICE:
		
		break;
	default:
		break;
	}
}


Core::~Core()
{
}

string Core::getScriptById(double id)const
{
	fstream file("data/scripts.s", ios::in);
	string res;
	string prefix = "";
	string tmp;
	stringstream ss;
	int corres;

	while (getline(file, tmp)) {
		for (int i = 0; i < 8; ++i)
		{
			if (i >= 2)
				prefix += tmp[0];
			tmp.erase(tmp.begin());
		}
		tmp.erase(tmp.begin());


		corres = atoi(prefix.c_str());
		prefix.clear();
		if (corres == id)
			return tmp;
	}

	return res;
}
