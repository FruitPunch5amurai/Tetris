#pragma once
#include <GLM/glm.hpp>
#include <Vertex.h>
#include <SpriteBatch.h>
class TetrisBlock
{
	public:
		TetrisBlock(const glm::vec2& position,
			int idCounter,
			const Rasengine::ColorRGBA8& color);
		TetrisBlock();
		~TetrisBlock();

		void Draw(Rasengine::SpriteBatch& spriteBatch);
		void SetIndex(int index) { m_cellIndex = index; }
		void SetPosition(const glm::vec2 &pos) { m_position = pos; }
		void SetCellPosition(const glm::ivec2 &pos) { m_cellPosition = pos; }
		glm::vec2 GetPosition() { return m_position; }
		glm::ivec2 GetCellPosition() { return m_cellPosition; }
	private:
		Rasengine::ColorRGBA8 m_color;
		
		int m_width = 24;
		int m_cellIndex;
		int id = 0;
		
		GLuint m_textureId;

		glm::vec2 m_position;
		glm::ivec2 m_cellPosition;
		
		bool inPlay = true;

		friend class TetrisPiece;
};
