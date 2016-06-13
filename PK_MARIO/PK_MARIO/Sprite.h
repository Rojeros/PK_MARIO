#ifndef SPRITE_H_
#define SPRITE_H_
#include "StdAfx.h"

#include "SpriteConfig.h"


class Sprite {
public:
	explicit Sprite(const SpriteConfigData& data);

	void Update(double dt);
	void SetCurrentFrame(size_t frame_num);
	void DrawCurrentFrame(double x, double y, double width, double height);

	/* Ustawia rozmiary sprite'a powy�ej kt�rych b�dzie on powtarzany -- rysowany ponownie.
	Wywo�anie:
	sprite->SetRepeat(.5, 1.0);
	sprite->DrawCurrentFrame(x, y, 2.0, 3.5);
	Oznacza, �e w poziomie sprite zostanie powt�rzony czterokrotnie, a w pionie 3,5-krotnie. Ka�dy z narysowanych
	sprite'�w (by� mo�e poza ostatnim) b�dzie mia� wymiary 0.5 X 1.0

	Przypuszczalnie najcz�ciej b�dzie wykorzystywane nast�puj�ce wywo�anie:
	sprite->SetRepeat(tile_width, tile_height);
	sprite->DrawCurrentFrame(x, y, any_width, any_height);
	Zostanie w�wczas narysowany prostok�t o wymiarach any_width X any_height wype�niony sprite'mi standartowej wielko�ci jednego kafla.

	Argumenty width oraz height powinny by� �ci�le wi�ksze od 0. Zachowanie dla pozosta�ych warto�ci jest nieokre�lone.
	*/
	void SetRepeat(double width, double height);

	/* Po wywo�aniu tej metody, sprite b�dzie rozci�gany, a nie powtarzany. */
	void ResetRepeat();

private:
	SpriteConfigData m_data;
	size_t m_current_frame;           // numer aktualnej klatki
	double m_current_frame_duration;  // czas trwania aktualnej klatki

	double m_width_repeat;            // szeroko��, powy�ej kt�rej sprite b�dzie ponownie rysowany
	double m_height_repeat;           // wysoko��, powy�ej kt�rej sprite b�dzie ponownie rysowany

	bool m_dark;                      // czy sprite ma by� przyciemniony
};

typedef boost::shared_ptr<Sprite> SpritePtr;

#endif /* SPRITE_H_ */
