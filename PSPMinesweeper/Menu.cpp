#include "Menu.h"
#include "Ressource.h"
#include "Game.h"
#include "Save.h"
#include "rules.h"

Menu::Menu()
{
  getExternalData();
  item_ = 1;
  level_ = EASY;
  mode_ = CLASSIC;
  size_.x = EASY_LENGTH;
  size_.y = EASY_HEIGHT;
  mines_ = EASY_MINES;
  is_fadingin_ = true;
  is_fadingout_ = false;
  fade_alpha_ = 0xFF;
}

void Menu::getExternalData() 
{
  click_ = Ressource::GetInstance()->click_;
  backgroundpic_ = Ressource::GetInstance()->backgroundpic_;
  ltn_ = Ressource::GetInstance()->ltn_;
}

void Menu::update(OSL_CONTROLLER* pad)
{
  if (!is_fadingout_) {
    if (pad->pressed.down) {
      oslPlaySound(click_, 1);
      item_++;
      if (item_ == 10) {item_ = 1;}
      if ((item_ == 4) && (level_ != CUSTOM)) {item_ = 7;}
    }
    if (pad->pressed.up) {
      oslPlaySound(click_, 1);
      item_--; 
      if (item_ == 0) {item_ = 9;}
      if ((item_ == 6) && (level_ != CUSTOM)) {item_ = 3;}
    }
    if (pad->pressed.right) {
      oslPlaySound(click_, 1);
      if ((level_ == CUSTOM) && (mode_ == CLASSIC)) {
        if (item_ == 4) {
          size_.x++;
          if (size_.x > MAX_LENGTH) {size_.x = MAX_LENGTH;}
        }
        if (item_ == 5) {
          size_.y++;
          if (size_.y > MAX_HEIGHT) {size_.y = MAX_HEIGHT;}
        }
        min_mines_ = (size_.y * size_.x) / 10;
        max_mines_ = (size_.y * size_.x) / 3;
        if (mines_ < min_mines_) {mines_ = min_mines_;}
        if (item_ == 6) {
          mines_++;
          if (mines_ > max_mines_) {mines_ = max_mines_;}
        }
      }
      if (item_ == 2) {
        mode_++;
        if (mode_ == (SURVIVAL + 1)) {mode_ = SURVIVAL;}
        if (mode_ == SURVIVAL) {
          if (level_ == CUSTOM) {
            level_ = EASY;
            mines_ = 12;
            size_.x = 10;
            size_.y = 10;
          }
        }
      }
      if (item_ == 3) {
        level_++;
        if (level_ == (HARD + 1)) {level_ = HARD;}
        if (level_ == EASY) {
          mines_ = 12;
          size_.x = 10;
          size_.y = 10;
        }
        if (level_ == MEDIUM) {
          mines_ = 25;
          size_.x = 15;
          size_.y = 12;
        } 
        if (level_ == HARD) {
          mines_ = 70;
          size_.x = 26;
          size_.y = 13;
        }  
      }
    }
    if (pad->pressed.left) {
      oslPlaySound(click_, 1);
      if ((level_ == CUSTOM) && (mode_ == CLASSIC)) {
        if (item_ == 4) {
          size_.x--;
          if (size_.x < MIN_LENGTH) {size_.x = MIN_LENGTH;}
        }
        if (item_ == 5) {
          size_.y--;
          if (size_.y < MIN_HEIGHT) {size_.y = MIN_HEIGHT;}
        }
        min_mines_ = (size_.y * size_.x) / 10;
        max_mines_ = (size_.y * size_.x) / 3;
        if (mines_ > max_mines_) {mines_ = max_mines_;}
        if (item_ == 6) {
          mines_--;
          if (mines_ < min_mines_) {mines_ = min_mines_;}
        }
      }
      if (item_ == 2) {
        mode_--;
        if (mode_ == (CLASSIC - 1)) {mode_ = CLASSIC;}
        if (mode_ == SURVIVAL) {
          if (level_ == CUSTOM) {
            level_ = EASY;
            mines_ = 12;
            size_.x = 10;
            size_.y = 10;
          }
        }
      }
      if (item_ == 3) {
        level_--;
        if ((level_ == CUSTOM) && (mode_ == SURVIVAL)) {level_ = CUSTOM + 1;}
        if (level_ == (CUSTOM - 1)) {level_ = CUSTOM;}
        if (level_ == EASY) {
          mines_ = 12;
          size_.x = 10;
          size_.y = 10;
        }
        if (level_ == MEDIUM) {
          mines_ = 25;
          size_.x = 15;
          size_.y = 12;
        } 
        if (level_ == HARD) {
          mines_ = 70;
          size_.x = 26;
          size_.y = 13;
        }
      }
    }
    if (pad->pressed.cross) {
      oslPlaySound(click_, 1);
      if (item_ == 1) {
        newGame();
      }
      if (item_ == 7) {
        scoresMenu();
      }
      if (item_ == 8) {
        helpMenu();
      }
      if (item_ == 9) {
        is_fadingout_ = true;
        fade_alpha_ = 15;
      }
    }
  }
}

void Menu::display()
{
  oslDrawImage(backgroundpic_);
  oslDrawFillRect(0, 42, 480, 232, 0x6F000000);
  intraFontSetStyle(ltn_, 0.5f, 0xF0F0F0F0, BLACK, INTRAFONT_ALIGN_RIGHT);
  intraFontPrint(ltn_, 470, 225, VERSION_TEXT);
  intraFontSetStyle(ltn_, 0.7f, WHITE, blinkingEffect(item_, 1), INTRAFONT_ALIGN_CENTER);
  intraFontPrint(ltn_, 240, 60, "New game");
  intraFontSetStyle(ltn_, 0.7f, WHITE, blinkingEffect(item_, 2), INTRAFONT_ALIGN_CENTER);      
  switch (mode_)
  {
    case CLASSIC:intraFontPrint(ltn_, 240, 80, "Mode: Classic");break;
    case SURVIVAL:intraFontPrint(ltn_, 240, 80, "Mode: Survival");break;
    default:intraFontPrint(ltn_, 240, 80, "Mode: Error");break;
  }       
  intraFontSetStyle(ltn_, 0.7f, WHITE, blinkingEffect(item_, 3), INTRAFONT_ALIGN_CENTER);
  switch (level_)
  {
    case CUSTOM:intraFontPrint(ltn_, 240, 100, "Difficulty: Custom");break;
    case EASY:intraFontPrint(ltn_, 240, 100, "Difficulty: Easy");break;
    case MEDIUM:intraFontPrint(ltn_, 240, 100, "Difficulty: Medium");break;
    case HARD:intraFontPrint(ltn_, 240, 100, "Difficulty: Hard");break;
    default:intraFontPrint(ltn_, 240, 100, "Difficulty: Error");break;
  }
  if ((level_ == CUSTOM) && (mode_ == CLASSIC)) {
    intraFontSetStyle(ltn_, 0.7f, WHITE, blinkingEffect(item_, 4), INTRAFONT_ALIGN_CENTER);
  } else {
    intraFontSetStyle(ltn_, 0.7f, GRAY, BLACK, INTRAFONT_ALIGN_CENTER);
  }        
  intraFontPrintf(ltn_, 240, 120, "Length <%i>", size_.x);
  if ((level_ == CUSTOM) && (mode_ == CLASSIC)) {
    intraFontSetStyle(ltn_, 0.7f, WHITE, blinkingEffect(item_, 5), INTRAFONT_ALIGN_CENTER);
  } else {
    intraFontSetStyle(ltn_, 0.7f, GRAY, BLACK, INTRAFONT_ALIGN_CENTER);
  }
  intraFontPrintf(ltn_, 240, 140, "Height <%i>", size_.y);
  if ((level_ == CUSTOM) && (mode_ == CLASSIC)) {
    intraFontSetStyle(ltn_, 0.7f, WHITE, blinkingEffect(item_, 6), INTRAFONT_ALIGN_CENTER);
  } else {
    intraFontSetStyle(ltn_, 0.7f, GRAY, BLACK, INTRAFONT_ALIGN_CENTER);
  }
  intraFontPrintf(ltn_, 240, 160, "Mines <%i>", mines_);
  intraFontSetStyle(ltn_, 0.7f, WHITE, blinkingEffect(item_, 7), INTRAFONT_ALIGN_CENTER);
  intraFontPrint(ltn_, 240, 180, "Highscores");
  intraFontSetStyle(ltn_, 0.7f, WHITE, blinkingEffect(item_, 8), INTRAFONT_ALIGN_CENTER);
  intraFontPrint(ltn_, 240, 200, "How to play ?");
  intraFontSetStyle(ltn_, 0.7f, WHITE, blinkingEffect(item_, 9), INTRAFONT_ALIGN_CENTER);
  intraFontPrint(ltn_, 240, 220, "Quit game");
  if (is_fadingin_) {
    oslDrawFillRect(0, 0, 480, 272, (fade_alpha_<<24));
    fade_alpha_ -= 16;
    if (fade_alpha_ < 0) {
      is_fadingin_ = false;
    }
  }
  if (is_fadingout_) {
    oslDrawFillRect(0, 0, 480, 272, (fade_alpha_<<24));
    fade_alpha_ += 16;
    if (fade_alpha_ > 0xFF) {
      osl_quit = true;
    }
  }
}

void Menu::newGame()
{
  int skip = 0;
  OSL_CONTROLLER* pad = oslReadKeys();
  Game game(size_.x, size_.y, mines_, mode_, level_);
  while ((!osl_quit) && (!game.isFinished())) {
    if (!skip) {
      pad = oslReadKeys();
      game.update(pad);
      oslStartDrawing();
      game.display();
      oslEndDrawing();
    }
    oslEndFrame();
    skip = oslSyncFrame();
  } 
}

void Menu::scoresMenu()
{
  int skip = 0;
  OSL_CONTROLLER* pad = oslReadKeys();
  scoreboard scores;
  bool loaded = false;
  {
    Savemanager save;
    loaded = save.isLoaded();
    if (loaded) {
      scores = save.getHighscores();
    }
  }
  while ((!osl_quit) && (!pad->pressed.cross)) {
    if (!skip) {
      pad = oslReadKeys();
      oslStartDrawing();
      oslDrawImage(backgroundpic_);
      oslDrawFillRect(0, 42, 480, 232, 0x6F000000);
      oslDrawFillRect(0, 42, 480, 70, 0x6F000000);
      intraFontSetStyle(ltn_, 0.7f, WHITE, BLACK, INTRAFONT_ALIGN_LEFT);
      intraFontPrint(ltn_, 10, 60, "High Scores");
      if (loaded) {
        intraFontSetStyle(ltn_, 0.8f, GOLD, BLACK, INTRAFONT_ALIGN_CENTER);
        intraFontPrint(ltn_, 130, 100, "Classic Mode");
        intraFontPrint(ltn_, 350, 100, "Survival Mode");
        
        intraFontSetStyle(ltn_, 0.7f, WHITE, BLACK, INTRAFONT_ALIGN_RIGHT);
        intraFontPrint(ltn_, 125, 130, "Easy:");
        intraFontPrint(ltn_, 125, 155, "Medium:");
        intraFontPrint(ltn_, 125, 180, "Hard:");
        
        intraFontPrint(ltn_, 345, 130, "Easy:");
        intraFontPrint(ltn_, 345, 155, "Medium:");
        intraFontPrint(ltn_, 345, 180, "Hard:");
        
        intraFontSetStyle(ltn_, 0.7f, WHITE, BLACK, INTRAFONT_ALIGN_LEFT);
        //Classic
        timeToText(scores.classic[0], temp_text_);

        intraFontPrint(ltn_, 130, 130, temp_text_);
        timeToText(scores.classic[1], temp_text_);
        intraFontPrint(ltn_, 130, 155, temp_text_);
        timeToText(scores.classic[2], temp_text_);
        intraFontPrint(ltn_, 130, 180, temp_text_);
        //Survival
        timeToText(scores.survival[0], temp_text_);
        intraFontPrint(ltn_, 350, 130, temp_text_);
        timeToText(scores.survival[1], temp_text_);
        intraFontPrint(ltn_, 350, 155, temp_text_);
        timeToText(scores.survival[2], temp_text_);
        intraFontPrint(ltn_, 350, 180, temp_text_);
      } else {
        intraFontSetStyle(ltn_, 0.7f, RED, BLACK, INTRAFONT_ALIGN_CENTER);
        intraFontPrint(ltn_, 240, 110, "Unable to load high-score file !");
        intraFontSetStyle(ltn_, 0.7f, RED, BLACK, INTRAFONT_ALIGN_LEFT);
        intraFontPrint(ltn_, 20, 130, "> Memory Stick may be unplugged");
        intraFontPrint(ltn_, 20, 150, "> Check if PSP/GAME/PSPMinesweeper/ms.data exists");
        intraFontSetStyle(ltn_, 0.7f, RED, BLACK, INTRAFONT_ALIGN_CENTER);
        intraFontPrint(ltn_, 240, 190, "High-scores won't be saved for now");
      }
      intraFontSetStyle(ltn_, 0.5f, WHITE, blinkingEffect(1, 1), INTRAFONT_ALIGN_RIGHT);
      intraFontPrint(ltn_, 470, 224, "Press Cross");
      oslEndDrawing();
    }
    oslEndFrame();
    skip = oslSyncFrame();
  }
}

void Menu::helpMenu()
{
  int skip = 0;
  OSL_CONTROLLER* pad = oslReadKeys();
  while ((!osl_quit) && (!pad->pressed.cross)) {
    if (!skip) {
      pad = oslReadKeys();
      oslStartDrawing();
      oslDrawImage(backgroundpic_);
      oslDrawFillRect(0, 42, 480, 232, 0x6F000000);
      oslDrawFillRect(0, 42, 480, 70, 0x6F000000);
      intraFontSetStyle(ltn_, 0.7f, WHITE, BLACK, INTRAFONT_ALIGN_LEFT);
      intraFontPrint(ltn_, 10, 60, "How to play ?");
      intraFontPrint(ltn_, 20, 100, "Cross: Discover");
      intraFontPrint(ltn_, 20, 120, "Square: Put flag/question mark");
      intraFontPrint(ltn_, 20, 140, "Triangle: Pause");
      intraFontPrint(ltn_, 20, 160, "Circle: Accelerate mouse");
      intraFontPrint(ltn_, 20, 180, "Analog/D-Pad: move mouse");
      intraFontSetStyle(ltn_, 0.5f, WHITE, blinkingEffect(1, 1), INTRAFONT_ALIGN_RIGHT);
      intraFontPrint(ltn_, 470, 224, "Press Cross");
      intraFontSetStyle(ltn_, 0.5f, WHITE, BLACK, INTRAFONT_ALIGN_LEFT);
      intraFontPrint(ltn_, 10, 224, "See also:  http://code.google.com/p/ryp-project/");
      oslEndDrawing();
    }
    oslEndFrame();
    skip = oslSyncFrame();
  }
}
