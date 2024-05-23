/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �ۼ���: 2023.04.02
// ��  ��: ��ǻ�ͱ׷��Ƚ�
// ��  ��: 20204023
// ��  ��: Ȳ�ٰ�
// ��  ��: Ű���� �̺�Ʈ�� ����Ͽ� ��Ű ������ �׸��ÿ�. (1: ū ��, 2:���� ��, 3:��, enter:��ü ����)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <math.h>

//Display �ݹ� �Լ�
void display() {
	glClearColor(0.9, 0.0, 0.0, 1.0); //������ ���� ��ο� ����������
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//ū ��� ���� ����� �Լ� white_circle()
void white_circle()
{
	glColor3f(1.0, 1.0, 1.0); //���� �� �������

	double radius = 0.35;

	glPushMatrix(); 
	glScalef(2.5, 2.5, 2.5); // ũ�� 2.5��
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

//���� ������ ���� ����� �Լ� red_circle()
void red_circle()
{
	glColor3f(0.9, 0.0, 0.0); //���� �� ����������(������ ����)

	double radius = 0.27;

	glPushMatrix(); 
	glScalef(2.5, 2.5, 2.5);// ũ�� 2.5��
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
	glScalef(3.0, 3.0, 3.0); //ũ�� 3��
	glColor3f(1.0, 1.0, 1.0); //���� �� ���
	glTranslatef(0, 0.05, 0);
	//�ﰢ�� 3���� ���� �������� 5�� ���� ����
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

//Ű���� �̺�Ʈ
void keyboardProcess(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'1':
		white_circle(); //Ű���� 1���� ������ ��� ���� �׷���
		break;
	case'2':
 		red_circle(); //Ű���� 2���� ������ ������ ���� �׷���
		break;
	case'3':
		star(); //Ű���� 3���� ������ ��� ���� �׷���
		break;
	case'\r': //���͸� ������ ��� ������ �ѹ��� �׷���
		white_circle();
		red_circle();
		star();
		break;
	}
}
void init(void)
{
	glClearColor(1.0, 0.0, 0.0, 0.0); //������ ����� ���������� ����
	glClear(GL_COLOR_BUFFER_BIT); //���� ���� ����
}
//reshape �ݹ� �Լ� ȣ��
void reshape(int new_w, int new_h)
{
	glViewport(0, 0, new_w, new_h);
	float WidthFactor = (float)new_w / 250.0;
	float HeightFactor = (float)new_h / 250.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//���� ���� left, right, bottom, top, near, far
	gluOrtho2D(-1.0* WidthFactor, 1.0*WidthFactor, -1.0*HeightFactor, 1.0*HeightFactor);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv); //GLUT ���� �ʱ�ȭ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //���÷��̸�� ���� single  & rgba ����

	glutInitWindowSize(600, 400); //������ â�� ũ�� ����
	glutInitWindowPosition(100, 100); //������ â�� ��ġ ����
	glutCreateWindow("20204023_��Ű"); //������ ����, �̸��� 20204023_��Ű�� ����
	init();

	//display, reshape �ݹ� �Լ� ���
	glutDisplayFunc(display);  
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardProcess); //�̺�Ʈ ó�� ���� ����

	glutMainLoop();
	return 0;
}
