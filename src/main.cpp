#include <stdio.h>
#include "button.h"


//----------------------------------------//
//          Brainfuck interpreter         //
//----------------------------------------//
int m[30000], *d=m, t;                    //
void bfi(char *p) {                       //
  for (; *p != 0 ; p++) {                 //
    switch (*p) {                         //
    case '>': ++d; break;                 //
    case '<': --d; break;                 //
    case '+': ++*d; break;                //
    case '-': --*d; break;                //
    case '.': putchar(*d); break;         //
    case ',': *d = getchar(); break;      //
    case '[':                             //
      if (*d == 0) {                      //
        for (t = 1; t != 0;) {            //
          ++p;                            //
          if (*p == '[') ++t;             //
          else if (*p == ']') --t;        //
        }                                 //
      }                                   //
      break;                              //
    case ']':                             //
      for (t = 1; t != 0;) {              //
        --p;                              //
        if (*p == '[') --t;               //
        else if (*p == ']') ++t;          //
      }                                   //
      --p;                                //
      break;                              //
    }                                     //
  }                                       //
}                                         //
//----------------------------------------//

int main(int argc, char* argv[]){
  gfxInitDefault();
  C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
  C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
  C2D_Prepare();
  consoleInit(GFX_TOP, NULL);

  char charlist[2000];

  C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
  
  u32 white = C2D_Color32(0xFF, 0xFF, 0xFF,0xFF);
  u32 black = C2D_Color32(0,0,0, 0xFF);
  u32 blue = C2D_Color32(0x0, 0x0, 0xFF, 0xFF);
  u32 red = C2D_Color32(0xFF, 0x0, 0x0, 0xFF);

  bool hasTouched = false;

  BFButton blist[8] = {
    BFButton(40,20,80,60,">"),
    BFButton(106,20,146,60,"<"),
    BFButton(173,20,213,60,"+"),
    BFButton(240,20,280,60,"-"),
    BFButton(40,80,80,120,"."),
    BFButton(106,80,146,120,","),
    BFButton(173,80,213,120,"["),
    BFButton(240,80,280,120,"]")
  };

  //GUIButton left(70, 140, 145, 180);
  //GUIButton right(70, 140, 145, 180);

  GUIButton bexe(37, 190, 112, 230);
  GUIButton bremove(122, 190, 197, 230);
  GUIButton breset(207, 190, 282, 230);

  printf("\x1b[0;0HPress Start to exit.");
  printf("\x1b[2;0HIs button touched?");

  while (aptMainLoop()){

		hidScanInput();
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break;

		touchPosition touch;
		hidTouchRead(&touch);

    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(bottom, white);
		C2D_SceneBegin(bottom);
    for (int i = 0; i < 8; i++){
      if (blist[i].isClicked(touch.px,touch.py) && hasTouched){
        blist[i].render(0, black);
        printf(blist[i].v);
        strcat(charlist, blist[i].v);
      } else {
        blist[i].render(0, blue);
      }
    }
    bexe.render(0, blue);
    bremove.render(0, blue);
    breset.render(0, red);
    if (bexe.isClicked(touch.px, touch.py) && hasTouched){
      printf("Output : \n");
      bfi(charlist);
      printf("\n");
    }

    if (!hasTouched && touch.px != 0 && touch.py != 0){
      hasTouched = true;
    } else if ( touch.px == 0 && touch.py == 0 && hasTouched){
      hasTouched = false;
    }

    C3D_FrameEnd(0);
	}

	C2D_Fini();
	C3D_Fini();
	gfxExit();
  return 0;
}
