#include <stdio.h>
#include <bangtal.h>
#include <time.h>
#include <stdlib.h>

SceneID scene0, scene1, scene2;
ObjectID A, B, shop,item0_1 ;//scene1 요소들
ObjectID initHeart[5];
ObjectID gameHeart[5];
ObjectID items[5]; //scene2 요소들
TimerID timer1;

int LHP[5] = { 100, 200, 300, 400, 500 }; // Left Heart Position
int IP[5] = { 200, 300, 550, 800, 1000 }; // Item Position

const Second animationTime = 0.01f;

int i = 200;

void Launch(int j) {
	enterScene(scene1);

	switch(j) {
	case 0: // 단검을 눌렀을때
		showObject(item0_1);
		locateObject(item0_1, scene1, i, 150);
		setTimer(timer1, animationTime);
		startTimer(timer1);

	}
		
}

void HookPick(int j) {
	switch (j) {
	case 0: Launch(0); break;
	//case 1: Launch 

	}



}

void game_init() {

	char heartImage_left[20];
	
	for (int k = 0; k < 5; k++) {
		sprintf_s(heartImage_left, "RH%d.png", k);
		initHeart[k] = createObject(heartImage_left);
		gameHeart[k] = initHeart[k];
		locateObject(gameHeart[k], scene1, LHP[k],550);
		scaleObject(gameHeart[k], 0.7);
		showObject(gameHeart[k]);
	}
	char itemImage[20];

	for (int f = 0; f < 5; f++) {
		sprintf_s(itemImage, "item%d.png", f);
		items[f] = createObject(itemImage);
		locateObject(items[f], scene2, IP[f], 100);
		showObject(items[f]);
		scaleObject(items[f], 0.7);
	}


}
	




void timerCallback(TimerID timer) {

	if (i > 0 && i < 900) {
		i = i + 40;
		setTimer(timer1, animationTime);
		startTimer(timer1);
		Launch(0);
		if (i >= 900) {
			hideObject(item0_1);
			i = 0;
		}

		


			

	}

	
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if(object == items[0]){
		launch(0);
		i = 200;
		}

	if (object == shop) {
		enterScene(scene2);
	}
	
	
}


int main() {

	setMouseCallback(mouseCallback);

	scene0 = createScene("후크 선장과의 결투", "후크vs피터팬.jpg");
	scene1 = createScene("후크 선장과의 결투", "전투창.jpg");
	scene2 = createScene("아이템 선택", "상점창.jpg");


	A = createObject("피터팬.png");
	locateObject(A, scene1, 100, 0);
	showObject(A);

	B = createObject("후크선장.png");
	locateObject(B, scene1, 900, 0);
	showObject(B);

	shop = createObject("상점.png");
	locateObject(shop, scene1, 600, 550);
	showObject(shop);
	scaleObject(shop, 0.5f);


	item0_1 = createObject("단검_왼-오.png");
	locateObject(item0_1, scene2, 100, 40);
	hideObject(item0_1);
	scaleObject(item0_1, 0.5f);


	game_init();


	setTimerCallback(timerCallback);
	timer1 = createTimer(10.0f);
	startTimer(timer1);
	startGame(scene1);

}