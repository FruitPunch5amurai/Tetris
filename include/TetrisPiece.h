#pragma once
#include <GLM/glm.hpp>
#include <vector>
#include <Vertex.h>
#include "TetrisBlock.h"
#include "TetrisCell.h"
enum class TetrisType {
	I_Block,
	J_Block,
	L_Block,
	O_Block,
	S_Block,
	T_Block,
	Z_Block,
	SINLGE
};

class TetrisPiece {

	public:
		TetrisPiece();
		~TetrisPiece();

		void CreateTetrisPiece(const glm::vec2& position,TetrisCell* cells,TetrisType type,int idCounter);
		std::vector<TetrisBlock*> GetTetrisBlocks() { return m_tetrisBlocks; }
		bool Update(float deltaTime,
			float fallSpeed,
			float collisionSpeed,
			TetrisCell* tetrisCells);
		bool CheckCollision(TetrisBlock* block,
			TetrisCell* tetrisCells);
		void MoveTetrisPiece(TetrisCell* tetrisCells,const glm::vec2& dir);
		void SpeedFall(TetrisCell* tetrisCells);
		void MoveDown(TetrisCell* tetrisCells);
		void Rotate(TetrisCell* cells, const glm::vec2& containerPosition, bool isRight);


		bool isFalling = true;

	private:

		float m_frameCounter = 0;
		float m_collisionFrameCounter = 0;

		bool didCollide = false;

		TetrisBlock* m_pivot;
		glm::vec2 m_position;
		Rasengine::ColorRGBA8 m_color;
		TetrisType m_type;
		std::vector<TetrisBlock*> m_tetrisBlocks;

		bool CanSpawn(TetrisCell* cells, const glm::vec2 &pos);
		void ResolveBorderCollision(TetrisBlock* rotatedBlocks, TetrisCell* tetrisCells);
		bool CheckRotationCollision(TetrisBlock* rotatedBlocks, TetrisCell* tetrisCells);
		bool CanMoveLeft(TetrisBlock* rotatedBlocks, TetrisCell* tetrisCells);
		bool CanMoveRight(TetrisBlock* rotatedBlocks, TetrisCell* tetrisCells);
		bool CanMoveUp(TetrisBlock* rotatedBlocks, TetrisCell* tetrisCells);
};