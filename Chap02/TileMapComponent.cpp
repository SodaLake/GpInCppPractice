#include "TileMapComponent.h"
#include<fstream>
#include<iostream>
#include<string>
#include <sstream>
#include <vector>
#include"Actor.h"
#include"Math.h"
using namespace std;
TileMapComponent::TileMapComponent(Actor* owner, int drawOrder)
    :SpriteComponent(owner, drawOrder)
    , tileSize(32, 32)
{
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{
    if (mTexture)
    {


        for (int i = 0; i < data.size(); i++)
        {

            for (int j = 0; j < data.front().size(); j++)
            {
                SDL_Rect r;
                // Scale the width/height by owner's scale
                r.w = static_cast<int>(tileSize.x * mOwner->GetScale());
                r.h = static_cast<int>(tileSize.y * mOwner->GetScale());
                // �»���� ���������Ͽ� ��������.
                r.x = static_cast<int>(mOwner->GetPosition().x + j * tileSize.x);
                r.y = static_cast<int>(mOwner->GetPosition().y + i * tileSize.y);

                //Ÿ���� ����κ��� ������ ���ΰ�.

                if (data[i][j] == -1)
                    continue;
               
                int xCount = mTexWidth / tileSize.x;

                SDL_Rect sr;
                sr.w = static_cast<int>(tileSize.x);
                sr.h = static_cast<int>(tileSize.y);
                sr.x = (data[i][j] % xCount) * tileSize.x;
                sr.y = (data[i][j] / xCount) * tileSize.y;



                // Draw (have to convert angle from radians to degrees, and clockwise to counter)
                SDL_RenderCopyEx(renderer,
                    mTexture,
                    &sr,
                    &r,
                    -Math::ToDegrees(mOwner->GetRotation()),
                    nullptr,
                    SDL_FLIP_NONE);
            }
        }
        
    }
}

void TileMapComponent::LoadCSV(const char* path)
{
    std::ifstream file(path); // data.csv ������ �б� ���� ����
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) { // ������ �� ���� ����
            std::stringstream lineStream(line); // ���ڿ� ��Ʈ�� ����
            std::string cell;
            std::vector<int> row;

            while (std::getline(lineStream, cell, ',')) { // ��ǥ�� �����Ͽ� �� ���� ����
                row.push_back(stoi(cell)); // �� �����͸� ���Ϳ� ����
            }

            data.push_back(row); 

            
        }
        file.close();
    }
    else {
        std::cerr << "���� ���� error" << std::endl;
    }

}

