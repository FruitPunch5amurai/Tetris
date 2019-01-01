#include <ResourceManager.h>

#include "TetrisBlock.h"


TetrisBlock::TetrisBlock(const glm::vec2& position,
	int idCounter,
	const Rasengine::ColorRGBA8& color)
{
	m_position = position;	
	m_color = color;
	m_textureId = Rasengine::ResourceManager::GetTexture("Textures/Block.png").id;
	id = idCounter;
}
TetrisBlock::TetrisBlock()
{

}
TetrisBlock::~TetrisBlock()
{
}

void TetrisBlock::Draw(Rasengine::SpriteBatch & spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(m_position.x,
		m_position.y,
		m_width,
		m_width);
	spriteBatch.Draw(destRect, uvRect, m_textureId, 0.0f, m_color);
}





