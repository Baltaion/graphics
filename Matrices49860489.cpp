// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

// define the screen resolution and keyboard macros
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

#define ENEMY_NUM 7 
#define ENEMY_NUM2 8 

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface



						// sprite declarations
LPDIRECT3DTEXTURE9 sprite;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_hero;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_bullet;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_bg;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_hp;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy2;    // the pointer to the sprite

									 // function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);		// closes Direct3D and releases memory

void init_game(void);
void do_game_logic(void);
bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);


// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

using namespace std;


enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };


//기본 클래스 
class entity {

public:
	float x_pos;
	float y_pos;
	int status;
	int Hp;
	
	int color;
	int cooldown;
};


bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1)
{

	if ((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) < (size0 + size1) * (size0 + size1))
		return true;
	else
		return false;

}



//주인공 클래스 
class Hero :public entity {

public:
	bool deadcheck;
	Hero()
	{
		deadcheck = false;
		Hp = 7;
	}
	void HP_down();
	void move(int i);
	void init(float x, float y);
	bool check_collision(float x, float y);

};

void Hero::HP_down() {
	Hp--;
}

bool Hero::check_collision(float x, float y)
{
	if (Hp >= 1)
	{


		//충돌 처리 시 
		if (sphere_collision_check(x_pos, y_pos, 16, x, y, 16) == true)
		{
			HP_down();
			return true;

		}
		else {

			return false;
		}
	}
}

void Hero::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}


void Hero::move(int i)
{
	if (Hp >= 1)
	{

		switch (i)
		{
		case MOVE_UP:
			y_pos -= 7;
			break;

		case MOVE_DOWN:
			y_pos += 7;
			break;


		case MOVE_LEFT:
			x_pos -= 7;
			break;


		case MOVE_RIGHT:
			x_pos += 7;
			break;

		}
		
	}
}




// 적 클래스 
class Enemy :public entity {

public:
	void fire();
	void init(float x, float y);
	void move();

};

void Enemy::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}


void Enemy::move()
{
	y_pos += 5;

}

// 적 클래스 2
class Enemy2 :public entity {

public:
	void fire();
	void init(float x, float y);
	void move();

};

void Enemy2::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}


void Enemy2::move()
{
	y_pos += 6;
}

// 적 클래스 3
class Enemy3 :public entity {

public:
	void fire();
	void init(float x, float y);
	void move();

};

void Enemy3::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}


void Enemy3::move()
{
	y_pos -= 3;
}
// 적 클래스 4
class Enemy4 :public entity {

public:
	void fire();
	void init(float x, float y);
	void move();

};

void Enemy4::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}


void Enemy4::move()
{
	x_pos -= 6;
}


// 위로나가는 총알 클래스 
class Bullet :public entity {

public:
	bool bShow;
	Bullet()
	{
		cooldown = 50;
		color = 0;
	}
	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);
	void colorchange();

};




bool Bullet::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}




void Bullet::init(float x, float y)
{
	x_pos = x;
	y_pos = y;

}



bool Bullet::show()
{
	return bShow;

}


void Bullet::active()
{
	bShow = true;

}



void Bullet::move()
{
	y_pos -= 8;
}

void Bullet::hide()
{
	bShow = false;

}

// 총알 색깔 변화 클래스 
void Bullet::colorchange()
{
	cooldown = 65;
		
		if (color <= 3)
		{
			color++;
		}
		if (color >= 4)
		{
			color = 0;
		}
	
	return;
}

// 아래로 나가는 총알
class Bullet2 :public entity {

public:
	bool bShow;
	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);
	

};




bool Bullet2::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}




void Bullet2::init(float x, float y)
{
	x_pos = x;
	y_pos = y;

}



bool Bullet2::show()
{
	return bShow;

}


void Bullet2::active()
{
	bShow = true;

}



void Bullet2::move()
{
	y_pos += 8;
}

void Bullet2::hide()
{
	bShow = false;

}

//왼쪽으로 나가는 총알
class Bullet3 :public entity {

public:
	bool bShow;
	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);


};




bool Bullet3::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}




void Bullet3::init(float x, float y)
{
	x_pos = x;
	y_pos = y;

}



bool Bullet3::show()
{
	return bShow;

}


void Bullet3::active()
{
	bShow = true;

}



void Bullet3::move()
{
	x_pos -= 8;
}

void Bullet3::hide()
{
	bShow = false;

}


//오른쪽으로 나가는 총알
class Bullet4 :public entity {

public:
	bool bShow;
	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);


};

bool Bullet4::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}




void Bullet4::init(float x, float y)
{
	x_pos = x;
	y_pos = y;

}



bool Bullet4::show()
{
	return bShow;

}


void Bullet4::active()
{
	bShow = true;

}



void Bullet4::move()
{
	x_pos += 8;
}

void Bullet4::hide()
{
	bShow = false;

}







//객체 생성 
Hero hero;
Enemy enemy[ENEMY_NUM];
Enemy2 enemy2[ENEMY_NUM2];
Enemy3 enemy3[ENEMY_NUM2];
Enemy4 enemy4[ENEMY_NUM];
Bullet bullet;
Bullet2 bullet2;
Bullet3 bullet3;
Bullet4 bullet4;


// the entry point for any Windows program
// 그렇다네요
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL, L"WindowClass", L"Our Direct3D Program",
		WS_EX_TOPMOST | WS_POPUP, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	initD3D(hWnd);


	//게임 오브젝트 초기화 
	init_game();

	// enter the main loop:

	MSG msg;

	while (TRUE)
	{
		DWORD starting_point = GetTickCount();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		do_game_logic();

		render_frame();

		// check the 'escape' key
		if (KEY_DOWN(VK_ESCAPE))
			PostMessage(hWnd, WM_DESTROY, 0, 0);




		while ((GetTickCount() - starting_point) < 25);
	}

	// clean up DirectX and COM
	cleanD3D();

	return msg.wParam;
}


// this is the main message handler for the program
// 옵션
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


// this function initializes and prepares Direct3D for use
// 스프라이트 모음
void initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;


	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	D3DXCreateSprite(d3ddev, &d3dspt);    // create the Direct3D Sprite object

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Panel1.PNG",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"spaceship.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 255, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hero);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"60004.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 255, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"missile.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 255, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_bullet);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"bg.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_bg);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"hp.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 255, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hp);    // load to sprite
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Q.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 255, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy2);    // load to sprite
	return;
}




void init_game(void)
{
	//객체 초기화 
	hero.init(265, 200);

	//적들 초기화 
	for (int i = 0; i<ENEMY_NUM; i++)
	{

		enemy[i].init((float)(rand() % 550), rand() % 200 - 300);
	}
	for (int i = 0; i<ENEMY_NUM2; i++)
	{

		enemy2[i].init((float)(rand() % 550 ), rand() % 500 - 550);
	}
	for (int i = 0; i<ENEMY_NUM2; i++)
	{

		enemy3[i].init((float)(rand() % 550), rand() % 100 + 500);
	}
	for (int i = 0; i<ENEMY_NUM; i++)
	{

		enemy4[i].init((float)(rand() % 150 + 500), rand() % 500);
	}
	//총알 초기화 
	bullet.init(hero.x_pos, hero.y_pos);
	bullet2.init(hero.x_pos, hero.y_pos);
	bullet3.init(hero.x_pos, hero.y_pos);
	bullet4.init(hero.x_pos, hero.y_pos);
}

//게임로직
//여기서 판정건들입니다
void do_game_logic(void)
{



	if (hero.Hp >= 1)
	{
		//주인공 처리 
		if (KEY_DOWN(VK_UP))
			hero.move(MOVE_UP);

		if (KEY_DOWN(VK_DOWN))
			hero.move(MOVE_DOWN);

		if (KEY_DOWN(VK_LEFT))
			hero.move(MOVE_LEFT);

		if (KEY_DOWN(VK_RIGHT))
			hero.move(MOVE_RIGHT);
	}
	//주인공 충돌 처리
	if (bullet.color != 0)
	{
		for (int i = 0; i<ENEMY_NUM; i++)
		{
			if (hero.check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
			{
				enemy[i].init((float)(rand() % 550), rand() % 200 - 300);

			}
		}
	}
	if (bullet.color != 1)
	{
		for (int i = 0; i<ENEMY_NUM2; i++)
		{
			if (hero.check_collision(enemy2[i].y_pos, enemy2[i].x_pos) == true)
			{
				enemy2[i].init((float)(rand() % 550), rand() % 500 - 550);

			}
		}
	}
	if (bullet.color != 2)
	{
		for (int i = 0; i<ENEMY_NUM2; i++)
		{
			if (hero.check_collision(enemy3[i].x_pos, enemy3[i].y_pos) == true)
			{
				enemy3[i].init((float)(rand() % 550), rand() % 100 + 500);

			}
		}
	}
	if (bullet.color != 3)
	{
		for (int i = 0; i<ENEMY_NUM; i++)
		{
			if (hero.check_collision(enemy4[i].x_pos, enemy4[i].y_pos) == true)
			{
				enemy4[i].init((float)(rand() % 150 + 500), rand() % 500);

			}
		}
	}


	//적들 처리 
	for (int j = 0; j<ENEMY_NUM; j++)
	{
		if (enemy[j].y_pos > 500)
			enemy[j].init((float)(rand() % 550), rand() % 200 - 300);
		else
			enemy[j].move();
	}
	for (int j = 0; j<ENEMY_NUM2; j++)
	{
		if (enemy2[j].y_pos > 550)
			enemy2[j].init((float)(rand() % 550), rand() % 500 - 550);
		else
			enemy2[j].move();
	}
	for (int j = 0; j<ENEMY_NUM2; j++)
	{
		if (enemy3[j].y_pos < -50)
			enemy3[j].init((float)(rand() % 550), rand() % 100 + 500);
		else
			enemy3[j].move();
	}
	for (int j = 0; j<ENEMY_NUM; j++)
	{
		if (enemy4[j].x_pos < -50)
			enemy4[j].init((float)(rand() % 150 + 500), rand() % 500);
		else
			enemy4[j].move();
	}
	if (hero.Hp >= 1){
	// 총알 쿨타임 처리
		if (bullet.cooldown < 10)
		{
			bullet.colorchange();
		}
		

	//위로 나가는 총알 처리 
	if (bullet.show() == false)
	{
		if (KEY_DOWN(VK_SPACE))
		{
			bullet.active();
			bullet.init(hero.x_pos, hero.y_pos);
		}
		

		

	}
	if (bullet.show() == true)
	{
		if (bullet.y_pos < -70)
			bullet.hide();
		else
			bullet.move();


		//충돌 처리 
		if (bullet.color == 0)
		{
			for (int i = 0; i<ENEMY_NUM; i++)
			{
				if (bullet.check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
				{
					enemy[i].init((float)(rand() % 550), rand() % 200 - 300);

				}
			}
		}
		if (bullet.color == 1)
		{
			for (int i = 0; i<ENEMY_NUM2; i++)
			{
				if (bullet.check_collision(enemy2[i].y_pos, enemy2[i].x_pos) == true)
				{
					enemy2[i].init((float)(rand() % 550), rand() % 500 - 550);

				}
			}
		}
		if (bullet.color == 2)
		{
			for (int i = 0; i<ENEMY_NUM2; i++)
			{
				if (bullet.check_collision(enemy3[i].x_pos, enemy3[i].y_pos) == true)
				{
					enemy3[i].init((float)(rand() % 550), rand() % 100 + 500);

				}
			}
		}
		if (bullet.color ==3)
		{
			for (int i = 0; i<ENEMY_NUM; i++)
			{
				if (bullet.check_collision(enemy4[i].x_pos, enemy4[i].y_pos) == true)
				{
					enemy4[i].init((float)(rand() % 150 + 500), rand() % 500);

				}
			}
		}


	}
	//아래로 나가는 총알 처리
	if (bullet2.show() == false)
	{
		if (KEY_DOWN(VK_SPACE))
		{
			bullet2.active();
			bullet2.init(hero.x_pos, hero.y_pos);
		}




	}

	if (bullet2.show() == true)
	{
		if (bullet2.y_pos > 550)
			bullet2.hide();
		else
			bullet2.move();


		//충돌 처리 
		if (bullet.color == 0)
		{
			for (int i = 0; i<ENEMY_NUM; i++)
			{
				if (bullet2.check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
				{
					enemy[i].init((float)(rand() % 500), rand() % 200 - 300);

				}
			}
		}
		if (bullet.color == 1)
		{
			for (int i = 0; i<ENEMY_NUM2; i++)
			{
				if (bullet2.check_collision(enemy2[i].y_pos, enemy2[i].x_pos) == true)
				{
					enemy2[i].init((float)(rand() % 550), rand() % 500 - 550);

				}
			}
		}
		if (bullet.color == 2)
		{
			for (int i = 0; i<ENEMY_NUM2; i++)
			{
				if (bullet2.check_collision(enemy3[i].x_pos, enemy3[i].y_pos) == true)
				{
					enemy3[i].init((float)(rand() % 550), rand() % 100 + 500);

				}
			}
		}
		if (bullet.color == 3)
		{
			for (int i = 0; i<ENEMY_NUM; i++)
			{
				if (bullet2.check_collision(enemy4[i].x_pos, enemy4[i].y_pos) == true)
				{
					enemy4[i].init((float)(rand() % 150 + 500), rand() % 500);

				}
			}
		}

	}

	//왼쪽으로 나가는 총알 처리
	if (bullet3.show() == false)
	{
		if (KEY_DOWN(VK_SPACE))
		{
			bullet3.active();
			bullet3.init(hero.x_pos, hero.y_pos);
		}




	}

	if (bullet3.show() == true)
	{
		if (bullet3.x_pos < 0)
			bullet3.hide();
		else
			bullet3.move();


		//충돌 처리 
		if (bullet.color == 0)
		{
			for (int i = 0; i<ENEMY_NUM; i++)
			{
				if (bullet3.check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
				{
					enemy[i].init((float)(rand() % 500), rand() % 200 - 300);

				}
			}
		}
		if (bullet.color == 1)
		{
			for (int i = 0; i<ENEMY_NUM2; i++)
			{
				if (bullet3.check_collision(enemy2[i].y_pos, enemy2[i].x_pos) == true)
				{
					enemy2[i].init((float)(rand() % 550), rand() % 500 - 550);

				}
			}
		}
		if (bullet.color == 2)
		{
			for (int i = 0; i<ENEMY_NUM2; i++)
			{
				if (bullet3.check_collision(enemy3[i].x_pos, enemy3[i].y_pos) == true)
				{
					enemy3[i].init((float)(rand() % 550), rand() % 100 + 500);

				}
			}
		}
		if (bullet.color == 3)
		{
			for (int i = 0; i<ENEMY_NUM; i++)
			{
				if (bullet3.check_collision(enemy4[i].x_pos, enemy4[i].y_pos) == true)
				{
					enemy4[i].init((float)(rand() % 150 + 500), rand() % 500);

				}
			}
		}

	}

	//오른쪽으로 나가는 총알 처리
	if (bullet4.show() == false)
	{
		if (KEY_DOWN(VK_SPACE))
		{
			bullet4.active();
			bullet4.init(hero.x_pos, hero.y_pos);
		}




	}

	if (bullet4.show() == true)
	{
		if (bullet4.x_pos > 550)
			bullet4.hide();
		else
			bullet4.move();


		//충돌 처리 
		if (bullet.color == 0)
		{
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				if (bullet4.check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
				{
					enemy[i].init((float)(rand() % 500), rand() % 200 - 300);

				}
			}
		}
		if (bullet.color == 1)
		{
			for (int i = 0; i < ENEMY_NUM2; i++)
			{
				if (bullet4.check_collision(enemy2[i].y_pos, enemy2[i].x_pos) == true)
				{
					enemy2[i].init((float)(rand() % 550), rand() % 500 - 550);

				}
			}
		}
		if (bullet.color == 2)
		{
			for (int i = 0; i < ENEMY_NUM2; i++)
			{
				if (bullet4.check_collision(enemy3[i].x_pos, enemy3[i].y_pos) == true)
				{
					enemy3[i].init((float)(rand() % 550), rand() % 100 + 500);

				}
			}
		}
		if (bullet.color == 3)
		{
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				if (bullet4.check_collision(enemy4[i].x_pos, enemy4[i].y_pos) == true)
				{
					enemy4[i].init((float)(rand() % 150 + 500), rand() % 500);

				}
			}
		}
	}
	}



}

// this is the function used to render a single frame
void render_frame(void)
{
	bullet.cooldown--;

	// clear the window to a deep blue
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();    // begins the 3D scene

	d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

											 //UI 창 렌더링 


											 /*
											 static int frame = 21;    // start the program on the final frame
											 if(KEY_DOWN(VK_SPACE)) frame=0;     // when the space key is pressed, start at frame 0
											 if(frame < 21) frame++;     // if we aren't on the last frame, go to the next frame

											 // calculate the x-position
											 int xpos = frame * 182 + 1;

											 RECT part;
											 SetRect(&part, xpos, 0, xpos + 181, 128);
											 D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
											 D3DXVECTOR3 position(150.0f, 50.0f, 0.0f);    // position at 50, 50 with no depth
											 d3dspt->Draw(sprite, &part, &center, &position, D3DCOLOR_ARGB(127, 255, 255, 255));
											 */

	RECT part3;
	SetRect(&part3, 0, 0, 370, 500);
	D3DXVECTOR3 center3(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	D3DXVECTOR3 position3(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
	d3dspt->Draw(sprite_bg, &part3, &center3, &position3, D3DCOLOR_ARGB(255, 255, 255, 255));



	if (hero.Hp >= 1)
	{
		////총알 
		if (bullet.bShow == true)
		{
			if (bullet.color == 0)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet.x_pos, bullet.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 255, 255, 255));
			}
			if (bullet.color == 1)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet.x_pos, bullet.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 237, 64, 61));
			}
			if (bullet.color == 2)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet.x_pos, bullet.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 0, 255, 0));
			}
			if (bullet.color == 3)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet.x_pos, bullet.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 0, 204, 255));
			}
		}
		if (bullet2.bShow == true)
		{
			if (bullet.color == 0)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet2.x_pos, bullet2.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 255, 255, 255));
			}
			if (bullet.color == 1)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet2.x_pos, bullet2.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 237, 64, 61));
			}
			if (bullet.color == 2)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet2.x_pos, bullet2.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 0, 255, 0));
			}
			if (bullet.color == 3)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet2.x_pos, bullet2.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 0, 204, 255));
			}
		}
		if (bullet3.bShow == true)
		{
			if (bullet.color == 0)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet3.x_pos, bullet3.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 255, 255, 255));
			}
			if (bullet.color == 1)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet3.x_pos, bullet3.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 237, 64, 61));
			}
			if (bullet.color == 2)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet3.x_pos, bullet3.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 0, 255, 0));
			}
			if (bullet.color == 3)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet3.x_pos, bullet3.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 0, 204, 255));
			}
		}
		if (bullet4.bShow == true)
		{
			if (bullet.color == 0)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet4.x_pos, bullet4.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 255, 255, 255));
			}
			if (bullet.color == 1)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet4.x_pos, bullet4.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 237, 64, 61));
			}
			if (bullet.color == 2)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet4.x_pos, bullet4.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 0, 255, 0));
			}
			if (bullet.color == 3)
			{
				RECT part1;
				SetRect(&part1, 0, 0, 64, 64);
				D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1(bullet4.x_pos, bullet4.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(170, 0, 204, 255));
			}
		}

	}

	//주인공
		if (hero.Hp >= 1)
		{
			if (bullet.color == 0)
			{
				RECT part; 
				SetRect(&part, 0, 0, 64, 64);
				D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_hero, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			if (bullet.color == 1)
			{
				RECT part; 
				SetRect(&part, 0, 0, 64, 64);
				D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_hero, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 100, 100));
			}
			if (bullet.color == 2)
			{
				RECT part;  
				SetRect(&part, 0, 0, 64, 64);
				D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_hero, &part, &center, &position, D3DCOLOR_ARGB(255, 100, 255, 100));
			}
			if (bullet.color == 3)
			{
				RECT part; 
				SetRect(&part, 0, 0, 64, 64);
				D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_hero, &part, &center, &position, D3DCOLOR_ARGB(255, 100, 100, 255));
			}
			
		}
		
	
	
	////에네미 
	RECT part2;
	SetRect(&part2, 0, 0, 64, 64);
	D3DXVECTOR3 center2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	for (int i = 0; i<ENEMY_NUM; i++)
	{

		D3DXVECTOR3 position2(enemy[i].x_pos, enemy[i].y_pos, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_enemy, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	////에네미 2
	RECT part5;
	SetRect(&part5, 0, 0, 64, 64);
	D3DXVECTOR3 center5(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	for (int i = 0; i<ENEMY_NUM2; i++)
	{

		D3DXVECTOR3 position5(enemy2[i].y_pos, enemy2[i].x_pos, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_enemy2, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 233, 30, 58));
	}

	////에네미 3
	RECT part6;
	SetRect(&part6, 0, 0, 64, 64);
	D3DXVECTOR3 center6(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	for (int i = 0; i<ENEMY_NUM2; i++)
	{

		D3DXVECTOR3 position6(enemy3[i].x_pos, enemy3[i].y_pos, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_enemy2, &part6, &center6, &position6, D3DCOLOR_ARGB(255, 100, 255, 100));
	}

	////에네미 4
	RECT part7;
	SetRect(&part7, 0, 0, 64, 64);
	D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	for (int i = 0; i<ENEMY_NUM; i++)
	{

		D3DXVECTOR3 position7(enemy4[i].x_pos, enemy4[i].y_pos, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_enemy, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 100, 100, 255));
	}
	////체력 UI
	RECT part8;
	SetRect(&part8, 0, 0, 32, 32);
	D3DXVECTOR3 center8(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	for (int i = 0; i<ENEMY_NUM; i++)
	{
		if (hero.Hp >=1)
		{
			D3DXVECTOR3 position8(10, 10, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_hp, &part8, &center8, &position8, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		
		if (hero.Hp >= 2)
		{
			D3DXVECTOR3 position9(30, 10, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_hp, &part8, &center8, &position9, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		
		if (hero.Hp >= 3)
		{
			D3DXVECTOR3 position10(50, 10, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_hp, &part8, &center8, &position10, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (hero.Hp >= 4)
		{
			D3DXVECTOR3 position11(70, 10, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_hp, &part8, &center8, &position11, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (hero.Hp >= 5)
		{
			D3DXVECTOR3 position12(90, 10, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_hp, &part8, &center8, &position12, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (hero.Hp >= 6)
		{
			D3DXVECTOR3 position13(110, 10, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_hp, &part8, &center8, &position13, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		if (hero.Hp >= 7)
		{
			D3DXVECTOR3 position14(130, 10, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_hp, &part8, &center8, &position14, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////




	d3dspt->End();    // end sprite drawing

	d3ddev->EndScene();    // ends the 3D scene

	d3ddev->Present(NULL, NULL, NULL, NULL);

	return;
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	sprite->Release();
	d3ddev->Release();
	d3d->Release();

	//객체 해제 
	sprite_hero->Release();
	sprite_enemy->Release();
	sprite_bullet->Release();

	return;
}
