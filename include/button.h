#include <3ds.h>
#include <citro2d.h>

class GUIButton{
protected:
  u16 sx; 
  u16 sy;
  u16 ex; 
  u16 ey;
public:
    

    bool isClicked(u16 x, u16 y){
        return (x >= this->sx && x <= this->ex && y >= this->sy && y <= this->ey);  
    }

    float width(){
        return this->ex-this->sx;
    }

    float height(){
        return this->ey-this->sy;
    }

    void render(float depth, u32 color){
        C2D_DrawRectSolid(sx, sy, depth, this->width(), this->height(),color);
        return;
    }
  


  GUIButton(u16 sx, u16 sy, u16 ex, u16 ey){
    this->sx = sx;
    this->ex = ex;
    this->sy = sy;
    this->ey = ey;
  }
};


class BFButton : public GUIButton{

    public:
        char* v;
        BFButton(u16 sx, u16 sy, u16 ex, u16 ey, char* v) : GUIButton(sx, sy, ex, ey){
            this->v = v;
        }

};