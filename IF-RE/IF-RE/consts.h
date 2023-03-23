#pragma once
/// NAME OF SECTION

// _Name of chapter_
// *name of paragraph*

/// <- this mean end of section



/// OBJP mean pointer on object
#define _INC_OBJP_MATRIX typedef std::vector<std::vector<Object*>> objp_matrix;
#define _INC_INT_MATRIX  typedef std::vector<std::vector<int>> int_matrix;
///



/// ENVIRONMENT
#define ENV_WIDTH  96
#define ENV_HEIGHT 44
///



/// GRAPH
// _Field_
#define CELL_SIZE 20.f 

#define HUD_HEIGHT 200.f
#define HUD_BG gui::Color::DarkGray


// *win prop*
#define WN_WIDTH	 1600
#define WN_HEIGHT	 900
#define WN_START_FPS 20
#define WN_START_MOD sf::Style::Default // or Fullscreen

// *view prop*
#define VIEW_SPEED 10


// *btn pos*
#define BTN_HORIZ_POS 40.f
#define BTN_VERT_POS  -HUD_HEIGHT + 40.f // reveres because BottomLeft
#define BTN_ANCHOR	  gui::BottomLeft

// *btn prop*
#define BTN_WITDH		100.f
#define BTN_HEIGHT		30.f
#define BTN_VERT_DEL	40.f
#define BTN_HORIZ_DEL	110.f


// _Labels_
#define STEP_LABEL_POS sf::Vector2f(3*BTN_HORIZ_DEL, BTN_VERT_POS)
#define STEP_LABEL_SIZE 30U

#define FPS_LABEL_POS sf::Vector2f(3*BTN_HORIZ_DEL, BTN_VERT_POS + BTN_VERT_DEL)
#define FPS_LABEL_SIZE 30U


// _Sliders_
#define SLD_HEIGHT 30.f
#define SLD_POSITION sf::Vector2f(5*BTN_HORIZ_DEL, BTN_VERT_POS + 2*BTN_VERT_DEL)
#define SLD_SIZE sf::Vector2f(540, BTN_WITDH)
///



/// CELLS
// _Namespases_
namespace cellType
{
	enum
	{
		Emptiness,
		Bot,
		Food,
		Corpse,
		Object
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
		_temperature
	};
}

// _Bot_
#define BOT_BRAIN_SIZE   64
#define BOT_CMD_AMOUNT   21
#define BOT_START_ENERGY 25

// _Food_
#define FOOD_ENERGY  10
#define FOOD_AMOUNT  0

// _Corpse_

///



/// OTHER
#define GENALG_MUTATION_PRECENT 0.1
#define GENALG_NUM_OUT_SELECT   8

#define DIR_UP		sf::Vector2i( 0, -1)
#define DIR_RIGHT	sf::Vector2i( 1,  0)
#define DIR_LEFT	sf::Vector2i(-1,  0)
#define DIR_DOWN	sf::Vector2i( 0,  1)

