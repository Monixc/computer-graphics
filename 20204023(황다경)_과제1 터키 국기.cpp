/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 작성일: 2023.04.02
// 과  목: 컴퓨터그래픽스
// 학  번: 20204023
// 이  름: 황다경
// 문  제: 키보드 이벤트를 사용하여 터키 국가를 그리시오. (1: 큰 원, 2:작은 원, 3:별, enter:전체 도형)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <math.h>

//Display 콜백 함수
void display() {
	glClearColor(0.9, 0.0, 0.0, 1.0); //배경색을 조금 어두운 빨간색으로
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//큰 흰색 원을 만드는 함수 white_circle()
void white_circle()
{
	glColor3f(1.0, 1.0, 1.0); //원의 색 흰색으로

	double radius = 0.35;

	glPushMatrix(); 
	glScalef(2.5, 2.5, 2.5); // 크기 2.5배
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		double angle = i * 3.14 / 180;
		double x = radius * cos(angle);
		double y = radius * sin(angle);
		glVertex2f(x -0.3, y);
	}
	glEnd();
	glPopMatrix(); 

	glFlush();
}

//작은 빨간색 원을 만드는 함수 red_circle()
void red_circle()
{
	glColor3f(0.9, 0.0, 0.0); //원의 색 빨간색으로(배경색과 동일)

	double radius = 0.27;

	glPushMatrix(); 
	glScalef(2.5, 2.5, 2.5);// 크기 2.5배
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		double angle = i * 3.141592 / 180;
		double x = radius * cos(angle);
		double y = radius * sin(angle);
		glVertex2f(x - 0.2, y);
	}
	glEnd();
	glPopMatrix(); 

	glFlush();
}
void star()
{
	glPushMatrix();
	glScalef(3.0, 3.0, 3.0); //크기 3배
	glColor3f(1.0, 1.0, 1.0); //별의 색 흰색
	glTranslatef(0, 0.05, 0);
	//삼각형 3개를 합쳐 꼭짓점이 5인 별을 생성
	glBegin(GL_TRIANGLES);
	glVertex3f(0.09, 0.084, 0);
	glVertex3f(0.09, -0.164, 0);
	glVertex3f(0.18, -0.04, 0);

	glBegin(GL_TRIANGLES);
	glVertex3f(0.09, 0.084, 0);
	glVertex3f(0.235, -0.116, 0);
	glVertex3f(0.089, -0.069, 0);

	glBegin(GL_TRIANGLES);
	glVertex3f(0, -0.04, 0);
	glVertex3f(0.235, 0.037, 0);
	glVertex3f(0.145, -0.087, 0);
	glEnd();

	
	glPopMatrix();
	glFlush();
}

//키보드 이벤트
void keyboardProcess(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'1':
		white_circle(); //키보드 1번을 누르면 흰색 원이 그려짐
		break;
	case'2':
 		red_circle(); //키보드 2번을 누르면 빨간색 원이 그려짐
		break;
	case'3':
		star(); //키보드 3번을 누르면 흰색 별이 그려짐
		break;
	case'\r': //엔터를 누르면 모든 도형이 한번에 그려짐
		white_circle();
		red_circle();
		star();
		break;
	}
}
void init(void)
{
	glClearColor(1.0, 0.0, 0.0, 0.0); //윈도우 배경을 빨간색으로 설정
	glClear(GL_COLOR_BUFFER_BIT); //색상 버퍼 삭제
}
//reshape 콜백 함수 호출
void reshape(int new_w, int new_h)
{
	glViewport(0, 0, new_w, new_h);
	float WidthFactor = (float)new_w / 250.0;
	float HeightFactor = (float)new_h / 250.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//직교 투영 left, right, bottom, top, near, far
	gluOrtho2D(-1.0* WidthFactor, 1.0*WidthFactor, -1.0*HeightFactor, 1.0*HeightFactor);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv); //GLUT 상태 초기화
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //디스플레이모드 형식 single  & rgba 선택

	glutInitWindowSize(600, 400); //윈도우 창의 크기 설정
	glutInitWindowPosition(100, 100); //윈도우 창의 위치 설정
	glutCreateWindow("20204023_터키"); //윈도우 생성, 이름은 20204023_터키로 설정
	init();

	//display, reshape 콜백 함수 등록
	glutDisplayFunc(display);  
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardProcess); //이벤트 처리 엔진 시작

	glutMainLoop();
	return 0;
}
