#include <ResourceManager.h>
#include "TetrisCell.h"

TetrisCell::TetrisCell()
{
	m_textureId = Rasengine::ResourceManager::GetTexture("Textures/cell.png").id;
}

TetrisCell::~TetrisCell()
{
}

void TetrisCell::Draw(Rasengine::SpriteBatch & spriteBatch,int width, Rasengine::ColorRGBA8 color)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(m_position.x,
		m_position.y,
		width,
		width);
	spriteBatch.Draw(destRect, uvRect, m_textureId, 0.0f, color);
}
