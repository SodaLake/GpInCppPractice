#pragma once
#include "SpriteComponent.h"
#include<vector>
#include"math.h "
using std::vector;


class TileMapComponent :
    public SpriteComponent
{
public:
    TileMapComponent(class Actor* owner, int drawOrder = 100);
    void Draw(SDL_Renderer* renderer);
    void LoadCSV(const char* path);
private:
    vector<vector<int>> data;
    Vector2 tileSize;



};

