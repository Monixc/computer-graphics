/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 작성일: 2023.04.03
// 과  목: 컴퓨터그래픽스
// 학  번: 20204023
// 이  름: 황다경
// 문  제: 삼각형 두개를 사용하여 별 생성 후, 마우스 이벤트를 사용하여 별자리를 생성
//         1. 마우스 좌클릭 시 클릭한 위치에 별 생성(생성된 별들 사이에는 중점을 잇는 선이 함께 생성)
//         2. 마우스 우클릭 시 화면에 존재하는 모든 별이 회전(토글 기능 추가하여 재클릭시 회전 방향 변경)
//         3. 마우스 가운데 버튼 클릭 시 화면에 존재하는 별들의 색 변경
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <GL/glut.h>

//이전 마우스 클릭 시 생성된 삼각형의 중점좌표 x, y를 저장하는 변수
float PreX = 0.0f;
float PreY = 0.0f;
float angle = 0.0f;
//생성된 별의 개수를 저장하는 변수
int StarNum = 0;
//회전방향을 변경하기 위한 변수
int r_direction = 1;
//생성된 별이 존재하는지 확인
bool isExist = false;
//마우스 가운데 버튼이 클릭되었는지를 확인하는 변수
bool isClicked_m = false;
bool isClicked_r = false;
//생성된 별의 좌표를 저장하는 배열 X_array, Y_array. 각각 i번째 별의 x좌표와 y좌표를 저장
GLfloat X_array[100];
GLfloat Y_array[100];
//생성된 선들의 좌표을 저장하는 배열 X_lines, Y_lines
GLfloat X_lines[100];
GLfloat Y_lines[100];

GLfloat RED = 0.0f;
GLfloat GREEN = 0.0f;
GLfloat BLUE = 0.0f;

GLint index = 0;
GLfloat Delta = 0.0f;

void Animation();

//색상 팔레트
unsigned char COLORS[9][3] = {
	//white, cyan, purple, Light Gray, Dark Gray, Dark Red, Dard Green, Dark Blue, Black
	{255,255,255}, {0, 255, 255}, {255, 0, 255}, {192, 192, 192}, {128, 128, 128}, {128, 0, 0},
	{0, 128, 0}, {0, 0, 128}, {0, 0, 0}
};

//timerProcess()가 호출되면 색이 변하는 동작 수행
void timerProcess(int value)
{
	if (Delta < 2.0f)
	{
		Delta = Delta + 0.01f;
		if (++index >= 8)
		{
			index = 0;
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
	else
	{
		Delta = 0.0f;
	}
	glutPostRedisplay();
	glutTimerFunc(1000, timerProcess, 1);
}

//회전 애니메이션을 위해 사용하는 idle callback 함수
void idleProcess()
{
	angle += 0.1;
	if (angle > 360.0)
		angle = 0.0f;
	glutPostRedisplay();
}
void color_change()
{
	RED = COLORS[index][0] / 255.0f;
	GREEN = COLORS[index][1] / 255.0f;
	BLUE = COLORS[index][2] / 255.0f;

	glColor3f(RED, GREEN, BLUE);
}
void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); //초기 화면을 검은색으로 설정
	//rotate_Animation()을 호출, 마우스 이벤트 발생 시 idle/timer을 사용하여 애니메이션 동작
	//마우스 가운데 버튼 혹은 오른쪽 버튼이 클릭 되었을 경우에만 호출되도록 설정
	if (isClicked_m || isClicked_r)
	{
		Animation();
	}
	
	glutSwapBuffers();
}

//별을 그리는 함수 draw_star()
void star(float x, float y)
{
	//두 개의 삼각형을 사용하여 별을 생성
	glBegin(GL_TRIANGLES);
	//클릭 위치를 x,y로 받아 도형을 생성하므로 각 꼭짓점은 x, y에 일정값을 더하여 설정
	glVertex2f(x, y);
	glVertex2f(x + 30, y);
	glVertex2f(x + 15, y + 35);

	glBegin(GL_TRIANGLES);
	glVertex2f(x, y + 22.5);
	glVertex2f(x + 30, y + 22.5);
	glVertex2f(x + 15, y - 12.5);

	glEnd();
}

//선을 그리는 함수  draw_line()
void line(float px1, float py1, float px2, float py2) {
	glBegin(GL_LINES);
	//선의 양 끝점의 좌표를 입력받아, 선을 생성한다.
	glVertex2f(px1, py1);
	glVertex2f(px2, py2);
	glEnd();
}

//회전과 색 변화를 위한 Animation()함수
void Animation(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 1; i < StarNum+1; i++)
	{
		if (i - 1 > 0)
		{
			line(X_lines[i - 1], Y_lines[i - 1], X_lines[i], Y_lines[i]);
		}

		glPushMatrix(); //변환 좌표 저장
		//별의 중점을 계산. 별을 이루는 삼각형의 세 꼭지점의 x,y값의 평균을 구함
		//translatef을 사용하여 오브젝트의 중심점을 원점으로 이동시켜 회전을 수행한 후, 다시 중심점 이동
		glTranslatef((3 * X_array[i] + 45) / 3.0, (3 * Y_array[i] + 35) / 3.0, 0.0);
		glRotatef(r_direction* angle, 0.0, 0.0, 1.0);
		glTranslatef(-1.0*(3 * X_array[i] + 45) / 3.0, -1.0*(3 * Y_array[i] + 35) / 3.0, 0.0);
		//glColor3f(250.0,0.0, 0.0);
		star(X_array[i], Y_array[i]);
		glPopMatrix(); //변환 좌표 호출
	}
	//마우스 가운데 버튼이 클릭되면 color_change()호출

	if (isClicked_m)
	{
		color_change();
	}
}
//마우스 클릭 이벤트
void mouseFunc(int button, int state, int x, int y) {
	//마우스 좌클릭 시
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//클릭 위치의 좌표를 받아 x,y에 저장
		//마우스 클릭 위치 click_x, click_y를 받아 OPENGL 좌표계로 변환
		//윈도우 좌표계와 OPENGL 좌표계는 반대이므로, 창의 높이에서 y좌표값을 뺌.
		float click_x = (float)x;
		float click_y = 400 - (float)y;

		click_x = click_x / 600 * 600;
		click_y = click_y / 400 * 600;

		//glutSwapBuffers는 더블 버퍼로, 전면 후면 버퍼가 있기 때문에 glutPostRedisplay()를 사용하지 않으면
		//클릭할때마다 짝수번째, 홀수번째 생성된 별들이 번갈아가면서 노출됨
		glutPostRedisplay();
		glutSwapBuffers();

		// 클릭한 위치에 별을 그림
		glColor3f(250.0, 250.0, 0.0);
		star(click_x, click_y);
		StarNum++;

		//isExist=true 일 경우, 즉 이전에 생성된 별이 존재할 경우 선을 생성
		if (isExist) {
			//이전에 생성된 별의 중점이 되는 좌표(PreX, PreY)와 새로 생성된 별의 삼각형 중점 (click_x,click_y)를 px1,py1,px2,py2로 받아 선을 생성
			glColor3f(250.0, 250.0, 0.0);
			line(PreX, PreY, click_x + 10, click_y + 10);
		}

		//isExist를 true로 변경
		isExist = true;
		//PreX와 PreY에 저장되는 좌표값 갱신
		PreX = click_x + 10;
		PreY = click_y + 10;

		//배열에 별과 선의 좌표 저장
		X_array[StarNum] = click_x;
		Y_array[StarNum] = click_y;
		X_lines[StarNum] = PreX;
		Y_lines[StarNum] = PreY;
	}
	//마우스 우클릭 시
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//isClicked_r을 true로 변경
		isClicked_r = true;
		//r_direction에 -1을 곱하여 회전 방향 변경. 우클릭을 할 때마다 회전 방향이 변경됨
		r_direction *= -1;
		//idleFunc를 호출하여 도형이 회전하는 동작을 수행
		glutIdleFunc(idleProcess);

	}
	//마우스 가운데 버튼 클릭 시
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		//isClicked_m을 true로 변경
		isClicked_m = true;
		//timerFunc를 호출하여, 도형의 색이 변하는 동작을 수행
		glutTimerFunc(2000, timerProcess, 1);
	}
}

//OpenGL 초기화 함수 init()
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 600.0, 0.0, 600.0);
	glLoadIdentity;
}

//메인함수
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //더블 버퍼 설정

	//윈도우 사이즈를 600,400으로 설정/윈도우 생성 위치를 100,100으로 설정
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("별자리");
	init();

	glutDisplayFunc(display);
	glutMouseFunc(mouseFunc);

	glutMainLoop();
	return 0;
}