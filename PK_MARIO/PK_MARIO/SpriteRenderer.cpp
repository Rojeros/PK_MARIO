#include "StdAfx.h"
#include "SpriteRenderer.h"
GLuint SpriteRenderer::m_texture;
std::string SpriteRenderer::filename;

void SpriteRenderer::setFilename(std::string path)
{
	filename = path;
}

double SpriteRenderer::GetTileWidth()
{
	return m_tile_width;
}
double SpriteRenderer::GetTileHeight()
{
	return m_tile_height;
}
size_t SpriteRenderer::GetHorizontalTilesOnScreenCount()
{
	return 1.0 / m_tile_width + 0.5;
}
size_t SpriteRenderer::GetVerticalTilesOnScreenCount()
{
	return 1.0 / m_tile_height + 0.5;
}
void SpriteRenderer::SetTileSize(double width, double height)
{
	m_tile_width = width;
	m_tile_height = height;
}

void SpriteRenderer::LoadTexture()
{
	// za³aduj z pliku
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (!surface)
	{
		std::cerr << "file error " + filename + " FAILED: " + SDL_GetError() + "\n";
		exit(1);
	}

	// sprawdŸ wymiary - czy s¹ potêg¹ 2
	const int width = surface->w;
	const int height = surface->h;
	if (((width & (width - 1)) != 0) || ((height & (height - 1)) != 0))
	{
		std::cerr << "Picture " + filename+ " have inccorect size: " << width << "x"
			<< height << "\n";
		exit(1);
	}

	GLenum format;
	switch (surface->format->BytesPerPixel)
	{
	case 3:
		format = GL_BGR;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		std::cerr << "wrong file extension " + filename + "\n";
		exit(1);
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, surface->format->BytesPerPixel, width, height, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

	if (surface)
	{
		SDL_FreeSurface(surface);
	}
}



void SpriteRenderer::DrawSprite(double tex_x, double tex_y, double tex_w, double tex_h,
	double pos_x, double pos_y, double width, double height, TYPES::DisplayLayer layer)
{
	if (m_texture <= 0)
		LoadTexture();

	glBindTexture(GL_TEXTURE_2D, m_texture);

	const double texture_w = 1024.0;
	const double texture_h = 1024.0;

	
	const double left = tex_x / texture_h;;
	const double right = left + tex_w / texture_w;
	const double bottom = (tex_y/texture_h);
	const double top = bottom - tex_h / texture_h;
	/*
	* Obrazek ³adowany jest do góry nogami, wiêc punkt (0,0) jest w lewym górnym rogu.
	* St¹d wynika, ¿e w powy¿szym wzorze top jest poni¿ej bottom
	*/
	//glColor3f(1, 1, 1);
//	glPushMatrix();

//	{
//		glTranslatef(0, 0, -static_cast<double> (layer));
	//	glBindTexture(GL_TEXTURE_2D, m_texture);
		glBegin(GL_QUADS);
		glColor4f(1, 1, 1,0.5);
	//	{
			glTexCoord2f(right, top);    glVertex2f(pos_x + width, pos_y + height);
			glTexCoord2f(left, top);     glVertex2f(pos_x, pos_y + height);
			glTexCoord2f(left, bottom);  glVertex2f(pos_x, pos_y);
			glTexCoord2f(right, bottom); glVertex2f(pos_x + width, pos_y);
	//	}
		glEnd();
		glDisable(GL_BLEND);
//	}
	glPopMatrix();
}
