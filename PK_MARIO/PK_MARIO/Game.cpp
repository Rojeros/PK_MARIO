#include "StdAfx.h"

#include "Game.h"
#include "Engine.h"
#include "Sprite.h"
#include "Text.h"


void Game::ProcessEvents(const SDL_Event& event) {
	if (IsDone()) {
		return;
	}

	// przyjrzyj zdarzenia
	if (event.type == SDL_QUIT) {
		SetDone();
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
	//	m_next_app_state = m_level_choice_screen;
		m_next_app_state->Init();
		SetDone();
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d) {
		m_player->Run();
	}
	else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_d) {
		m_player->StopRunning();
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s) {
		m_player->FireBullet();
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
		m_player->Jump();
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
		m_player->GoLeft();
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
		m_player->GoRight();
	}
	else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT) {
		m_player->StopLeft();
	}
	else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT) {
		m_player->StopRight();
	}
}

void Game::Start() {
//	Engine::Get().GetSound()->PlayMusic("game");
}

void Game::Init() {
	Engine& engine = Engine::Get();

	// �adowanie poziomu i sprite'�w planszy
	m_level.reset(new Level());
	m_level->LoadFromFile("data/" + m_level_name + ".lvl");
	if (!m_level->GetLoaded()) {
		m_level_name = "1";
		m_level->LoadFromFile("data/" + m_level_name + ".lvl");
	}

	// za�aduj jednostki do poziomu
	m_level->LoadEntitiesFromFile("data/" + m_level_name + ".ents");
//	m_entities_to_create = m_level->GetAllEntitiesToCreate();

	m_level_view.StoreSprite(PlatformTopLeft, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("PlatformTopLeft"))));
	m_level_view.StoreSprite(PlatformLeft, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("PlatformLeft"))));
	m_level_view.StoreSprite(PlatfromMid, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("PlatfromMid"))));
	m_level_view.StoreSprite(PlatformTop, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("PlatformTop"))));
	m_level_view.StoreSprite(PlatformLeftTopRight, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("PlatformLeftTopRight"))));
	m_level_view.StoreSprite(PlatformLeftRight, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("PlatformLeftRight"))));
	m_level_view.StoreSprite(PlatformTopRight, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("PlatformTopRight"))));
	m_level_view.StoreSprite(PlatformRight, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("PlatformRight"))));

	m_level_view.StoreSprite(EndOfLevel, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("EndOfLevel"))));

	m_level_view.StoreSprite(NcPlatformTopLeft, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("NcPlatformTopLeft"))));
	m_level_view.StoreSprite(NcPlatformLeft, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("NcPlatformLeft"))));
	m_level_view.StoreSprite(NcPlatfromMid, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("NcPlatfromMid"))));
	m_level_view.StoreSprite(NcPlatformTop, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("NcPlatformTop"))));
	m_level_view.StoreSprite(NcPlatformLeftTopRight, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("NcPlatformLeftTopRight"))));
	m_level_view.StoreSprite(NcPlatformLeftRight, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("NcPlatformLeftRight"))));
	m_level_view.StoreSprite(NcPlatformTopRight, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("NcPlatformTopRight"))));
	m_level_view.StoreSprite(NcPlatformRight, SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("NcPlatformRight"))));


	// utw�rz posta� gracza
	const LevelEntityData player_data = m_level->GetPlayerData();
	if (!m_player) {
		if (player_data.name == "player") {
			m_player.reset(new Player(player_data.x, player_data.y, m_level->GetWidth(),
				3, 0));
			m_player->SetSprites(SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("player_left"))),
				SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("player_right"))),
				SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("player_stop"))));
		}
		else {
			std::cerr << "brak informacji o postaci gracza w pliku z poziomem" << std::endl;
		}
	}
	else {
		m_stored_player_pos_x = 9;
		m_player->NewLevelReset(m_level);

	}
}

void Game::CheckPlayerEntitiesCollisions(double dt) {
	// poziomy i pionowy aabb gracza w nast�pnym 'kroku'
	Aabb player_box_x = m_player->GetNextHorizontalAabb(dt);
	Aabb player_box_y = m_player->GetNextVerticalAabb(dt);

	for (std::vector<EntityPtr>::iterator it = m_entities.begin(); it != m_entities.end(); ++it) {
		EntityPtr entity = *it;
		const ET::EntityType entity_type = entity->GetType();

		if (entity_type == ET::PlayerBullet) {
			// posta� nie koliduje ze swoimi pociskami
			continue;
		}
		else if (entity_type == ET::TwinShot) {
			// czy gracz wzi�� bonus TwinShot
			if (m_player->GetAabb().Collides(entity->GetAabb())) {
				m_player->EnableTwinShot();
				entity->SetIsDead(true);
			}
			continue;
		}

		// nie�miertelna posta� nie koliduje z innymi jednostkami,
		// ale mo�e zbiera� np. upgrade'y (patrz wy�ej)
		if (m_player->IsImmortal()) {
			continue;
		}

		entity->SetDefaultMovement();
		Aabb entity_box = entity->GetAabb();

		// sprawd� czy wyst�pi�a kolizja. Je�eli tak to gracz, zdecyduje o losie
		// swoim i jednostki. Zauwa�my, �e je�eli wyst�pi kolizja poni�ej gracza
		// (naskoczenie na jednostk�), to pozosta�e nie b�d� sprawdzane.
		if (player_box_y.IsOver(entity_box)) {
			// naskoczenie na jednostk�
			m_player->CollisionUnderPlayer(entity);
			player_box_y = m_player->GetNextVerticalAabb(dt);
		}
		else if (player_box_x.IsOnLeftOf(entity_box)) {
			m_player->ForbidGoingRight();
			m_player->CollisionOnRight(entity);
			player_box_x = m_player->GetNextHorizontalAabb(dt);
		}
		else if (player_box_x.IsOnRightOf(entity_box)) {
			m_player->ForbidGoingLeft();
			m_player->CollisionOnLeft(entity);
			player_box_x = m_player->GetNextHorizontalAabb(dt);
		}
		else if (player_box_y.IsUnder(entity_box)) {
			m_player->Fall();
			m_player->CollisionOverPlayer(entity);
			player_box_y = m_player->GetNextVerticalAabb(dt);
		}
	}
}

void Game::CheckCollisionOfOnePair(EntityPtr fst_entity, EntityType fst_type,
	EntityPtr snd_entity, EntityType snd_type,
	double dt) {
	if (fst_entity->GetNextAabb(dt).Collides(snd_entity->GetNextAabb(dt)) == false) {
		return;
	}

	// makro SWAP_IF pozwala zamieni� znaczenie argument�w fst_* z snd_*
	// w ten spos�b, �e sprawdzaj�c kolizj� otrzymujemy wska�niki zawsze
	// w dobrej kolejno�ci, tzn. tak, aby ka�d� par� obs�ugiwa� jeden raz
#define SWAP_IF( type_a, type_b )  \
    if (fst_type == type_a && snd_type == type_b) {  \
        std::swap(fst_entity, snd_entity);   \
        std::swap(fst_type, snd_type);   \
    }

	SWAP_IF(PlayerBullet, Mush)

		// w tym miejscu wiemy, �e je�eli nast�pi�a kolizja Mush z PlayerBullet,
		// to jednostka Mush b�dzie pod fst_entity a PlayerBullet pod snd_entity

		if (fst_type == ET::Mush && snd_type == ET::PlayerBullet) {
			snd_entity->SetIsDead(true);
			m_player->AddScores(fst_entity->GetScoresWhenKilled());
			fst_entity->KilledWithBullet();
		}

	if (fst_type == ET::Mush && snd_type == ET::Mush) {
		fst_entity->NegateXVelocity();
		snd_entity->NegateXVelocity();
	}

#undef SWAP_IF
}

void Game::CheckEntityEntityCollisions(double dt) {
	// sprawdzenie ka�dej pary (ka�dej jednokrotnie) - O(n^2)
	std::vector<EntityPtr>::iterator outer, inner;
	EntityPtr out_entity, inn_entity;
	ET::EntityType out_type, inn_type;
	for (outer = m_entities.begin(); outer != m_entities.end(); ++outer) {
		out_entity = *outer;
		out_type = out_entity->GetType();
		if (out_entity->IsDead()) {
			continue;
		}
		inner = outer;
		++inner;
		for (; inner != m_entities.end(); ++inner) {
			inn_entity = *inner;
			inn_type = inn_entity->GetType();
			if (inn_entity->IsDead()) {
				continue;
			}
			CheckCollisionOfOnePair(inn_entity, inn_type, out_entity, out_type, dt);
		}
	}
}

void Game::ExecuteCreators() {
	std::list<CreatorPtr> creators;

	// pobierz kreatory od gracza
	std::list<CreatorPtr> plr_c = m_player->GetCreators();
	creators.splice(creators.end(), plr_c);
	m_player->DropAllCreators();

	// pobierz kreatory z jednostek
	for (std::vector<EntityPtr>::iterator it = m_entities.begin(); it != m_entities.end(); ++it) {
		EntityPtr e = *it;
		if (!e->IsDead()) {
			std::list<CreatorPtr> ent_c = e->GetCreators();
			creators.splice(creators.end(), ent_c);
			e->DropAllCreators();
		}
	}

	// uruchom wszystkie kreatory
	for (std::list<CreatorPtr>::iterator it = creators.begin(); it != creators.end(); ++it) {
		(*it)->Create(*this);
	}
}

void Game::SeepAndAddEntities(double /* dt */) {
	// oznacz jednostki, kt�re s� za lew� kraw�dzi� ekranu jako martwe
	const double distance_of_deletion = Engine::Get().GetRenderer()->GetHorizontalTilesOnScreenCount();
	for (std::vector<EntityPtr>::iterator it = m_entities.begin(); it != m_entities.end(); ++it) {
		EntityPtr e = *it;
		if (e->GetX() + distance_of_deletion < m_player->GetX()) {
			e->SetIsDead(true);
		}
	}

	// usu� martwe jednostki - O(n^2). Mo�na w O(n), ale trzeba napisa� 
	// funktor - google(erase remove idiom).
	for (size_t i = 0; i < m_entities.size(); ++i) {
		if (m_entities.at(i)->IsDead()) {
			for (size_t c = i; c < m_entities.size() - 1; ++c) {
				m_entities.at(c) = m_entities.at(c + 1);
			}
			m_entities.resize(m_entities.size() - 1);
		}
	}

	// dodaj kolejne jednostki z listy do gry
	const double distance_of_creation = Engine::Get().GetRenderer()->GetHorizontalTilesOnScreenCount();
	while (m_entities_to_create.empty() == false) {
		if (m_entities_to_create.front().x - m_player->GetX() < distance_of_creation) {
			LevelEntityData data = m_entities_to_create.front();
			m_entities_to_create.pop_front();
			EntityPtr e = Engine::Get().GetEntityFactory()->CreateEntity(data.name, data.x, data.y);
			m_entities.push_back(e);
		}
		else {
			break;
		}
	}
}

void Game::BindLevelChoiceScreen(const boost::shared_ptr<LevelChoiceScreen>& screen) {
	m_level_choice_screen = screen;
}

bool Game::Update(double dt) {
	// czy gracz zako�czy� aktualny poziom
	if (m_player->HasCompletedCurrentLevel()) {
		m_level_choice_screen->SetPlayer(m_player);
		m_next_app_state = m_level_choice_screen;
		// m_next_app_state->Init();      // wa�ne!!

		SetDone();
		return IsDone();
	}
	else if (m_player->GetLifesCount() < 1) {
		size_t score = m_player->GetScores();
		if (score != 0) {
			m_next_app_state.reset(new ScoreSubmit(score));
		}
		else {
			m_next_app_state.reset(new HallOfFame());
		}
		SetDone();
	}

	// zbierz nowe obiekty z ju� istniej�cych
	ExecuteCreators();

	// ustaw domy�lny ruch graczowi
	m_player->SetDefaultMovement();

	// sprawd� kolizje gracz-jednostka oraz jednostka-jednostka
	CheckPlayerEntitiesCollisions(dt);
	CheckEntityEntityCollisions(dt);

	// uaktualnij obiekt reprezentuj�cy gracza
	m_player->Update(dt, m_level);

	// uaktualnij stan jednostek
	for (std::vector<EntityPtr>::iterator it = m_entities.begin(); it != m_entities.end(); ++it) {
		EntityPtr e = *it;
		if (e->IsAlive()) {
			e->Update(dt, m_level);
		}
	}

	// usu� niepotrzebne jednostki i dodaj nowe
	SeepAndAddEntities(dt);

	// zaaktualizuj stan mapy kaflowej (np. animacj� kafli)
	m_level_view.Update(dt);

	return !IsDone();
}

void Game::Draw() {
	if (IsClearBeforeDraw()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
	}

	// narysuj map�
	if (m_player->MoveMap()) {
		m_stored_player_pos_x = m_player->GetX();
	}

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	{
		double player_x = -(m_stored_player_pos_x * Engine::Get().GetRenderer()->GetTileWidth() - 0.45);
		glTranslated(player_x, 0, 0);
		glMatrixMode(GL_MODELVIEW);

		m_level_view.SetLevel(m_level, m_stored_player_pos_x);
		m_level_view.Draw(m_stored_player_pos_x);

		// narysuj posta� gracza
		m_player->Draw();

		// narysuj pozosta�e obiekty
		for (std::vector<EntityPtr>::const_iterator it = m_entities.begin(); it != m_entities.end(); ++it) {
			const EntityPtr e = *it;
			if (e->IsAlive()) {
				e->Draw();
			}
		}
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	if (IsSwapAfterDraw()) {
		SDL_GL_SwapBuffers();
	}
}
