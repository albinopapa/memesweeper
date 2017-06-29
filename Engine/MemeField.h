#pragma once

#include "Graphics.h"
#include "Sound.h"

class MemeField
{
public:
	enum class State
	{
		Fucked,
		Winrar,
		Memeing
	};
	enum class Size
	{
		Small, Medium, Large
	};
private:
	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed
		};
	public:
		void SpawnMeme();
		bool HasMeme() const;
		void Draw( const Vei2& screenPos,MemeField::State fucked,Graphics& gfx ) const;
		void Reveal();
		bool IsRevealed() const;
		void ToggleFlag();
		bool IsFlagged() const;
		bool HasNoNeighborMemes() const;
		void SetNeighborMemeCount( int memeCount );
	private:
		State state = State::Hidden;
		bool hasMeme = false;
		int nNeighborMemes = -1;
	};
public:
	MemeField( const Vei2& center );
	~MemeField();

	void Draw( Graphics& gfx ) const;
	RectI GetRect() const;
	void OnRevealClick( const Vei2& screenPos );
	void OnFlagClick( const Vei2& screenPos );
	State GetState() const;
	void SetSize( Size FieldSize );
	
private:
	void SetupField();
	void RevealTile( const Vei2& gridPos );
	Tile& TileAt( const Vei2& gridPos );
	const Tile& TileAt( const Vei2& gridPos ) const;
	Vei2 ScreenToGrid( const Vei2& screenPos );
	int CountNeighborMemes( const Vei2& gridPos );
	bool GameIsWon() const;
private:
	static constexpr int sm_width = 8;
	static constexpr int sm_height = 6;
	static constexpr int sm_nMemes = 4;

	static constexpr int md_width = 16;
	static constexpr int md_height = 12;
	static constexpr int md_nMemes = sm_nMemes * 4;

	static constexpr int lg_width = 32;
	static constexpr int lg_height = 24;
	static constexpr int lg_nMemes = md_nMemes * 4;

	static constexpr int borderThickness = 10;
	static constexpr Color borderColor = Colors::Blue;

	int width = sm_width, height = sm_height;

	Sound sndLose = Sound( L"spayed.wav" );
	Vei2 topLeft, center;
	State state = State::Memeing;
	Tile *pField = nullptr;
	int nMemes = 0;
};