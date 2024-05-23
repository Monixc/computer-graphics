/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �ۼ���: 2023.04.04
// ��  ��: ��ǻ�ͱ׷��Ƚ�
// ��  ��: 20204023
// ��  ��: Ȳ�ٰ�
// ��  ��: �±ر� �׸���
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14

//������, rgb��, �ݿ����θ� �޾� ���� �׸��� �Լ� DrawCircle()
void DrawCircle(float radius, float r, float g, float b, int half)
{
	glColor3f(r, g, b); //rgb���� �޾� �� ����
	glBegin(GL_POLYGON); //�� �׸���
	if (half == 0) //int half�� ���� 0�̸� ���� �׸�
	{
		for (int i = 0; i < 360; i++)
		{
			float angle = i * PI / 180;
			glVertex3f(cos(angle) * radius, sin(angle)*radius, 0);
		}
	}
	else if (half == 1) //half�� ���� 1�̸� �ݿ��� �׸�
	{
		for (int i = 0; i < 180; i++)
		{
			float angle = i * PI / 180;
			glVertex3f(cos(angle) * radius, sin(angle)*radius, 0);
		}
	}
	glEnd();
}

//4���� ������� �� �ϳ��� ���� �׸��� �Լ� DrawLine()
void DrawLine()
{
	glColor3f(0, 0, 0); //������
	glBegin(GL_POLYGON);
	glVertex3f((-1 / 4.), 0, 0);
	glVertex3f(1 / 4., 0, 0);
	glVertex3f(1 / 4., 1 / 12., 0);
	glVertex3f((-1 / 4.), 1 / 12., 0);
	glEnd();

}

//4���� ������� �� ������ ���� �׸��� �Լ� DrawLine() 
void DrawTwoLine()
{
	glColor3f(0, 0, 0); //������

	glBegin(GL_POLYGON);
	glVertex3f((-1 / 4.), 0, 0);
	glVertex3f((-1 / 48.), 0, 0);
	glVertex3f((-1 / 48.), 1 / 12., 0);
	glVertex3f((-1 / 4.), 1 / 12., 0);
	glEnd();

	glTranslatef(1 / 48., 0.0, 0.0); //������ ���� ǥ���ϱ� ���� 1/48.��ŭ x��ǥ �̵�

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(1 / 4. + (-1 / 48.), 0, 0);
	glVertex3f(1 / 4. + (-1 / 48.), 1 / 12., 0);
	glVertex3f(0, 1 / 12., 0);
	glEnd();
}
void Display()
{
	//ū��
	glClear(GL_COLOR_BUFFER_BIT);
	DrawCircle(1 / 2., 1.0, 0.0, 0.0, 0); //������ ���� �׸�
	glPushMatrix();
	glRotated(180, 1, 0, 0);
	glRotated(33.6, 0, 0, 1); //33.6����ŭ ȸ������, �������� �Ķ����� ��谡 ���������� ��
	DrawCircle(1 / 2., 0.0, 0.201, 0.502, 1); //�Ķ��� �ݿ��� �׸�
	glPopMatrix();
	glPushMatrix();

	//�±ع���
	glPushMatrix();
	glRotated(147, 0, 0, 1);
	glTranslatef(1 / 4., 0, 0);
	DrawCircle(1 / 4., 1.0, 0.0, 0.0, 1); //������ ���� �ݿ��� �׸�
	glPopMatrix();

	glRotated(-33.6, 0, 0, 1);
	glTranslatef(1 / 4., -0.018, 0);
	DrawCircle(1 / 4., 0.0, 0.201, 0.502, 1); //�Ķ��� ���� �ݿ��� �׸�
	glPopMatrix();

	//4��
	glPushMatrix();        //�� 
	glRotated((-33.690068), 0, 0, 1);
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);
	glRotated(90, 0, 0, 1);
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawLine();
	glPopMatrix();

	glPushMatrix();        //��
	glRotated((147.690068), 0, 0, 1);
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);
	glRotated(90, 0, 0, 1);
	DrawTwoLine();
	glTranslated(-1 / 48., (1 / 12.) + (1 / 24.), 0);
	DrawTwoLine();
	glTranslated(-1 / 48., (1 / 12.) + (1 / 24.), 0);
	DrawTwoLine();
	glPopMatrix();

	glPushMatrix();        //��
	glRotated((-147.690068), 0, 0, 1);
	glTranslated(((-1 / 2.) + (-1 / 4.)), 0, 0);
	glRotated(90, 0, 0, 1);
	DrawTwoLine();
	glTranslated(-1 / 48., (1 / 12.) + (1 / 24.), 0);
	DrawLine();
	glTranslated(0, (1 / 12.) + (1 / 24.), 0);
	DrawTwoLine();
	glPopMatrix();

	glPushMatrix();        //��
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


	//�±ر� �۵��� ���� ��ġ���� �Ǽ���
	printf("(1) 1/2. = %f\n", (float)1 / 2.);
	printf("(2) 1/4. = %f\n", (float)1 / 4.);
	printf("(3) 1/12. = %f\n", (float)1 / 12.);
	printf("(4) 1/24. = %f\n", (float)1 / 24.);
	printf("(5) 1/48. = %f\n", (float)1 / 48.);

	glutMainLoop();
	return 0;
}
