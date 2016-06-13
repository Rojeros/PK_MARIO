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

	/* Ustawia rozmiary sprite'a powy¿ej których bêdzie on powtarzany -- rysowany ponownie.
	Wywo³anie:
	sprite->SetRepeat(.5, 1.0);
	sprite->DrawCurrentFrame(x, y, 2.0, 3.5);
	Oznacza, ¿e w poziomie sprite zostanie powtórzony czterokrotnie, a w pionie 3,5-krotnie. Ka¿dy z narysowanych
	sprite'ów (byæ mo¿e poza ostatnim) bêdzie mia³ wymiary 0.5 X 1.0

	Przypuszczalnie najczêœciej bêdzie wykorzystywane nastêpuj¹ce wywo³anie:
	sprite->SetRepeat(tile_width, tile_height);
	sprite->DrawCurrentFrame(x, y, any_width, any_height);
	Zostanie wówczas narysowany prostok¹t o wymiarach any_width X any_height wype³niony sprite'mi standartowej wielkoœci jednego kafla.

	Argumenty width oraz height powinny byæ œciœle wiêksze od 0. Zachowanie dla pozosta³ych wartoœci jest nieokreœlone.
	*/
	void SetRepeat(double width, double height);

	/* Po wywo³aniu tej metody, sprite bêdzie rozci¹gany, a nie powtarzany. */
	void ResetRepeat();

private:
	SpriteConfigData m_data;
	size_t m_current_frame;           // numer aktualnej klatki
	double m_current_frame_duration;  // czas trwania aktualnej klatki

	double m_width_repeat;            // szerokoœæ, powy¿ej której sprite bêdzie ponownie rysowany
	double m_height_repeat;           // wysokoœæ, powy¿ej której sprite bêdzie ponownie rysowany

	bool m_dark;                      // czy sprite ma byæ przyciemniony
};

typedef boost::shared_ptr<Sprite> SpritePtr;

#endif /* SPRITE_H_ */
