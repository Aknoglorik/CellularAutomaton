#pragma once
/// NAME OF SECTION

// _Name of chapter_
// *name of paragraph*

/// <- this mean end of section



/// OBJP mean pointer on object
#define _INC_OBJP_MATRIX typedef std::vector<std::vector<Object*>> objp_matrix;
#define _INC_INT_MATRIX  typedef std::vector<std::vector<int>> int_matrix;
#define _INC_FLOAT_MATRIX typedef std::vector<std::vector<float>> float_matrix;
///



/// ENVIRONMENT
#define ENV_WIDTH				128
#define ENV_HEIGHT				72
#define ENV_FREQ_TEMP_UPDATE	10
#define ENV_HEAT_TRANSFER		1

/// THE FIRST TYPE OF SELECTION
#define ENV_NUM_SELECTION	60
#define ENV_NUM_DESCENDANTS 5
#define ENV_NUM_MUTATION	4

///



/// GRAPH
// _Field_
#define CELL_SIZE 20.f 

#define HUD_HEIGHT 150.f
#define HUD_BG gui::Color::DarkGray


// *win prop*
#define WN_WIDTH	 1600
#define WN_HEIGHT	 900
#define WN_START_FPS 10
#define WN_START_MOD sf::Style::Default // or Fullscreen

// *view prop*
#define VIEW_SPEED 10


// *btn pos*
#define BTN_HORIZ_POS 20.f
#define BTN_VERT_POS  -HUD_HEIGHT + 20.f // reveres because BottomLeft
#define BTN_ANCHOR	  gui::BottomLeft

// *btn prop*
#define BTN_WITDH		120.f
#define BTN_HEIGHT		30.f
#define BTN_VERT_DEL	40.f
#define BTN_HORIZ_DEL	130.f


// _Labels_
#define STEP_LABEL_POS sf::Vector2f(BTN_HORIZ_POS + 2*BTN_HORIZ_DEL, BTN_VERT_POS)
#define STEP_LABEL_SIZE 30U

#define FPS_LABEL_POS sf::Vector2f(BTN_HORIZ_POS + 2*BTN_HORIZ_DEL, BTN_VERT_POS + BTN_VERT_DEL)
#define FPS_LABEL_SIZE 30U


// _Sliders_
#define SLD_HEIGHT 30.f
#define SLD_POSITION sf::Vector2f(BTN_HORIZ_POS + 4*BTN_HORIZ_DEL, BTN_VERT_POS + BTN_VERT_DEL)
#define SLD_SIZE sf::Vector2f(2*BTN_HORIZ_DEL - 10.f, SLD_HEIGHT)


// _Dialog win_
#define DLG_HEAD_BAR	30.f
#define DLG_LB_SIZE		14.f
#define DLG_POS			sf::Vector2f(0, 0)
#define DLG_SIZE		sf::Vector2f(200, 300)
#define DLG_CMD_MARGIN  6.f

///



/// CELLS
// _Namespases_
namespace cellType
{
	enum cell
	{
		Emptiness,
		Bot,
		Food,
		Corpse,
		Object,
		Wall
	};
}

namespace botMove
{
	enum
	{
		up,
		up_right,
		right,
		down_right,
		down,
		down_left,
		left,
		up_left
	};
}

namespace botCmd
{
	enum
	{
		move,
		eat,
		photosynthesis,
		nothing,
		gemmation
	};
}

namespace operatingMode
{
	enum Mode
	{
		_default,
		_temperature,
		_energy,
		_botType
	};
}

// 1, 2, 4, 8...
namespace botSpriteType
{
	inline char prey = 1;
	inline char predator = 2;
	inline char corpse_eater = 4;
}

// _Bot_
#define BOT_BRAIN_SIZE   64
#define BOT_CMD_AMOUNT   64
#define BOT_START_ENERGY 30

#define BOT_MAX_ENERGY	 200
#define BOT_MAX_LIFE	 200
#define BOT_EAT_RATIO	 0.8f

#define BOT_DIGEST_RATIO 2.f
#define BOT_DIGEST_SPEED 0.1f

#define BOT_NRG_TO_MOVE  0
#define BOT_NRG_TO_EAT   0

// _Food_
#define FOOD_ENERGY			10
#define FOOD_AMOUNT			200000
#define FOOD_REDUCE_TEMP	1

// _Corpse_

///



/// OTHER
#define GENALG_MUTATION_PRECENT 0.5
#define GENALG_NUM_OUT_SELECT   8

#define DIR_UP		sf::Vector2i( 0, -1)
#define DIR_RIGHT	sf::Vector2i( 1,  0)
#define DIR_LEFT	sf::Vector2i(-1,  0)
#define DIR_DOWN	sf::Vector2i( 0,  1)

