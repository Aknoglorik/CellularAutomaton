#pragma once
/// NAME OF SECTION

// _Name of chapter_
// *name of paragraph*

/// <- this mean end of section

/// OBJP mean pointer on object
#define _INC_OBJP_MATRIX typedef std::vector<std::vector<Object*>> objp_matrix;
#define _INC_INT_MATRIX  typedef std::vector<std::vector<int>> int_matrix;


/// ENVIRONMENT
#define ENV_WIDTH  30
#define ENV_HEIGHT 30

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
		nothing
	};
}


// _Bot_
#define BOT_BRAIN_SIZE   18
#define BOT_START_ENERGY 25

// _Food_
#define FOOD_ENERGY  10
#define FOOD_AMOUNT  10
#define FOOD_FOR_BOT 10

// _Corpse_

///



/// GRAPH
// _Win prop_
#define WN_WIDTH	 1920
#define WN_HEIGHT	 1080
#define WN_START_FPS 20


// _Field_
#define CELL_SIZE 20.f 

// *btn pos*
#define BTN_HORIZ_POS 1600.f
#define BTN_VERT_POS  50.f

// *btn prop*
#define BTN_WITDH		100.f
#define BTN_HEIGHT		30.f
#define BTN_VERT_DEL	40.f
#define BTN_HORIZ_DEL	110.f


// _Labels_
#define STEP_LABEL_POS sf::Vector2f(240.f, 0.f)
#define STEP_LABEL_SIZE 40U

#define FPS_LABEL_POS sf::Vector2f(0.f, 0.f)
#define FPS_LABEL_SIZE 40U
///



/// OTHER
#define GENALG_MUTATION_PRECENT 0.25
#define GENALG_NUM_OUT_SELECT   8

#define DIR_UP		sf::Vector2i( 0, -1)
#define DIR_RIGHT	sf::Vector2i( 1,  0)
#define DIR_LEFT	sf::Vector2i(-1,  0)
#define DIR_DOWN	sf::Vector2i( 0,  1)

