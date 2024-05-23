/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 작성일: 2023.04.04
// 과  목: 컴퓨터그래픽스
// 학  번: 20204023
// 이  름: 황다경
// 문  제: 태극기 그리기
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14

//반지름, rgb값, 반원여부를 받아 원을 그리는 함수 DrawCircle()
void DrawCircle(float radius, float r, float g, float b, int half)
{
	glColor3f(r, g, b); //rgb값을 받아 색 결정
	glBegin(GL_POLYGON); //원 그리기
	if (half == 0) //int half의 값이 0이면 원을 그림
	{
		for (int i = 0; i < 360; i++)
		{
			float angle = i * PI / 180;
			glVertex3f(cos(angle) * radius, sin(angle)*radius, 0);
		}
	}
	else if (half == 1) //half의 값이 1이면 반원을 그림
	{
		for (int i = 0; i < 180; i++)
		{
			float angle = i * PI / 180;
			glVertex3f(cos(angle) * radius, sin(angle)*radius, 0);
		}
	}
	glEnd();
}

//4괘의 구성요소 중 하나의 선을 그리는 함수 DrawLine()
void DrawLine()
{
	glColor3f(0, 0, 0); //검은색
	glBegin(GL_POLYGON);
	glVertex3f((-1 / 4.), 0, 0);
	glVertex3f(1 / 4., 0, 0);
	glVertex3f(1 / 4., 1 / 12., 0);
	glVertex3f((-1 / 4.), 1 / 12., 0);
	glEnd();

}

//4괘의 구성요소 중 끊어진 선을 그리는 함수 DrawLine() 
void DrawTwoLine()
{
	glColor3f(0, 0, 0); //검은색

	glBegin(GL_POLYGON);
	glVertex3f((-1 / 4.), 0, 0);
	glVertex3f((-1 / 48.), 0, 0);
	glVertex3f((-1 / 48.), 1 / 12., 0);
	glVertex3f((-1 / 4.), 1 / 12., 0);
	glEnd();

	glTranslatef(1 / 48., 0.0, 0.0); //끊어진 것을 표현하기 위해 1/48.만큼 x좌표 이동

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(1 / 4. + (-1 / 48.), 0, 0);
	glVertex3f(1 / 4. + (-1 / 48.), 1 / 12., 0);
	glVertex3f(0, 1 / 12., 0);
	glEnd();
}
void Display()
{
	//큰원
	glClear(GL_COLOR_BUFFER_BIT);
	DrawCircle(1 / 2., 1.0, 0.0, 0.0, 0); //빨간색 원을 그림
	glPushMatrix();
	glRotated(180, 1, 0, 0);
	glRotated(33.6, 0, 0, 1); //33.6도만큼 회전시켜, 빨간색과 파란색의 경계가 기울어지도록 함
	DrawCircle(1 / 2., 0.0, 0.201, 0.502, 1); //파란색 반원을 그림
	glPopMatrix();
	glPushMatrix();

	//태극무늬
	glPushMatrix();
	glRotated(147, 0, 0, 1);
	glTranslatef(1 / 4., 0, 0);
	DrawCircle(1 / 4., 1.0, 0.0, 0.0, 1); //빨간색 작은 반원을 그림
	glPopMatrix();

	glRotated(-33.6, 0, 0, 1);
	glTranslatef(1 / 4., -0.018, 0);
	DrawCircle(1 / 4., 0.0, 0.201, 0.502, 1); //파란색 작은 반원을 그림
	glPopMatrix();

	//4괘
	glPushMatrix();        //건 
	glRotated((-33.690068), 0, 0, 1);
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);
	glRotated(90, 0, 0, 1);
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawLine();
	glPopMatrix();

	glPushMatrix();        //곤
	glRotated((147.690068), 0, 0, 1);
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);
	glRotated(90, 0, 0, 1);
	DrawTwoLine();
	glTranslated(-1 / 48., (1 / 12.) + (1 / 24.), 0);
	DrawTwoLine();
	glTranslated(-1 / 48., (1 / 12.) + (1 / 24.), 0);
	DrawTwoLine();
	glPopMatrix();

	glPushMatrix();        //감
	glRotated((-147.690068), 0, 0, 1);
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);
	glRotated(90, 0, 0, 1);
	DrawTwoLine();
	glTranslated(-1 / 48., (1 / 12.) + (1 / 24.), 0);
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawTwoLine();
	glPopMatrix();

	glPushMatrix();        //이
	glRotated((33.690068), 0, 0, 1);
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);
	glRotated(90, 0, 0, 1);
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawTwoLine();
	glTranslated((-1 / 48.), (1 / 12.) + (1 / 24.), 0);
	DrawLine();
	glPopMatrix();
	glutSwapBuffers();
}
void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	float ratio = (float)600 / (float)400;
	gluOrtho2D(-ratio, ratio, -1.0, 1.0);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Taegeukgi");
	init();

	glutDisplayFunc(Display);


	//태극기 작도에 사용된 수치들의 실수값
	printf("(1) 1/2. = %f\n", (float)1 / 2.);
	printf("(2) 1/4. = %f\n", (float)1 / 4.);
	printf("(3) 1/12. = %f\n", (float)1 / 12.);
	printf("(4) 1/24. = %f\n", (float)1 / 24.);
	printf("(5) 1/48. = %f\n", (float)1 / 48.);

	glutMainLoop();
	return 0;
}
