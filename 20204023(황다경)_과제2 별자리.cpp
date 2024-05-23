/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �ۼ���: 2023.04.03
// ��  ��: ��ǻ�ͱ׷��Ƚ�
// ��  ��: 20204023
// ��  ��: Ȳ�ٰ�
// ��  ��: �ﰢ�� �ΰ��� ����Ͽ� �� ���� ��, ���콺 �̺�Ʈ�� ����Ͽ� ���ڸ��� ����
//         1. ���콺 ��Ŭ�� �� Ŭ���� ��ġ�� �� ����(������ ���� ���̿��� ������ �մ� ���� �Բ� ����)
//         2. ���콺 ��Ŭ�� �� ȭ�鿡 �����ϴ� ��� ���� ȸ��(��� ��� �߰��Ͽ� ��Ŭ���� ȸ�� ���� ����)
//         3. ���콺 ��� ��ư Ŭ�� �� ȭ�鿡 �����ϴ� ������ �� ����
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <GL/glut.h>

//���� ���콺 Ŭ�� �� ������ �ﰢ���� ������ǥ x, y�� �����ϴ� ����
float PreX = 0.0f;
float PreY = 0.0f;
float angle = 0.0f;
//������ ���� ������ �����ϴ� ����
int StarNum = 0;
//ȸ�������� �����ϱ� ���� ����
int r_direction = 1;
//������ ���� �����ϴ��� Ȯ��
bool isExist = false;
//���콺 ��� ��ư�� Ŭ���Ǿ������� Ȯ���ϴ� ����
bool isClicked_m = false;
bool isClicked_r = false;
//������ ���� ��ǥ�� �����ϴ� �迭 X_array, Y_array. ���� i��° ���� x��ǥ�� y��ǥ�� ����
GLfloat X_array[100];
GLfloat Y_array[100];
//������ ������ ��ǥ�� �����ϴ� �迭 X_lines, Y_lines
GLfloat X_lines[100];
GLfloat Y_lines[100];

GLfloat RED = 0.0f;
GLfloat GREEN = 0.0f;
GLfloat BLUE = 0.0f;

GLint index = 0;
GLfloat Delta = 0.0f;

void Animation();

//���� �ȷ�Ʈ
unsigned char COLORS[9][3] = {
	//white, cyan, purple, Light Gray, Dark Gray, Dark Red, Dard Green, Dark Blue, Black
	{255,255,255}, {0, 255, 255}, {255, 0, 255}, {192, 192, 192}, {128, 128, 128}, {128, 0, 0},
	{0, 128, 0}, {0, 0, 128}, {0, 0, 0}
};

//timerProcess()�� ȣ��Ǹ� ���� ���ϴ� ���� ����
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

//ȸ�� �ִϸ��̼��� ���� ����ϴ� idle callback �Լ�
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
	glClearColor(0.0, 0.0, 0.0, 0.0); //�ʱ� ȭ���� ���������� ����
	//rotate_Animation()�� ȣ��, ���콺 �̺�Ʈ �߻� �� idle/timer�� ����Ͽ� �ִϸ��̼� ����
	//���콺 ��� ��ư Ȥ�� ������ ��ư�� Ŭ�� �Ǿ��� ��쿡�� ȣ��ǵ��� ����
	if (isClicked_m || isClicked_r)
	{
		Animation();
	}
	
	glutSwapBuffers();
}

//���� �׸��� �Լ� draw_star()
void star(float x, float y)
{
	//�� ���� �ﰢ���� ����Ͽ� ���� ����
	glBegin(GL_TRIANGLES);
	//Ŭ�� ��ġ�� x,y�� �޾� ������ �����ϹǷ� �� �������� x, y�� �������� ���Ͽ� ����
	glVertex2f(x, y);
	glVertex2f(x + 30, y);
	glVertex2f(x + 15, y + 35);

	glBegin(GL_TRIANGLES);
	glVertex2f(x, y + 22.5);
	glVertex2f(x + 30, y + 22.5);
	glVertex2f(x + 15, y - 12.5);

	glEnd();
}

//���� �׸��� �Լ�  draw_line()
void line(float px1, float py1, float px2, float py2) {
	glBegin(GL_LINES);
	//���� �� ������ ��ǥ�� �Է¹޾�, ���� �����Ѵ�.
	glVertex2f(px1, py1);
	glVertex2f(px2, py2);
	glEnd();
}

//ȸ���� �� ��ȭ�� ���� Animation()�Լ�
void Animation(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 1; i < StarNum+1; i++)
	{
		if (i - 1 > 0)
		{
			line(X_lines[i - 1], Y_lines[i - 1], X_lines[i], Y_lines[i]);
		}

		glPushMatrix(); //��ȯ ��ǥ ����
		//���� ������ ���. ���� �̷�� �ﰢ���� �� �������� x,y���� ����� ����
		//translatef�� ����Ͽ� ������Ʈ�� �߽����� �������� �̵����� ȸ���� ������ ��, �ٽ� �߽��� �̵�
		glTranslatef((3 * X_array[i] + 45) / 3.0, (3 * Y_array[i] + 35) / 3.0, 0.0);
		glRotatef(r_direction* angle, 0.0, 0.0, 1.0);
		glTranslatef(-1.0*(3 * X_array[i] + 45) / 3.0, -1.0*(3 * Y_array[i] + 35) / 3.0, 0.0);
		//glColor3f(250.0,0.0, 0.0);
		star(X_array[i], Y_array[i]);
		glPopMatrix(); //��ȯ ��ǥ ȣ��
	}
	//���콺 ��� ��ư�� Ŭ���Ǹ� color_change()ȣ��

	if (isClicked_m)
	{
		color_change();
	}
}
//���콺 Ŭ�� �̺�Ʈ
void mouseFunc(int button, int state, int x, int y) {
	//���콺 ��Ŭ�� ��
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//Ŭ�� ��ġ�� ��ǥ�� �޾� x,y�� ����
		//���콺 Ŭ�� ��ġ click_x, click_y�� �޾� OPENGL ��ǥ��� ��ȯ
		//������ ��ǥ��� OPENGL ��ǥ��� �ݴ��̹Ƿ�, â�� ���̿��� y��ǥ���� ��.
		float click_x = (float)x;
		float click_y = 400 - (float)y;

		click_x = click_x / 600 * 600;
		click_y = click_y / 400 * 600;

		//glutSwapBuffers�� ���� ���۷�, ���� �ĸ� ���۰� �ֱ� ������ glutPostRedisplay()�� ������� ������
		//Ŭ���Ҷ����� ¦����°, Ȧ����° ������ ������ �����ư��鼭 �����
		glutPostRedisplay();
		glutSwapBuffers();

		// Ŭ���� ��ġ�� ���� �׸�
		glColor3f(250.0, 250.0, 0.0);
		star(click_x, click_y);
		StarNum++;

		//isExist=true �� ���, �� ������ ������ ���� ������ ��� ���� ����
		if (isExist) {
			//������ ������ ���� ������ �Ǵ� ��ǥ(PreX, PreY)�� ���� ������ ���� �ﰢ�� ���� (click_x,click_y)�� px1,py1,px2,py2�� �޾� ���� ����
			glColor3f(250.0, 250.0, 0.0);
			line(PreX, PreY, click_x + 10, click_y + 10);
		}

		//isExist�� true�� ����
		isExist = true;
		//PreX�� PreY�� ����Ǵ� ��ǥ�� ����
		PreX = click_x + 10;
		PreY = click_y + 10;

		//�迭�� ���� ���� ��ǥ ����
		X_array[StarNum] = click_x;
		Y_array[StarNum] = click_y;
		X_lines[StarNum] = PreX;
		Y_lines[StarNum] = PreY;
	}
	//���콺 ��Ŭ�� ��
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//isClicked_r�� true�� ����
		isClicked_r = true;
		//r_direction�� -1�� ���Ͽ� ȸ�� ���� ����. ��Ŭ���� �� ������ ȸ�� ������ �����
		r_direction *= -1;
		//idleFunc�� ȣ���Ͽ� ������ ȸ���ϴ� ������ ����
		glutIdleFunc(idleProcess);

	}
	//���콺 ��� ��ư Ŭ�� ��
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		//isClicked_m�� true�� ����
		isClicked_m = true;
		//timerFunc�� ȣ���Ͽ�, ������ ���� ���ϴ� ������ ����
		glutTimerFunc(2000, timerProcess, 1);
	}
}

//OpenGL �ʱ�ȭ �Լ� init()
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 600.0, 0.0, 600.0);
	glLoadIdentity;
}

//�����Լ�
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //���� ���� ����

	//������ ����� 600,400���� ����/������ ���� ��ġ�� 100,100���� ����
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("���ڸ�");
	init();

	glutDisplayFunc(display);
	glutMouseFunc(mouseFunc);

	glutMainLoop();
	return 0;
}