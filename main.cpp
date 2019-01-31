//
// Copyright (c) 2005, Wei Mingzhi <whistler@openoffice.org>
// All Rights Reserved.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301, USA
//

#include "main.h"

SDL_Window *gpWindow = NULL;
SDL_Renderer *grenderer = NULL;
SDL_Surface *gpScreen = NULL;
SDL_Texture *sdlTexture = NULL;

bool g_fNoSound = false;
bool g_fNoMusic = false;

int main(int argc, char *argv[])
{
   LoadCfg(); // load the configuration file

   // Initialize defaults, video and audio
   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE) == -1) { 
      fprintf(stderr, "FATAL ERROR: Could not initialize SDL: %s.\n", SDL_GetError());
      exit(1);
   }

   // Initialize the TTF library
   if (TTF_Init() < 0) {
      fprintf(stderr, "FATAL ERROR: Couldn't initialize TTF: %s\n", SDL_GetError());
      exit(1);
   }
   gpWindow = SDL_CreateWindow("Majong",
	   SDL_WINDOWPOS_UNDEFINED,
	   SDL_WINDOWPOS_UNDEFINED,
	   640, 480,
	   SDL_WINDOW_SHOWN);

   grenderer = SDL_CreateRenderer(gpWindow, -1, 0);

   gpScreen = SDL_CreateRGBSurface(0, 640, 480, 32,
	   0x00FF0000,
	   0x0000FF00,
	   0x000000FF,
	   0xFF000000);
 

 
   if (gpScreen == NULL) {
	   fprintf(stderr, "FATAL ERROR: Could not set video mode: %s\n", SDL_GetError());
	   exit(1);
   }


   g_fNoSound = (atoi(cfg.Get("OPTIONS", "NoSound", "0")) > 0);
   g_fNoMusic = (atoi(cfg.Get("OPTIONS", "NoMusic", "0")) > 0);

   // Open the audio device
   if (!g_fNoSound || !g_fNoMusic) {
      if (Mix_OpenAudio(22050, AUDIO_S16, 1, 1024) < 0) {
         fprintf(stderr, "WARNING: Couldn't open audio: %s\n", SDL_GetError());
         g_fNoSound = g_fNoMusic = true;
      }
   }

   gpGeneral = new CGeneral;
   gpGame = new CGame;
   if (gpGame == NULL || gpGeneral == NULL)
      TerminateOnError("Not enough memory!");

   InitTextMessage();

   gpGame->RunGame();

   UserQuit();

   return 255;
}

void UserQuit()
{
   if (gpScreen != NULL)
	   SDL_FreeSurface(gpScreen);

   if (sdlTexture != NULL)
   {
	   SDL_DestroyTexture(sdlTexture);
   }

   if (grenderer != NULL) {
	   SDL_DestroyRenderer(grenderer);
   }

   if (gpWindow != NULL) {
	   SDL_DestroyWindow(gpWindow);
   }



   if (gpGeneral != NULL)
      delete gpGeneral;

   if (gpGame != NULL)
      delete gpGame;

   SDL_Quit();
   TTF_Quit();

   FreeTextMessage();

   exit(0);
}

