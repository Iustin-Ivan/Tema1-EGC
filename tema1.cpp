#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"
#define SIZEPINKSTAR 40
#define SIZEHEX 40


using namespace std;
using namespace m1;

int nrlives = 3;
int points = 5;
int poslives = 850;
int pospoints = 860;
int cost;
vector<pair<int, int>> pinkstars;

int timerpinkstars = 25000;
int timerenemies;
int enemieslim = 25000;
float timelapsed;
int timerpinkfallingstars;
float timerprojectiles[9];

int xstartgreen[9] = { 100, 250, 400, 100, 250, 400, 100, 250, 400 };
int xendgreen[9] = { 225, 375, 525, 225, 375, 525, 225, 375, 525};
int ystartgreen[9] = { 325, 325, 325, 175, 175, 175, 25, 25, 25 };
int yendgreen[9] = { 450, 450, 450, 300, 300, 300, 150, 150, 150 };
bool insidesquare[9] = { false, false, false, false, false, false, false, false, false };
int xstartblackedges[4] = { 50, 250, 450, 650 };
int xendblackedges[4] = { 175, 375, 575, 775 };
int ystartblackedges[4] = { 575, 575, 575, 575 };
int yendblackedges[4] = { 700, 700, 700, 700 };
int costsdiamonds[4] = { 1, 2, 2, 3 };
int xrenderpoints[9] = {150, 300, 450, 150, 300, 450, 150, 300, 450};
int yrenderpoints[9] = { 325, 325, 325, 175, 175, 175, 25, 25, 25 };
bool tobedeleted[9];
float scalesX[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
float scalesY[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int YHEX[3] = { 375, 225, 75 };
string colors[4] = { "orange", "blue", "yellow", "purple" };
Mesh* diamonds[4];

Mesh* objectsquare[9];
string colorsquares[9] = {"", "", "", "", "", "", "", "", ""};

string draggedcolor;

Mesh *draggedObject;

bool insidediamond;

typedef struct enemy {
	int x;
	int y;
	char line;
	int translateX;
	int lives;
	bool shrink;
	float scaleX;
	float scaleY;
	string color;
	Mesh* bighex;
	Mesh* smallhex;
} enemy;

typedef struct projectile {
	int x;
	int y;
	char line;
	int translateX;
	float angle;
	string color;
	Mesh* star;
} projectile;

typedef struct fallingstar {
	int x;
	int y;
	int translateY;
	int finalY;
}fallingstar;

vector<fallingstar> fallingstars;

vector<enemy> enemies;
vector<projectile> projectiles;
vector<projectile*> deletedprojectiles;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// TODO(student): Compute coordinates of a square's center, and store
	// then in the `cx` and `cy` class variables (see the header). Use
	// `corner` and `squareSide`. These two class variables will be used
	// in the `Update()` function. Think about it, why do you need them?

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	// Initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;


	// Initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;





	Mesh* lightgreensquare = object2D::CreateSquare("greensquare", corner, 125, glm::vec3(0.5f, 1, 0.5f), true);
	AddMeshToList(lightgreensquare);

	Mesh* redsquare = object2D::CreateSquare("redsquare", corner, 75, glm::vec3(1, 0, 0), true);
	AddMeshToList(redsquare);

	Mesh* blackedgesquare = object2D::CreateSquare("blackedgesquare", corner, 125, glm::vec3(0, 0, 0), false);
	AddMeshToList(blackedgesquare);

	Mesh* redrectangle = object2D::CreateRectangle("redrectangle", glm::vec3(0, 0, 0.7f), 425, 50, glm::vec3(1, 0, 0), true);
	AddMeshToList(redrectangle);

	Mesh* greystar = object2D::CreateStar("greystar", corner, 50, glm::vec3(0.7f, 0.7f, 0.7f), 20);
	AddMeshToList(greystar);

	Mesh* pinkstar = object2D::CreateStar("pinkstar", corner, 50, glm::vec3(1, 0.f, 1), SIZEPINKSTAR);
	AddMeshToList(pinkstar);

	Mesh *orangestar = object2D::CreateStar("orangestar", corner, 50, glm::vec3(1, 0.4f, 0), 40);
	AddMeshToList(orangestar);

	Mesh* bluestar = object2D::CreateStar("bluestar", corner, 50, glm::vec3(0, 0, 1), 40);
	AddMeshToList(bluestar);

	Mesh* yellowstar = object2D::CreateStar("yellowstar", corner, 50, glm::vec3(1, 1, 0), 40);
	AddMeshToList(yellowstar);

	Mesh* purplestar = object2D::CreateStar("purplestar", corner, 50, glm::vec3(0.6f, 0, 1), 40);
	AddMeshToList(purplestar);

	Mesh* orangediamond = object2D::CreateDiamond("orangediamond", corner, 100, 20, glm::vec3(1, 0.4f, 0), true);
	AddMeshToList(orangediamond);

	Mesh* bluediamond = object2D::CreateDiamond("bluediamond", corner, 100, 20, glm::vec3(0, 0, 1), true);
	AddMeshToList(bluediamond);

	Mesh* yellowdiamond = object2D::CreateDiamond("yellowdiamond", corner, 100, 20, glm::vec3(1, 1, 0), true);
	AddMeshToList(yellowdiamond);

	Mesh* purplediamond = object2D::CreateDiamond("purplediamond", corner, 100, 20, glm::vec3(0.6f, 0, 1), true);
	AddMeshToList(purplediamond);

	Mesh* yellowhex = object2D::CreateHex("yellowhex", glm::vec3(1, 1, 0), true, 40);
	AddMeshToList(yellowhex);

	Mesh* bluehex = object2D::CreateHex("bluehex", glm::vec3(0, 0, 1), true, 40);
	AddMeshToList(bluehex);

	Mesh* orangehex = object2D::CreateHex("orangehex", glm::vec3(1, 0.4f, 0), true, 40);
	AddMeshToList(orangehex);

	Mesh* purplehex = object2D::CreateHex("purplehex", glm::vec3(0.6f, 0, 1), true, 40);
	AddMeshToList(purplehex);

	Mesh* blacksmallhex = object2D::CreateSmallHex("blacksmallhex", glm::vec3(0, 0, 0), true, 25);
	AddMeshToList(blacksmallhex);

	diamonds[0] = meshes["orangediamond"];
	diamonds[1] = meshes["bluediamond"];
	diamonds[2] = meshes["yellowdiamond"];
	diamonds[3] = meshes["purplediamond"];

}


void Tema1::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.2, 0.2, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// first row
	modelMatrix = transform2D::Translate(100, 325);
	RenderMesh2D(meshes["greensquare"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(250, 325);
	RenderMesh2D(meshes["greensquare"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(400, 325);
	RenderMesh2D(meshes["greensquare"], shaders["VertexColor"], modelMatrix);
	// second row
	modelMatrix = transform2D::Translate(100, 175);
	RenderMesh2D(meshes["greensquare"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(250, 175);
	RenderMesh2D(meshes["greensquare"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(400, 175);
	RenderMesh2D(meshes["greensquare"], shaders["VertexColor"], modelMatrix);
	// third row
	modelMatrix = transform2D::Translate(100, 25);
	RenderMesh2D(meshes["greensquare"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(250, 25);
	RenderMesh2D(meshes["greensquare"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(400, 25);
	RenderMesh2D(meshes["greensquare"], shaders["VertexColor"], modelMatrix);
	// black edges
	modelMatrix = transform2D::Translate(50, 575);
	RenderMesh2D(meshes["blackedgesquare"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(250, 575);
	RenderMesh2D(meshes["blackedgesquare"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(450, 575);
	RenderMesh2D(meshes["blackedgesquare"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(650, 575);
	RenderMesh2D(meshes["blackedgesquare"], shaders["VertexColor"], modelMatrix);
	// barrier
	modelMatrix = transform2D::Translate(25, 25);
	RenderMesh2D(meshes["redrectangle"], shaders["VertexColor"], modelMatrix);
	// cost of diamonds
	modelMatrix = transform2D::Translate(60, 550);
	RenderMesh2D(meshes["greystar"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(260, 550);
	RenderMesh2D(meshes["greystar"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(300, 550);
	RenderMesh2D(meshes["greystar"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(460, 550);
	RenderMesh2D(meshes["greystar"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(500, 550);
	RenderMesh2D(meshes["greystar"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(660, 550);
	RenderMesh2D(meshes["greystar"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(700, 550);
	RenderMesh2D(meshes["greystar"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(740, 550);
	RenderMesh2D(meshes["greystar"], shaders["VertexColor"], modelMatrix);
	// diamonds
	modelMatrix = transform2D::Translate(100, 590);
	RenderMesh2D(meshes["orangediamond"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(300, 590);
	RenderMesh2D(meshes["bluediamond"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(500, 590);
	RenderMesh2D(meshes["yellowdiamond"], shaders["VertexColor"], modelMatrix);
	modelMatrix = transform2D::Translate(700, 590);
	RenderMesh2D(meshes["purplediamond"], shaders["VertexColor"], modelMatrix);


	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
	// TODO(student): Update steps for translation, rotation and scale,
	// in order to create animations. Use the class variables in the
	// class header, and if you need more of them to complete the task,
	// add them over there!

	// Update steps for translation, rotation, scale, in order to create animations
	glm::ivec2 resolution = window->GetResolution();
	// life counter
	if (nrlives == 0) {
		cout << "GAME OVER" << endl;
		exit(0);
	}
	
	// life counter
	for (int i = 0; i < nrlives; i++) {
		modelMatrix = transform2D::Translate(poslives + i * 100, 600);
		RenderMesh2D(meshes["redsquare"], shaders["VertexColor"], modelMatrix);
	}

	// point counter
	for (int i = 0; i < points; i++) {
		modelMatrix = transform2D::Translate(pospoints + i*40, 550);
		RenderMesh2D(meshes["greystar"], shaders["VertexColor"], modelMatrix);
	}

	// renderstars
	for (auto i = pinkstars.begin(); i < pinkstars.end(); i++) {
		modelMatrix = transform2D::Translate(i->first, i->second);
		RenderMesh2D(meshes["pinkstar"], shaders["VertexColor"], modelMatrix);
	}

	// generate stars
	timerpinkstars += rand() % 100;
	if (timerpinkstars > 30000) {
		if (enemieslim > 15000) {
			pinkstars.push_back(make_pair(rand() % 1280, rand() % 720));
			pinkstars.push_back(make_pair(rand() % 1280, rand() % 720));
			pinkstars.push_back(make_pair(rand() % 1280, rand() % 720));
		}
		else if (enemieslim > 5000){
			pinkstars.push_back(make_pair(rand() % 1280, rand() % 720));
            pinkstars.push_back(make_pair(rand() % 1280, rand() % 720));
		}
		else {
			pinkstars.push_back(make_pair(rand() % 1280, rand() % 720)); 
		}
		timerpinkstars = 0;
	}
	//generate falling stars;
	timerpinkfallingstars += rand() % 100;
	if (timerpinkfallingstars > 15000) {
		fallingstar fallingstar;
		fallingstar.x = rand() % 1280;
		fallingstar.y = 720;
		fallingstar.translateY = 0;
		fallingstar.finalY = rand() % 520;
		fallingstars.push_back(fallingstar);
		timerpinkfallingstars = 0;
	}
	// falling stars
	for (auto i = fallingstars.begin(); i < fallingstars.end(); i++) {
		if (720+i->translateY >= i->finalY) {
			modelMatrix = transform2D::Translate(i->x, i->y);
			i->translateY -= 0.1f * deltaTimeSeconds * resolution.y;
			modelMatrix *= transform2D::Translate(0, i->translateY);
		}
		else {
			modelMatrix = transform2D::Translate(i->x, i->finalY);
		}
		RenderMesh2D(meshes["pinkstar"], shaders["VertexColor"], modelMatrix);
	}
	// generate enemies
	timerenemies += rand() % 100;
	if (timerenemies > enemieslim) {
		enemy hex;
		hex.line = rand() % 3;
		hex.y = YHEX[hex.line];
		hex.x = 1280;
		hex.color = colors[rand() % 4];
		hex.bighex = meshes[hex.color + "hex"];
		hex.smallhex = meshes["blacksmallhex"];
		hex.translateX = 0;
		hex.lives = 3;
		hex.shrink = false;
		hex.scaleX = 1;
		hex.scaleY = 1;
		enemies.push_back(hex);
		timerenemies = 0;
	}
	timelapsed += deltaTimeSeconds;
	if (timelapsed > 5 && enemieslim > 5000) {
		enemieslim -= 1000;
		timelapsed = 0;
	}

	for (int i = 0; i < 9; i++) {
		timerprojectiles[i] += deltaTimeSeconds;
	}

	// render enemies
	int nrenemies = 0;
	vector<int> deletedenemies;
	for (auto i = enemies.begin(); i < enemies.end(); i++) {
		modelMatrix = transform2D::Translate(i->x, i->y);
		modelMatrix *= transform2D::Translate(i->translateX, 0);
		if (i->shrink) {
			i->scaleX -= deltaTimeSeconds;
			i->scaleY -= deltaTimeSeconds;
			if (i->scaleX <= 0) {
				deletedenemies.push_back(nrenemies);
			}
			modelMatrix *= transform2D::Scale(i->scaleX, i->scaleY);
			RenderMesh2D(i->smallhex, shaders["VertexColor"], modelMatrix);
			RenderMesh2D(i->bighex, shaders["VertexColor"], modelMatrix);
		}
		else {
			i->translateX -= 0.05f * deltaTimeSeconds * resolution.x;
			RenderMesh2D(i->smallhex, shaders["VertexColor"], modelMatrix);
			RenderMesh2D(i->bighex, shaders["VertexColor"], modelMatrix);
		}
		if (i->translateX <= -1230) {
			nrlives--;
			deletedenemies.push_back(nrenemies);
		}
		int abs = 1280+i->translateX-SIZEHEX;
		switch(i->line){
			case 0:
				for (int j = 0; j < 3; j++) {
					if (abs > xstartgreen[j] && abs < xendgreen[j] && insidesquare[j]) {
							tobedeleted[j] = true;
							colorsquares[j] = "";
					}
					if (colorsquares[j] == i->color && timerprojectiles[j] >= 2) {
						projectile starprojectile;
						starprojectile.x = xendgreen[j];
						starprojectile.y = ystartgreen[j]+50;
						starprojectile.line = i->line;
						starprojectile.translateX = 0;
						starprojectile.color = i->color;
						starprojectile.star = meshes[i->color + "star"];
						starprojectile.angle = 0;
						projectiles.push_back(starprojectile);
						timerprojectiles[j] = 0;
					}
				}
				break;
			case 1:
				for (int j = 3; j < 6; j++) {
					if (abs > xstartgreen[j] && abs < xendgreen[j] && insidesquare[j]) {
							tobedeleted[j] = true;
							colorsquares[j] = "";
					}
					if (colorsquares[j] == i->color && timerprojectiles[j] >= 2) {
						projectile starprojectile;
						starprojectile.x = xendgreen[j];
						starprojectile.y = ystartgreen[j] + 50;
						starprojectile.line = i->line;
						starprojectile.translateX = 0;
						starprojectile.color = i->color;
						starprojectile.star = meshes[i->color + "star"];
						starprojectile.angle = 0;
						projectiles.push_back(starprojectile);
						timerprojectiles[j] = 0;
					}
				}
				break;
			default:
				for (int j = 6; j < 9; j++) {
					if (abs > xstartgreen[j] && abs < xendgreen[j] && insidesquare[j]) {
							tobedeleted[j] = true;
							colorsquares[j] = "";
					}
					if (colorsquares[j] == i->color && timerprojectiles[j] >= 2) {
						projectile starprojectile;
						starprojectile.x = xendgreen[j];
						starprojectile.y = ystartgreen[j] + 50;
						starprojectile.line = i->line;
						starprojectile.translateX = 0;
						starprojectile.color = i->color;
						starprojectile.star = meshes[i->color + "star"];
						starprojectile.angle = 0;
						projectiles.push_back(starprojectile);
						timerprojectiles[j] = 0;
					}
				}
		}
		nrenemies++;
	}

	// delete enemies
	for (auto i = deletedenemies.begin(); i < deletedenemies.end(); i++) {
		enemies.erase(enemies.begin() + *i);
	}

	// render projectile
	int nr = 0;
	vector<int> deletedprojectiles;
	for (auto i = projectiles.begin(); i < projectiles.end(); i++) {
		i->angle -= 3*deltaTimeSeconds;
		modelMatrix = transform2D::Translate(i->x, i->y);
		i->translateX += 0.2f*deltaTimeSeconds*resolution.x;
		modelMatrix *= transform2D::Translate(i->translateX, 0);
		modelMatrix *= transform2D::Rotate(i->angle);
		if (i->translateX >= 1280) {
			deletedprojectiles.push_back(nr);
		}
		RenderMesh2D(i->star, shaders["VertexColor"], modelMatrix);
		for (auto j = enemies.begin(); j < enemies.end(); j++) {
			if (glm::distance(glm::vec2(i->x + i->translateX, i->y), glm::vec2(j->x + j->translateX, j->y)) < SIZEPINKSTAR + SIZEHEX
				&& i->color == j->color) {
				j->lives--;
				if (j->lives == 0) {
					j->shrink = true;
				}
				deletedprojectiles.push_back(nr);
			}
		}
		nr++;
	}

	// delete projectiles
	for (auto i = deletedprojectiles.begin(); i < deletedprojectiles.end(); i++) {
		projectiles.erase(projectiles.begin() + *i);
	}

	// draw the dragged object
	RenderMesh2D(draggedObject, shaders["VertexColor"], modelMatrixDragged);


	// render the diamonds inside the squares
	for (int i = 0; i < 9; i++) {
		if (insidesquare[i]) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(xrenderpoints[i], yrenderpoints[i]);
			modelMatrix *= transform2D::Scale(scalesX[i], scalesY[i]);
			if (tobedeleted[i]) {
				scalesX[i] -= deltaTimeSeconds;
				scalesY[i] -= deltaTimeSeconds;
				RenderMesh2D(objectsquare[i], shaders["VertexColor"], modelMatrix);
				if (scalesX[i] <= 0 || scalesY[i] <= 0) {
					insidesquare[i] = false;
					tobedeleted[i] = false;
					scalesX[i] = 1;
					scalesY[i] = 1;
				}
			}
			else {
				RenderMesh2D(objectsquare[i], shaders["VertexColor"], modelMatrix);
			}
		}
	}
}


void Tema1::FrameEnd()
{

}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
	// Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event
	int x = mouseX;
	int y = 720 - mouseY;
	if (insidediamond) {
		modelMatrixDragged = transform2D::Translate(x, y);
	}
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
	if (button == GLFW_MOUSE_BUTTON_2) {
		int x = mouseX;
		int y = 720 - mouseY;
		for (auto i = pinkstars.begin(); i < pinkstars.end(); i++) {
			if (x > i->first - SIZEPINKSTAR && x < i->first + SIZEPINKSTAR &&
				y > i->second - SIZEPINKSTAR && y < i->second + SIZEPINKSTAR) {
				points++;
				pinkstars.erase(i);
				break;
			}
		}
		for (auto i = fallingstars.begin(); i < fallingstars.end(); i++) {
			if (x > i->x - SIZEPINKSTAR && x < i->x + SIZEPINKSTAR && 
				y > i->y + i->translateY - SIZEPINKSTAR && y < i->y + i->translateY + SIZEPINKSTAR) {
				points++;
				fallingstars.erase(i);
				break;
			}
		}
		for (int i = 0; i < 4; i++) {
			if (x > xstartblackedges[i] && x < xendblackedges[i] && 
				y > ystartblackedges[i] && y < yendblackedges[i] && costsdiamonds[i] <= points) {
				insidediamond = true;
				draggedObject = diamonds[i];
				cost = costsdiamonds[i];
				modelMatrixDragged = transform2D::Translate(x, y);
				draggedcolor = colors[i];
			}
		}
	}

	if (button == GLFW_MOUSE_BUTTON_3) {
		int x = mouseX;
		int y = 720 - mouseY;
		for (int i = 0; i < 9; i++) {
			if (x > xstartgreen[i] && x < xendgreen[i] && y > ystartgreen[i] && y < yendgreen[i] && insidesquare[i]) {
				tobedeleted[i] = true;
				colorsquares[i] = "";
			}
		}
	}
	
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
	if (button == GLFW_MOUSE_BUTTON_2) {
		int x = mouseX;
		int y = 720 - mouseY;
		bool valid = false;
		for (int i = 0; i < 9; i++) {
			if (x > xstartgreen[i] && x < xendgreen[i] && y > ystartgreen[i] && y < yendgreen[i]) {
				if (draggedObject && !insidesquare[i]) {
					insidesquare[i] = true;
					valid = true;
					points -= cost;
					cost = 0;
					objectsquare[i] = draggedObject;
					colorsquares[i] = draggedcolor;
				}
				draggedObject = NULL;
				draggedcolor = "";
			}
		}
		if (!valid) {
			insidediamond = false;
			draggedObject = NULL;
			draggedcolor = "";
		}
	}
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{

}


void Tema1::OnWindowResize(int width, int height)
{
}
