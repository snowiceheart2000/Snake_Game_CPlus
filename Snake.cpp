#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>

using namespace std;

const string PathImages = "Resources/Images/";
const string PathFonts = "Resources/Fonts/Birdy Game.ttf";
const string PathMusics = "Resources/Musics/";
const string PathFiles = "Resources/Files/HighScore.txt";
unsigned int Score;

float W1 = 39.857142857142857142857142857142857142857142857142857142;
float H1 = 39.824561403508771929;
float W2 = 32;
float H2 = 32;

int Num;
enum Direction {UP, DOWN, LEFT, RIGHT};

struct Pos
{
    int x, y;
};

Pos Snake[532], Fruit[1];
Direction Dir;

int Map[27][48] = {
                      {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                      {10,10,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,10,10},
                      {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                      {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                      {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,12,12,12,12,12,12,12,12,12,12,12,12,12,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                      {10,10,10,10,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,10,10,10,10},
                      {10,12,12,12,13,13,13,14,15,15,15,15,15,16,17,13,13,13,13,13,13,13,13,13,18,13,13,13,13,13,13,14,15,15,15,15,15,15,16,13,13,13,13,13,12,12,12,10},
                      {12,13,13,13,19,13,13,20,21,21,21,21,21,21,17,19,19,13,13,13,13,13,13,13,19,13,13,13,13,13,13,20,21,21,21,21,21,21,21,13,19,19,13,13,13,13,13,12},
                      {22,13,13,13,13,13,13,20,21,21,23,21,21,21,17,19,19,13,13,13,13,13,13,13,13,13,13,13,13,13,13,20,21,21,21,23,21,21,21,13,19,13,13,13,19,13,13,13},
                      {24,13,13,13,13,13,13,20,21,21,21,21,21,21,17,19,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,20,21,21,21,21,21,21,21,13,19,19,13,13,19,19,19,13},
                      {22,13,13,13,13,13,13,25,26,26,26,26,26,27,17,17,17,17,17,17,13,13,13,13,17,17,17,17,17,17,17,25,26,26,26,26,26,26,27,13,13,19,13,19,13,13,13,13},
                      {22,24,22,24,22,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,19,13,13,13,13,13,13,13,13,13,17,17,17,17,17,17,17,17,17,13,13,24,22,24,22,24,22,22},
                      {28,28,28,28,22,22,22,28,28,28,28,28,28,28,28,28,28,28,28,28,28,13,13,13,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,22,24,22,28,28,28,28,28,28},
                      {28,28,28,28,28,28,28,28,28,29,30,30,30,30,30,30,30,28,28,28,28,28,13,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28},
                      {28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,13,28,28,28,28,28,28,29,30,30,30,30,30,30,30,28,28,28,28,28,28,28,28,28,28,28},
                      {28,28,28,28,13,13,13,28,28,28,28,28,28,28,28,28,28,28,28,28,28,31,13,13,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,13,13,13,28,28,28,28,28,28},
                      {13,13,13,13,13,13,17,17,17,17,17,17,17,17,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13},
                      {13,13,13,13,13,13,17,14,15,15,15,15,15,16,13,13,13,13,13,13,19,32,13,13,13,13,13,13,13,13,32,14,15,15,15,15,15,15,16,32,13,19,13,13,13,19,13,13},
                      {13,13,13,13,13,13,17,20,21,21,21,21,21,21,13,13,13,13,13,13,13,13,13,13,13,32,32,32,32,32,32,20,21,21,21,21,21,21,21,13,13,13,13,13,13,13,13,13},
                      {13,13,13,13,13,13,17,20,21,21,23,21,21,21,13,13,13,13,13,13,13,17,17,17,17,17,17,17,17,17,17,20,21,21,21,23,21,21,21,13,13,13,13,13,13,13,13,13},
                      {12,13,13,13,13,13,17,20,21,21,21,21,21,21,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,17,20,21,21,21,21,21,21,21,13,13,13,13,13,13,13,13,12},
                      {10,12,12,12,13,13,17,25,26,26,26,26,26,27,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,17,25,26,26,26,26,26,26,27,13,13,13,13,13,12,12,12,10},
                      {10,10,10,10,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,10,10,10,10},
                      {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,12,12,12,12,12,12,12,12,12,12,12,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                      {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                      {10,10,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,10,10},
                      {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10}
                  };

int wall[4]={12,17,22,24};

int Gate_x[10]={ 2,  2, 9, 10, 10, 29, 35, 35, 45, 45};
int Gate_y[10]={ 1, 25, 13, 8, 19, 14,  8, 19,  1, 25};

void CreateSnake(Pos Snake[])
{
    Snake[0].x=15;
    Snake[0].y=9;

    for (int i=1; i<Num; i++)
    {
        Snake[i].x=Snake[i-1].x - 1;
        Snake[i].y=Snake[i-1].y;
    }
}

void CreateFruit(Pos Snake[], Pos Fruit[])
{
    int tempX, tempY;
    while (true)
    {
        tempX = rand()%28;
        tempY = rand()%19;

        int dem=0;
        for (int i=0; i<Num; i++)
            if (tempX != Snake[i].x && tempY != Snake[i].y)
                dem++;

        if (dem==Num)
        {
            Fruit[0].x=tempX;
            Fruit[0].y=tempY;
            break;
        }
        else
            dem=0;
    }
}

void SnakeProcess(Pos Snake[], Pos Fruit[], Direction Dir, sf::Sound &sEat)
{
    for (int i=Num; i>0; --i)
    {
        Snake[i].x=Snake[i-1].x;
        Snake[i].y=Snake[i-1].y;
    }
    if (Dir==LEFT)
        Snake[0].x--;
    if (Dir==RIGHT)
        Snake[0].x++;
    if (Dir==UP)
        Snake[0].y--;
    if (Dir==DOWN)
        Snake[0].y++;

    if (Snake[0].x>27)
        Snake[0].x=0;
    if (Snake[0].x<0)
        Snake[0].x=27;
    if (Snake[0].y>18)
        Snake[0].y=0;
    if (Snake[0].y<0)
        Snake[0].y=18;

    if (Snake[0].x==Fruit[0].x && Snake[0].y==Fruit[0].y)
    {
        Num++;
        Score+=10;
        sEat.play();
        CreateFruit(Snake, Fruit);
    }
}

bool Died(Pos Snake[])
{
    for (int i=1; i<Num; i++)
    {
        if (Snake[0].x==Snake[i].x && Snake[0].y==Snake[i].y)
            return true;
    }
    return false;
}

void CreateSnake2(Pos Snake[])
{
    Snake[0].x=26;
    Snake[0].y=14;

    for (int i=1; i<Num; i++)
    {
        Snake[i].x=Snake[i-1].x - 1;
        Snake[i].y=Snake[i-1].y;
    }
}

void CreateFruit2(Pos Snake[], Pos Fruit[], int Map[27][48], int wall[])
{
    int tempX, tempY;
    while (true)
    {
        tempX = rand()%48;
        tempY = rand()%27;

        int dem=0;
        for (int i=0; i<Num; i++)
            if (tempX != Snake[i].x && tempY != Snake[i].y)
                dem++;

        if (dem==Num)
        {
            int dem2=0;
            for (int j=0; j<4; j++)
                if (Map[tempY][tempX]!=wall[j])
                    dem2++;

            if (dem2==4)
            {
                Fruit[0].x=tempX;
                Fruit[0].y=tempY;
                break;
            }
        }
    }
}

void SnakeProcess2(Pos Snake[], Pos Fruit[], Direction Dir, int Gate_x[], int Gate_y[], sf:: Sound &sEat)
{
    for (int i=Num; i>0; --i)
    {
        Snake[i].x=Snake[i-1].x;
        Snake[i].y=Snake[i-1].y;
    }
    if (Dir==LEFT)
        Snake[0].x--;
    if (Dir==RIGHT)
        Snake[0].x++;
    if (Dir==UP)
        Snake[0].y--;
    if (Dir==DOWN)
        Snake[0].y++;

    if (Snake[0].x>47)
        Snake[0].x=0;
    if (Snake[0].x<0)
        Snake[0].x=47;
    if (Snake[0].y>26)
        Snake[0].y=0;
    if (Snake[0].y<0)
        Snake[0].y=26;

    if (Snake[0].x==Fruit[0].x && Snake[0].y==Fruit[0].y)
    {
        Num++;
        Score+=10;
        sEat.play();
        CreateFruit2(Snake, Fruit, Map, wall);
    }

    for (int i=0; i<10; i++)
    {
        if (Snake[0].x==Gate_x[i] && Snake[0].y==Gate_y[i])
        {
            while (true)
            {
                int j=rand()%10;
                if (j!=i)
                {
                    Snake[0].x=Gate_x[j];
                    Snake[0].y=Gate_y[j];

                    break;
                }
            }
        }
    }
}

bool Died2(Pos Snake[], int Map[27][48], int wall[])
{
    for (int i=1; i<Num; i++)
    {
        if (Snake[0].x==Snake[i].x && Snake[0].y==Snake[i].y)
            return true;
    }

    for (int i=0; i<4; i++)
    {
        if (Map[Snake[0].y][Snake[0].x] == wall[i])
            return true;
    }

    return false;
}

bool NearFruit(Pos Snake[], Pos Fruit[])
{
    int di[24]={-2, -2, -2, -2, -2, -1, -1, -1, -1, -1,  0,  0, 0, 0,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2};
    int dj[24]={-2, -1,  0,  1,  2, -2, -1,  0,  1,  2, -2, -1, 1, 2, -2, -1,  0,  1,  2, -2, -1,  0,  1,  2};

    for (int k=0; k<24; k++)
    {
        if (Snake[0].x==Fruit[0].x+di[k] && Snake[0].y==Fruit[0].y+dj[k])
            return true;
    }
    return false;
}

void SetHighScore()
{
    ifstream Read;
    Read.open(PathFiles, ios_base::in);

    unsigned int Score[5];

    for (int i = 0; i < 5; i++)
        Read >> Score[i];

    Read.close();

    if (Score[4] < ::Score)
    {
        int count=0;
        for (int i = 0; i < 4; i++)
        {
            if (Score[i] != ::Score)
                count++;
            if (count==4)
                Score[4] = ::Score;
        }
        for (int i = 0; i < 5; i++)
            for (int j = i; j < 5; j++)
                if (Score[i] < Score[j])
                    swap(Score[i], Score[j]);
        ofstream Write;
        Write.open(PathFiles, ios_base::out);
        Write.clear();
        for (int i = 0; i < 5; i++)
        {
            Write << Score[i];
            Write << "\n";
        }
        Write.close();
    }
}

void PlayGame(sf::RenderWindow &window)
{
    window.create(sf::VideoMode(1116, 1000), "Snake - Normal", sf::Style::Close);
    window.setFramerateLimit(60);

    int frameEye=0;
    int frameTongue=0;
    int frameMouth=0;

    sf::SoundBuffer Eat;
    Eat.loadFromFile(PathMusics + "eat.wav");
    sf::Sound sEat(Eat);

    sf::Texture BackGround, GameOver;
    BackGround.loadFromFile(PathImages + "map.jpg");
    GameOver.loadFromFile(PathImages + "game_over.png");

    sf::Texture Head, LeftEye, RightEye, Tongue, Mouth, Body, Tail, tFruit;
    Head.loadFromFile(PathImages + "right.png");
    Head.setSmooth(true);
    LeftEye.loadFromFile(PathImages + "blink.png");
    RightEye.loadFromFile(PathImages + "blink.png");
    Tongue.loadFromFile(PathImages + "tongue.png");
    Mouth.loadFromFile(PathImages + "eat.png");
    Body.loadFromFile(PathImages + "blue.png");
    tFruit.loadFromFile(PathImages + "apple.png");

    sf::Font font;
    font.loadFromFile(PathFonts);

    sf::Sprite Back(BackGround);
    Back.setTexture(BackGround);
    Back.setPosition(0,121.6666666666666666666666666666666666666666666666666666666666);
    Back.setScale(0.6666666666666666666666666666666666666,0.66666666666666666666666666666666666666666666666666);

    sf::Text tScore;
    tScore.setFont(font);
    tScore.setPosition(50,50);
    tScore.setFillColor(sf::Color::White);
    tScore.setOutlineColor(sf::Color::Black);
    tScore.setOutlineThickness(4);
    tScore.setCharacterSize(40);

    Num=4;
    Dir=RIGHT;

    CreateSnake(Snake);
    CreateFruit(Snake, Fruit);

    sf::Sprite sHead(Head);
    sHead.setTexture(Head);
    sHead.setPosition(Snake[0].x*W1+W1/2, Snake[0].y*H1 + H1/2 + 121.6666666666666666666666666666666666666666666666666666666666);
    sHead.setScale(0.159428571428571428571428571428571, 0.15929824561403508771929824561403508771);
    sHead.setOrigin(125, 125);

    sf::Sprite sLeftEye(LeftEye);
    sLeftEye.setTexture(LeftEye);
    sLeftEye.setScale(1.1,1.1);
    sLeftEye.setOrigin(14,14);

    sf::Sprite sRightEye(RightEye);
    sRightEye.setTexture(RightEye);
    sRightEye.setScale(1.1,1.1);
    sRightEye.setOrigin(14,14);

    sf::Sprite sTongue(Tongue);
    sTongue.setTexture(Tongue);
    sTongue.setScale(4, 2);

    sf::Sprite sMouth(Mouth);
    sMouth.setTexture(Mouth);
    sMouth.setScale(1.3, 1.3);

    sf::Sprite sBody(Body);
    sBody.setTexture(Body);
    sBody.setScale(0.079714285714285714285714285714285, 0.07964912280701754385964912280701754385);

    sf::Sprite sFruit(tFruit);
    sFruit.setTexture(tFruit);
    sFruit.setScale(0.3113839285714285714285714285714285714, 0.311129385964912280701754385964912280701754);

    sf::Sprite sGameOver(GameOver);
    sGameOver.setTexture(GameOver);
    sGameOver.setScale(1.554317548746518, 1.554317548746518);

    sf::Clock clock, EyeAnimationTime, TongueAnimationTime;
    float Timer=0, Delay=0.2;

    while (window.isOpen())
    {
        float Time = clock.getElapsedTime().asSeconds();
        clock.restart();
        Timer+=Time;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                window.close();
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {

            if (Dir==RIGHT)
                Dir=RIGHT;
            else
            {
                Dir=LEFT;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (Dir==LEFT)
                Dir=LEFT;
            else
            {
                Dir=RIGHT;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (Dir==DOWN)
                Dir=DOWN;
            else
            {
                Dir=UP;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (Dir==UP)
                Dir=UP;
            else
            {
                Dir=DOWN;
            }
        }

        if (!Died(Snake))
        {
            if (Timer>Delay)
            {
                Timer=0;
                SnakeProcess(Snake, Fruit, Dir, sEat);
                tScore.setString("Score: " + to_string(Score));
            }

            window.clear(sf::Color(207,255,254));
            window.draw(Back);

            window.draw(tScore);

            if (Dir==LEFT)
            {
                sTongue.setRotation(180);
                sHead.setRotation(180);
                sLeftEye.setRotation(180);
                sRightEye.setRotation(180);
                sMouth.setRotation(180);
                sLeftEye.setPosition(sHead.getPosition().x+13,sHead.getPosition().y+13);
                sRightEye.setPosition(sHead.getPosition().x+13,sHead.getPosition().y-12);
                sTongue.setPosition(sHead.getPosition().x-W1/2+38,sHead.getPosition().y-H1/2+45);
                sMouth.setPosition(sHead.getPosition().x-W1/2+30,sHead.getPosition().y-H1/2+55);
            }

            if (Dir==RIGHT)
            {
                sTongue.setRotation(0);
                sHead.setRotation(0);
                sLeftEye.setRotation(0);
                sRightEye.setRotation(0);
                sMouth.setRotation(0);
                sLeftEye.setPosition(sHead.getPosition().x-13,sHead.getPosition().y-12);
                sRightEye.setPosition(sHead.getPosition().x-13,sHead.getPosition().y+13);
                sTongue.setPosition(sHead.getPosition().x-W1/2+5,sHead.getPosition().y-H1/2-7);
                sMouth.setPosition(sHead.getPosition().x-W1/2+7,sHead.getPosition().y-H1/2-15);
            }

            if (Dir==UP)
            {
                sHead.setRotation(-90);
                sTongue.setRotation(-90);
                sLeftEye.setRotation(-90);
                sRightEye.setRotation(-90);
                sMouth.setRotation(-90);
                sLeftEye.setPosition(sHead.getPosition().x-13,sHead.getPosition().y+13);
                sRightEye.setPosition(sHead.getPosition().x+11,sHead.getPosition().y+13);
                sTongue.setPosition(sHead.getPosition().x-W1/2-5,sHead.getPosition().y-H1/2+35);
                sMouth.setPosition(sHead.getPosition().x-W1/2-16,sHead.getPosition().y-H1/2+30);
            }
            if (Dir==DOWN)
            {
                sTongue.setRotation(90);
                sHead.setRotation(90);
                sLeftEye.setRotation(90);
                sRightEye.setRotation(90);
                sMouth.setRotation(90);
                sLeftEye.setPosition(sHead.getPosition().x+11,sHead.getPosition().y-15);
                sRightEye.setPosition(sHead.getPosition().x-13,sHead.getPosition().y-15);
                sTongue.setPosition(sHead.getPosition().x-W1/2+46,sHead.getPosition().y-H1/2+4);
                sMouth.setPosition(sHead.getPosition().x-W1/2+55,sHead.getPosition().y-H1/2+7);
            }

            for (int i=1; i<Num; i++)
            {
                sBody.setPosition(Snake[i].x*W1, Snake[i].y*H1 + 121.6666666666666666666666666666666666666666666666666666666666);
                window.draw(sBody);
            }

            if (TongueAnimationTime.getElapsedTime().asSeconds() > 4)
            {
                frameTongue = (++frameTongue) % 21;
                if (frameTongue == 20)
                {
                    TongueAnimationTime.restart();
                    frameTongue = 0;
                }
            }

            sTongue.setTextureRect(sf::IntRect(0, frameTongue*24, 21, 24));
            window.draw(sTongue);

            sHead.setPosition(Snake[0].x*W1+W1/2, Snake[0].y*H1 + H1/2 + 121.6666666666666666666666666666666666666666666666666666666666);
            window.draw(sHead);

            if (NearFruit(Snake, Fruit))
            {
                if (frameMouth<7)
                {
                    frameMouth = ++frameMouth;
                    sMouth.setTextureRect(sf::IntRect(0, frameMouth*54, 35, 54));
                    window.draw(sMouth);
                }
                else
                {
                    sMouth.setTextureRect(sf::IntRect(0, frameMouth*54, 35, 54));
                    window.draw(sMouth);
                }
            }
            else
            {
                if (frameMouth>0)
                {
                    frameMouth = --frameMouth;
                    sMouth.setTextureRect(sf::IntRect(0, frameMouth*54, 35, 54));
                    window.draw(sMouth);
                }
            }

            if (EyeAnimationTime.getElapsedTime().asSeconds() > 2)
            {
                frameEye = (++frameEye) % 9;
                if (frameEye == 8)
                {
                    EyeAnimationTime.restart();
                    frameEye = 0;
                }
            }

            sLeftEye.setTextureRect(sf::IntRect(0, frameEye*28, 28, 28));
            window.draw(sLeftEye);
            sRightEye.setTextureRect(sf::IntRect(0, frameEye*28, 28, 28));
            window.draw(sRightEye);

            sFruit.setPosition(Fruit[0].x*W1, Fruit[0].y*H1 + 121.6666666666666666666666666666666666666666666666666666666666);
            window.draw(sFruit);
        }
        else
        {
            SetHighScore();
            Score=0;
            window.clear(sf::Color::Black);
            sGameOver.setPosition(0, 127.7409470752089);
            window.draw(sGameOver);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x >= 0 && sf::Mouse::getPosition(window).x <= 1116 && sf::Mouse::getPosition(window).y >= 0 && sf::Mouse::getPosition(window).y <= 1000)
            {
                window.create(sf::VideoMode(1536, 1024), "Snake - Choose Map", sf::Style::Close);
                break;
            }
        }
        window.display();
    }
}

void PlayGame2(sf::RenderWindow &window)
{
    window.create(sf::VideoMode(1536, 1080), "Snake - Advanced", sf::Style::Close);
    window.setFramerateLimit(60);

    int frameEye=0;
    int frameTongue=0;
    int frameMouth=0;

    sf::SoundBuffer Eat;
    Eat.loadFromFile(PathMusics + "eat.wav");
    sf::Sound sEat(Eat);

    sf::Texture BackGround, GameOver;
    BackGround.loadFromFile(PathImages + "map2.png");
    GameOver.loadFromFile(PathImages + "game_over.png");

    sf::Texture Head, LeftEye, RightEye, Tongue, Mouth, Body, Tail, tFruit;
    Head.loadFromFile(PathImages + "right.png");
    Head.setSmooth(true);
    LeftEye.loadFromFile(PathImages + "blink.png");
    RightEye.loadFromFile(PathImages + "blink.png");
    Tongue.loadFromFile(PathImages + "tongue.png");
    Mouth.loadFromFile(PathImages + "eat.png");
    Body.loadFromFile(PathImages + "blue.png");
    tFruit.loadFromFile(PathImages + "apple.png");

    sf::Font font;
    font.loadFromFile(PathFonts);

    sf::Sprite Back(BackGround);
    Back.setTexture(BackGround);
    Back.setPosition(0,108);

    sf::Text tScore;
    tScore.setFont(font);
    tScore.setPosition(50,50);
    tScore.setFillColor(sf::Color::White);
    tScore.setOutlineColor(sf::Color::Black);
    tScore.setOutlineThickness(4);
    tScore.setCharacterSize(40);

    Num=4;
    Dir=RIGHT;

    CreateSnake2(Snake);
    CreateFruit2(Snake, Fruit, Map, wall);

    sf::Sprite sHead(Head);
    sHead.setTexture(Head);
    sHead.setPosition(Snake[0].x*W2+W2/2, Snake[0].y*H2 + H2/2 + 108);
    sHead.setScale(0.128, 0.128);
    sHead.setOrigin(125, 125);

    sf::Sprite sLeftEye(LeftEye);
    sLeftEye.setTexture(LeftEye);
    sLeftEye.setScale(1.1,1.1);
    sLeftEye.setOrigin(14,14);

    sf::Sprite sRightEye(RightEye);
    sRightEye.setTexture(RightEye);
    sRightEye.setScale(1.1,1.1);
    sRightEye.setOrigin(14,14);

    sf::Sprite sTongue(Tongue);
    sTongue.setTexture(Tongue);
    sTongue.setScale(4, 2);

    sf::Sprite sMouth(Mouth);
    sMouth.setTexture(Mouth);
    sMouth.setScale(1.1, 1.1);

    sf::Sprite sBody(Body);
    sBody.setTexture(Body);
    sBody.setScale(0.064, 0.064);

    sf::Sprite sFruit(tFruit);
    sFruit.setTexture(tFruit);
    sFruit.setScale(0.25, 0.25);

    sf::Sprite sGameOver(GameOver);
    sGameOver.setTexture(GameOver);
    sGameOver.setScale(2.13927566, 2.139275766);

    sf::Clock clock, EyeAnimationTime, TongueAnimationTime;
    float Timer=0, Delay=0.2;

    while (window.isOpen())
    {
        float Time = clock.getElapsedTime().asSeconds();
        clock.restart();
        Timer+=Time;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                window.close();
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {

            if (Dir==RIGHT)
                Dir=RIGHT;
            else
            {
                Dir=LEFT;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (Dir==LEFT)
                Dir=LEFT;
            else
            {
                Dir=RIGHT;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (Dir==DOWN)
                Dir=DOWN;
            else
            {
                Dir=UP;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (Dir==UP)
                Dir=UP;
            else
            {
                Dir=DOWN;
            }
        }

        if (!Died2(Snake, Map, wall))
        {
            if (Timer>Delay)
            {
                Timer=0;
                SnakeProcess2(Snake, Fruit, Dir, Gate_x, Gate_y, sEat);
                cout << Snake[0].y << " " << Snake[0].x << " " << Map[Snake[0].y][Snake[0].x] << endl;
                tScore.setString("Score: " + to_string(Score));
            }

            window.clear(sf::Color(207,255,254));
            window.draw(Back);

            window.draw(tScore);

            if (Dir==LEFT)
            {
                sTongue.setRotation(180);
                sHead.setRotation(180);
                sLeftEye.setRotation(180);
                sRightEye.setRotation(180);
                sMouth.setRotation(180);
                sLeftEye.setPosition(sHead.getPosition().x+13,sHead.getPosition().y+13);
                sRightEye.setPosition(sHead.getPosition().x+13,sHead.getPosition().y-12);
                sTongue.setPosition(sHead.getPosition().x-W2/2+38,sHead.getPosition().y-H2/2+42);
                sMouth.setPosition(sHead.getPosition().x-W2/2+25,sHead.getPosition().y-H2/2+47);
            }

            if (Dir==RIGHT)
            {
                sTongue.setRotation(0);
                sHead.setRotation(0);
                sLeftEye.setRotation(0);
                sRightEye.setRotation(0);
                sMouth.setRotation(0);
                sLeftEye.setPosition(sHead.getPosition().x-13,sHead.getPosition().y-12);
                sRightEye.setPosition(sHead.getPosition().x-13,sHead.getPosition().y+13);
                sTongue.setPosition(sHead.getPosition().x-W2/2+5,sHead.getPosition().y-H2/2-10);
                sMouth.setPosition(sHead.getPosition().x-W2/2+7,sHead.getPosition().y-H2/2-13);
            }

            if (Dir==UP)
            {
                sHead.setRotation(-90);
                sTongue.setRotation(-90);
                sLeftEye.setRotation(-90);
                sRightEye.setRotation(-90);
                sMouth.setRotation(-90);
                sLeftEye.setPosition(sHead.getPosition().x-13,sHead.getPosition().y+13);
                sRightEye.setPosition(sHead.getPosition().x+11,sHead.getPosition().y+13);
                sTongue.setPosition(sHead.getPosition().x-W2/2-8,sHead.getPosition().y-H2/2+35);
                sMouth.setPosition(sHead.getPosition().x-W2/2-15,sHead.getPosition().y-H2/2+26);
            }
            if (Dir==DOWN)
            {
                sTongue.setRotation(90);
                sHead.setRotation(90);
                sLeftEye.setRotation(90);
                sRightEye.setRotation(90);
                sMouth.setRotation(90);
                sLeftEye.setPosition(sHead.getPosition().x+11,sHead.getPosition().y-15);
                sRightEye.setPosition(sHead.getPosition().x-13,sHead.getPosition().y-15);
                sTongue.setPosition(sHead.getPosition().x-W2/2+43,sHead.getPosition().y-H2/2+4);
                sMouth.setPosition(sHead.getPosition().x-W2/2+46,sHead.getPosition().y-H2/2+4);
            }

            for (int i=1; i<Num; i++)
            {
                sBody.setPosition(Snake[i].x*W2, Snake[i].y*H2 + 108);
                window.draw(sBody);
            }

            if (TongueAnimationTime.getElapsedTime().asSeconds() > 4)
            {
                frameTongue = (++frameTongue) % 21;
                if (frameTongue == 20)
                {
                    TongueAnimationTime.restart();
                    frameTongue = 0;
                }
            }

            sTongue.setTextureRect(sf::IntRect(0, frameTongue*24, 21, 24));
            window.draw(sTongue);

            sHead.setPosition(Snake[0].x*W2+W2/2, Snake[0].y*H2 + H2/2 + 108);
            window.draw(sHead);

            if (NearFruit(Snake, Fruit))
            {
                if (frameMouth<7)
                {
                    frameMouth = ++frameMouth;
                    sMouth.setTextureRect(sf::IntRect(0, frameMouth*54, 35, 54));
                    window.draw(sMouth);
                }
                else
                {
                    sMouth.setTextureRect(sf::IntRect(0, frameMouth*54, 35, 54));
                    window.draw(sMouth);
                }
            }
            else
            {
                if (frameMouth>0)
                {
                    frameMouth = --frameMouth;
                    sMouth.setTextureRect(sf::IntRect(0, frameMouth*54, 35, 54));
                    window.draw(sMouth);
                }
            }

            if (EyeAnimationTime.getElapsedTime().asSeconds() > 2)
            {
                frameEye = (++frameEye) % 9;
                if (frameEye == 8)
                {
                    EyeAnimationTime.restart();
                    frameEye = 0;
                }
            }

            sLeftEye.setTextureRect(sf::IntRect(0, frameEye*28, 28, 28));
            window.draw(sLeftEye);
            sRightEye.setTextureRect(sf::IntRect(0, frameEye*28, 28, 28));
            window.draw(sRightEye);

            sFruit.setPosition(Fruit[0].x*W2, Fruit[0].y*H2 + 108);
            window.draw(sFruit);
        }
        else
        {
            SetHighScore();
            Score=0;
            window.clear(sf::Color::Black);
            sGameOver.setPosition(27.643454039, 0);
            window.draw(sGameOver);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x >= 0 && sf::Mouse::getPosition(window).x <= 1116 && sf::Mouse::getPosition(window).y >= 0 && sf::Mouse::getPosition(window).y <= 1000)
            {
                window.create(sf::VideoMode(1536, 1024), "Snake - Choose Map", sf::Style::Close);
                break;
            }
        }
        window.display();
    }
}

void chooseMap(sf::RenderWindow &window)
{
    window.create(sf::VideoMode(1536, 1024), "Snake - Choose Map", sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Texture BackGround, Map1, Map2;
    BackGround.loadFromFile(PathImages + "waterfall.jpg");
    Map1.loadFromFile(PathImages + "map.jpg");
    Map2.loadFromFile(PathImages + "map2.png");

    sf::Sprite Back(BackGround);
    Back.setTexture(BackGround);
    Back.setScale(0.75, 0.75);

    sf::Sprite sMap1(Map1);
    sMap1.setTexture(Map1);
    sMap1.setScale(0.375, 0.375);
    sMap1.setPosition(100, 230);

    sf::Sprite sMap2(Map2);
    sMap2.setTexture(Map2);
    sMap2.setScale(0.486914064, 0.486914064);
    sMap2.setPosition(770, 230);

    sf::Font font;
    font.loadFromFile(PathFonts);

    sf::Text Normal, Advanced;
    Normal.setString("Normal");
    Advanced.setString("Advanced");

    Normal.setFont(font);
    Advanced.setFont(font);

    Normal.setCharacterSize(50);
    Advanced.setCharacterSize(50);

    Normal.setPosition(300, 720);
    Advanced.setPosition(1050, 720);

    Normal.setFillColor(sf::Color::Blue);
    Advanced.setFillColor(sf::Color::Blue);

    Normal.setOutlineThickness(10);
    Advanced.setOutlineThickness(10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(207,255,254));
        window.draw(Back);
        window.draw(sMap1);
        window.draw(sMap2);
        window.draw(Normal);
        window.draw(Advanced);

        if (sf::Mouse::getPosition(window).x >= 250 && sf::Mouse::getPosition(window).x <= 500 && sf::Mouse::getPosition(window).y >= 680 && sf::Mouse::getPosition(window).y <= 800)
        {
            Normal.setOutlineColor(sf::Color::White);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                PlayGame(window);
            }
        }
        else
            Normal.setOutlineColor(sf::Color(254,248,134));

        if (sf::Mouse::getPosition(window).x >= 1000 && sf::Mouse::getPosition(window).x <= 1300 && sf::Mouse::getPosition(window).y >= 680 && sf::Mouse::getPosition(window).y <= 800)
        {
            Advanced.setOutlineColor(sf::Color::White);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                PlayGame2(window);
        }
        else
            Advanced.setOutlineColor(sf::Color(254,248,134));

        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.create(sf::VideoMode(1197, 1000), "Snake", sf::Style::Close);
            break;
        }
    }
}

void HighScore(sf::RenderWindow &window)
{
    ifstream Read;
    Read.open(PathFiles, ios_base::in);

    unsigned int * Score = new unsigned int[5];
    string SCORE[5];
    for (int i = 0; i < 5; i++)
    {
        Read >> *(Score + i);
        SCORE[i] = to_string(*(Score + i));
    }
    delete Score;
    Read.close();

    sf::Font font;
    font.loadFromFile(PathFonts);

    sf::Text HIGHSCORE;
    HIGHSCORE.setString("High Score");
    HIGHSCORE.setPosition(400, 100);
    HIGHSCORE.setFont(font);
    HIGHSCORE.setOutlineColor(sf::Color::Black);
    HIGHSCORE.setOutlineThickness(10);
    HIGHSCORE.setCharacterSize(100);

    sf::Text Point;
    Point.setFont(font);
    Point.setOutlineColor(sf::Color::Black);
    Point.setOutlineThickness(5);
    Point.setCharacterSize(50);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(207,255,254));
        window.draw(HIGHSCORE);
        for (int i = 0; i < 5; i++)
        {
            Point.setString(SCORE[i]);
            Point.setPosition(600, i * 100 + 300);
            window.draw(Point);
        }
        window.display();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x >= 0 && sf::Mouse::getPosition(window).x <= 1197 && sf::Mouse::getPosition(window).y >= 0 && sf::Mouse::getPosition(window).y <= 1000)
            break;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            break;
    }
}

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1197, 1000), "Snake", sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Music BG;
    BG.openFromFile(PathMusics + "BackGround.wav");
    BG.play();
    BG.setLoop(true);
    BG.setVolume(50);

    sf::Texture BackGround;
    BackGround.loadFromFile(PathImages + "snake.jpg");

    sf::Sprite Back(BackGround);
    Back.setTexture(BackGround);
    Back.setPosition(0,197.5);

    sf::Font font;
    font.loadFromFile(PathFonts);

    sf::Text Play, High, Quit;
    Play.setString("Play");
    High.setString("High Score");
    Quit.setString("Quit");

    Play.setFont(font);
    High.setFont(font);
    Quit.setFont(font);

    Play.setCharacterSize(100);
    High.setCharacterSize(50);
    Quit.setCharacterSize(50);

    Play.setPosition(520, 650);
    High.setPosition(90, 720);
    Quit.setPosition(1000, 720);

    Play.setFillColor(sf::Color::Blue);
    High.setFillColor(sf::Color::Blue);
    Quit.setFillColor(sf::Color::Blue);

    Play.setOutlineThickness(25);
    High.setOutlineThickness(10);
    Quit.setOutlineThickness(10);

    //Game Loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(207,255,254));
        window.draw(Back);
        window.draw(Play);
        window.draw(High);
        window.draw(Quit);

        if (sf::Mouse::getPosition(window).x >= 500 && sf::Mouse::getPosition(window).x <= 735 && sf::Mouse::getPosition(window).y >= 650 && sf::Mouse::getPosition(window).y <= 799)
        {
            Play.setOutlineColor(sf::Color::White);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                chooseMap(window);
            }
        }
        else
            Play.setOutlineColor(sf::Color(254,248,134));

        if (sf::Mouse::getPosition(window).x >= 80 && sf::Mouse::getPosition(window).x <= 350 && sf::Mouse::getPosition(window).y >= 720 && sf::Mouse::getPosition(window).y <= 795)
        {
            High.setOutlineColor(sf::Color::White);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                HighScore(window);
        }
        else
            High.setOutlineColor(sf::Color(254,248,134));

        if (sf::Mouse::getPosition(window).x >= 980 && sf::Mouse::getPosition(window).x <= 1100 && sf::Mouse::getPosition(window).y >= 720 && sf::Mouse::getPosition(window).y <= 795)
        {
            Quit.setOutlineColor(sf::Color::White);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                break;
        }
        else
            Quit.setOutlineColor(sf::Color(254,248,134));

        window.display();
    }
    return EXIT_SUCCESS;
}


