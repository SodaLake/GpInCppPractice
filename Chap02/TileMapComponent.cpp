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
                // 좌상단을 기준으로하여 렌더링함.
                r.x = static_cast<int>(mOwner->GetPosition().x + j * tileSize.x);
                r.y = static_cast<int>(mOwner->GetPosition().y + i * tileSize.y);

                //타일의 어느부분을 가져올 것인가.

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
    std::ifstream file(path); // data.csv 파일을 읽기 모드로 열기
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) { // 파일의 각 줄을 읽음
            std::stringstream lineStream(line); // 문자열 스트림 생성
            std::string cell;
            std::vector<int> row;

            while (std::getline(lineStream, cell, ',')) { // 쉼표로 구분하여 각 셀을 읽음
                row.push_back(stoi(cell)); // 셀 데이터를 벡터에 저장
            }

            data.push_back(row); 

            
        }
        file.close();
    }
    else {
        std::cerr << "파일 열기 error" << std::endl;
    }

}

