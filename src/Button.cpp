#include "Button.h"

#define DEBUG 0
#ifdef DEBUG
    #define DEBUG_PRINT(x) do{ std::cout << x <<  std::endl; }while(0);
#else
    #define DEBUG_PRINT(x)
#endif // DEBUG

Button::Button(GameObject& associated, string path):
    sp(new Sprite(associated, path))
{
    associated.AddComponent(sp);
    sp->SetPosition(associated.box.x, associated.box.y + 50 );
    DEBUG_PRINT("Botao sera renderizado em: " << sp->GetScreenX() << "x" << sp->GetScreenY());
    //ctor
}

Button::~Button()
{
    //dtor
}

bool Button::Is(ComponentType type) const{
    return (BUTTON == type);
}


#ifdef DEBUG
    #undef DEBUG
#endif
