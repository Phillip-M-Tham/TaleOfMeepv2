#include <math.h>
#include <stdlib.h>
#include "wolf.h"
#include "space.h"
#include "spawn.h"
#include "player.h"
#include "audio.h"
#include "entity.h"
#include "particle.h"
#include "projectiles.h"
#include "weapons.h"


extern Entity *ThePlayer;
extern Level level;
extern int Nextlevel;
extern int lvl;
extern void Init_All();
extern void GiveInfo();
extern void CleanUpAll();
Entity *Wolf=NULL;

void UpdateWolf(Entity *self);

int count;

void SpawnWolf(Entity *owner,int x,int y,int subtype,int affiliation)
{
	Entity *newent=NULL;
	newent=	NewEntity();
	if(newent == NULL){
		fprintf(stderr,"Unable to generate wolf entity; %s",SDL_GetError());
		return;
	}
	newent->owner=owner;
	newent->s.x=x;
	newent->s.y=y;
	newent->sprite=LoadSwappedSprite("images/92x134wolf.png",92,134);
	newent->origin.x = 10;
	newent->origin.y = 10;
	newent->Boundingbox.x=15;
	newent->Boundingbox.y=15;
	newent->Boundingbox.w=92;
	newent->Boundingbox.h=134;
	newent->Unit_Type=affiliation;
	newent->update = UpdateWolf;
	//newent->lifespan=900;
	newent->used=1;
	newent->v.x=0;
	newent->v.y=0;
	newent->trail[0].x = x;
	newent->trail[0].y = y;
	newent->m.x = (x + newent->origin.x) >> 6;
	newent->m.y = (y + newent->origin.y) >> 6;
	AddEntToRegion(newent,newent->m.x,newent->m.y);
	Wolf=newent;
}

void UpdateWolf(Entity *self)
{
  UpdateEntityPosition(self,0);
  if(UpdateEntityPosition(self,0)!=1)
  {
	  self->v.y+=5;
  }
  /*self->lifespan--;
  if(self->lifespan <= 0)
  {
    FreeEntity(self);
    return;  
  }*/
  if(ThePlayer!=NULL)
  {
	SDL_Rect bbox,bbox2;
	bbox2.x=ThePlayer->s.x;
	bbox2.y=ThePlayer->s.y;
	bbox2.h=ThePlayer->Boundingbox.w;
	bbox2.w=ThePlayer->Boundingbox.h;
	bbox.x=self->s.x;
	bbox.y=self->s.y;
	bbox.w=self->Boundingbox.w;
	bbox.h=self->Boundingbox.h;
	if(Collide(bbox,bbox2)==1){
		count=0;
		printf("YOU GOT THE WOLF TRANSITION TO NEXT LEVEL");
		//printf("%i",lvl);
		if(lvl==1)
		{
			FreeEntity(self);
			lvl++;	
			FreeEntity(ThePlayer);
			//ClearEntities();
			GenerateLevel("maps/level2.txt",320,54);
			DrawLevel2();
			SpawnAll(1);
		}else{
			printf("%i",lvl);
		}
	}
  }
}