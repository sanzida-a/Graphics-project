#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>
//#include <iostream>
//using namespace std;
#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

int sph, scl, posx, inc;
double ang;
int drawgrid;
int drawaxes;
double angle;

GLuint makeaTree;
float x, y, z;


struct point
{
	double x, y, z;
};

double cameraLookingX = 0;
double cameraLookingY = 0;
double cameraLookingZ = 0;


double cameraAngle = 275.0;
double cameraRadius = 800;

double cameraX = 300;
double cameraY = 30;
double cameraHeight = 600;

double cameraAngleDelta = -0.0003;

double move_X = 0;
double move_Y = 0;
double move_Z = 0;
double speed = 30;
double ang_speed = 0.5;
int num_texture = -1;
int at = 200;

GLuint ab, bc, cd, xc, de, ef, fg, sky, water, wall, br, br1, sur;



/***************************** Texture Functions *******************************/

int loadBitmapImage(char *filename)
{
	int i, j = 0;
	FILE *l_file;
	unsigned char *l_texture;

	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;

	num_texture++;

	if ((l_file = fopen(filename, "rb")) == NULL)
	{
		printf("efg");
		return (-1);
	}

	fread(&fileheader, sizeof(fileheader), 1, l_file);

	fseek(l_file, sizeof(fileheader), SEEK_SET);
	fread(&infoheader, sizeof(infoheader), 1, l_file);

	l_texture = (byte *)malloc(infoheader.biWidth * infoheader.biHeight * 4);
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
	for (i = 0; i < infoheader.biWidth * infoheader.biHeight; i++)
	{
		fread(&rgb, sizeof(rgb), 1, l_file);

		l_texture[j + 0] = rgb.rgbtRed;
		l_texture[j + 1] = rgb.rgbtGreen;
		l_texture[j + 2] = rgb.rgbtBlue;
		l_texture[j + 3] = 255;
		j += 4;
	}
	fclose(l_file);

	glBindTexture(GL_TEXTURE_2D, num_texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

	free(l_texture);

	return (num_texture);
}

void loadAllImages()
{
	ab = loadBitmapImage("image/grass.bmp");
	sur = loadBitmapImage("image/field.bmp");
	bc = loadBitmapImage("image/grass.bmp");
	cd = loadBitmapImage("image/road.bmp");

	br = loadBitmapImage("image/extend1.bmp");
	br1 = loadBitmapImage("image/extend1.bmp");
	ef = loadBitmapImage("image/extend2.bmp");
	fg = loadBitmapImage("image/6.bmp");
	sky = loadBitmapImage("image/sky.bmp");
	water = loadBitmapImage("image/lake.bmp");
	wall = loadBitmapImage("image/wall.bmp");
}


/****************************** GridLines and Axes ***********************************/




void drawAxes()
{

	glBegin(GL_LINES);
	{
		glColor3f(0, 1.0, 0);
		glVertex3f(1000, 0, 0);
		glVertex3f(-1000, 0, 0);

		glColor3f(0, 0, 1.0);
		glVertex3f(0, -1000, 0);
		glVertex3f(0, 1000, 0);

		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(0, 0, 1000);
		glVertex3f(0, 0, -1000);
	}
	glEnd();

}



void building()
{
	glEnable(GL_TEXTURE_2D);
	{
		glTranslated(-50, 400, 1);     // middle building
		glScaled(2, 1, 1);
		glPushMatrix();
		{

			glTranslated(15, 240, 1);
			glScaled(4, 2, 4);

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);
				glColor3f(1, 1, 1);

				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix(); ///top of middle building big grass hobe
			{
				glBindTexture(GL_TEXTURE_2D, ab);
				glColor3f(1, 1, 1);
				glTranslatef(0, 0, 60);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix(); /// dorkaqr nai
			{
				glBindTexture(GL_TEXTURE_2D, wall);
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();///dorkar nai 2
			{
				glBindTexture(GL_TEXTURE_2D, wall);
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();/// middle build big left side brick hobe
			{
				glBindTexture(GL_TEXTURE_2D, wall);

				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix(); /// middle build right side brick hobe
			{
				glBindTexture(GL_TEXTURE_2D, wall);

				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();



		}
		glPopMatrix();




		glTranslated(60, 0, 0);
		glScaled(1, 1, 4);





		glPushMatrix();
		{

			glTranslated(90, 0, 0);
			glColor3f(1, 1, 1);
			glPushMatrix();
			{
				glTranslated(-250, -60, 0);
				glScaled(.5, 1, 1);


			}
			glPopMatrix();





			//###################left right block







			///tyachra building begin
			//################### right left block


			glTranslated(20, 0, 0);
			glScaled(.7, .7, 1);
			glPushMatrix();
			{


				glPushMatrix();
				{
					glTranslated(-149, -60, 0);
					glScaled(.5, 1, 1.3);



					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, ab);/// grass hobe top

						glColor3f(1, 1, 1);
						glTranslatef(0, 0, 60);
						glBegin(GL_QUADS);
						{
							glTexCoord2f(0, 1);
							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -30, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-30, -54, 0);
						}
						glEnd();

					}
					glPopMatrix();


					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, br);///front side hobe baranda type jinishpotrw glBindTexture(GL_TEXTURE_2D, cd);
						glColor3f(1, 1, 1);
						glTranslatef(30, 0, 0);
						glRotated(20, 0, 0, 1);
						glTranslatef(-40, 0, 0);
						glTranslatef(0, 0, 30);
						glRotated(90, 1, 0, 0);
						glTranslatef(0, 0, 30);
						glBegin(GL_QUADS);   ////fronttttt
						{
							glTexCoord2f(0, 1);
							glVertex3f(-35, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -30, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-35, -30, 0);
						}
						glEnd();

					}
					glPopMatrix();


					glPushMatrix(); ///dorkar nai
					{
						glBindTexture(GL_TEXTURE_2D, cd);
						glColor3f(1, 1, 1);

						glTranslatef(0, 0, 30);
						glRotated(90, 1, 0, 0);
						glTranslatef(0, 0, -30);
						glBegin(GL_QUADS); // backkkkkkkkkkkk
						{
							glTexCoord2f(0, 1);
							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -30, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-30, -30, 0);
						}
						glEnd();

					}
					glPopMatrix();

					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, cd); ///dorkar nai
						glColor3f(1, 1, 1);

						glTranslatef(0, 0, 30);
						glRotated(90, 0, 1, 0);
						glTranslatef(0, 0, 30);
						glBegin(GL_QUADS); // rightttttt
						{
							glTexCoord2f(0, 1);
							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -30, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-30, -30, 0);
						}
						glEnd();
					}
					glPopMatrix();


					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, wall); /// brick hobe

						glColor3f(1, 1, 1);

						glTranslatef(0, 0, 30);
						glRotated(90, 0, 1, 0);
						glTranslatef(0, 0, -30);
						glBegin(GL_QUADS); // leftttttt
						{
							glTexCoord2f(0, 1);
							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -54, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-30, -54, 0);
						}
						glEnd();

					}
					glPopMatrix();



				}
				glPopMatrix();



				//################### right right block

				glPushMatrix();
				{
					glTranslated(-120, -60, 0);
					glScaled(.5, 1, 1.3);


					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, ab);/// grass hobe top
						glColor3f(1, 1, 1);
						glTranslatef(0, 0, 60);
						glBegin(GL_QUADS);
						{
							glTexCoord2f(0, 1);
							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -54, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-30, -30, 0);
						}
						glEnd();

					}
					glPopMatrix();

					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, br);///front hobe

						glColor3f(1, 1, 1);
						glTranslatef(40, -25, 0);
						glRotated(-20, 0, 0, 1);
						glTranslatef(-30, 0, 0);
						glTranslatef(0, 0, 30);
						glRotated(90, 1, 0, 0);
						glTranslatef(0, 0, 30);
						glBegin(GL_QUADS);   ////fronttttt
						{
							glTexCoord2f(0, 1);

							glVertex3f(-35, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -30, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-35, -30, 0);
						}
						glEnd();

					}
					glPopMatrix();


					glPushMatrix();

					glBindTexture(GL_TEXTURE_2D, wall);///dorkar nai bac
					{
						glColor3f(1, 1, 1);

						glTranslatef(0, 0, 30);
						glRotated(90, 1, 0, 0);
						glTranslatef(0, 0, -30);
						glBegin(GL_QUADS); // backkkkkkkkkkkk
						{
							glTexCoord2f(0, 1);

							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -30, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-30, -30, 0);
						}
						glEnd();

					}
					glPopMatrix();


					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, wall);/// brick hobe

						glColor3f(1, 1, 1);

						glTranslatef(0, 0, 30);
						glRotated(90, 0, 1, 0);
						glTranslatef(0, 0, 30);
						glBegin(GL_QUADS); // rightttttt
						{
							glTexCoord2f(0, 1);
							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 1);
							glVertex3f(30, 30, 0);
							glTexCoord2f(0, 1);
							glVertex3f(30, -54, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-30, -54, 0);
						}
						glEnd();
					}
					glPopMatrix();


					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, cd);///dorkar nai

						glColor3f(1, 1, 1);

						glTranslatef(0, 0, 30);
						glRotated(90, 0, 1, 0);
						glTranslatef(0, 0, -30);
						glBegin(GL_QUADS); // leftttttt
						{
							glTexCoord2f(0, 1);
							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -30, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-30, -30, 0);
						}
						glEnd();

					}
					glPopMatrix();


				}
				glPopMatrix();


			}
			glPopMatrix();
		}
		glPopMatrix();

		///tyachra building end



		glPushMatrix();
		{
			glTranslated(15.7, 5, 0);
			glScaled(.71, 2, 1.3);

			glPushMatrix();
			{
				glColor3f(1, 1, 1);
				glBegin(GL_QUADS);
				{

					/* glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);*/
				}
				glEnd();

			}
			glPopMatrix();

			///front right

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, ab);/// grass hobe top right

				glColor3f(1, 1, 1);
				glTranslatef(0, 0, 60);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, br);
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);   ////fronttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);

				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS); // backkkkkkkkkkkk
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);///right brick
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS); // rightttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);

				}
				glEnd();
			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);/// left brick hobe

				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS); // leftttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


		}
		glPopMatrix();

		///tyachra building with back end




		///2nd left tyachra

		///tyachra building begin
		//################### right left block

		glPushMatrix();
		{
			glTranslated(-20, 0, 0);
			glScaled(.7, .7, 1);
			glPushMatrix();
			{


				glPushMatrix();
				{
					glTranslated(-149, -60, 0);
					glScaled(.5, 1, 1.3);


					/// top
					glPushMatrix();
					{

						glBindTexture(GL_TEXTURE_2D, ab); ///top grass
						glColor3f(1, 1, 1);
						glTranslatef(0, 0, 60);
						glBegin(GL_QUADS);
						{
							glTexCoord2f(0, 1);

							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -30, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-30, -54, 0);
						}
						glEnd();

					}
					glPopMatrix();


					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, br); /// front baranda type jinishpotrw

						glColor3f(1, 1, 1);
						glTranslatef(30, 0, 0);
						glRotated(20, 0, 0, 1);
						glTranslatef(-40, 0, 0);
						glTranslatef(0, 0, 30);
						glRotated(90, 1, 0, 0);
						glTranslatef(0, 0, 30);
						glBegin(GL_QUADS);   ////fronttttt
						{
							glTexCoord2f(0, 1);

							glVertex3f(-35, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0); glTexCoord2f(1, 0);
							glVertex3f(30, -30, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-35, -30, 0);
						}
						glEnd();

					}
					glPopMatrix();

					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, wall);
						glColor3f(1, 1, 1);

						glTranslatef(0, 0, 30);
						glRotated(90, 1, 0, 0);
						glTranslatef(0, 0, -30);
						glBegin(GL_QUADS); // backkkkkkkkkkkk
						{
							glTexCoord2f(0, 1);

							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -30, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-30, -30, 0);
						}
						glEnd();

					}
					glPopMatrix();


					glPushMatrix();
					{
						glColor3f(1, 1, 1);

						glTranslatef(0, 0, 30);
						glRotated(90, 0, 1, 0);
						glTranslatef(0, 0, 30);
						glBegin(GL_QUADS); // rightttttt
						{

							glVertex3f(-30, 30, 0);
							glVertex3f(30, 30, 0);
							glVertex3f(30, -30, 0);
							glVertex3f(-30, -30, 0);
						}
						glEnd();
					}
					glPopMatrix();


					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, wall);/// left brick hobe
						glColor3f(1, 1, 1);

						glTranslatef(0, 0, 30);
						glRotated(90, 0, 1, 0);
						glTranslatef(0, 0, -30);
						glBegin(GL_QUADS); // leftttttt
						{
							glTexCoord2f(0, 1);

							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -54, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-30, -54, 0);
						}
						glEnd();

					}
					glPopMatrix();


				}
				glPopMatrix();



				//################### right right block

				glPushMatrix();
				{
					glTranslated(-120, -60, 0);
					glScaled(.5, 1, 1.3);

					/// top

					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, ab);
						glColor3f(1, 1, 1);
						glTranslatef(0, 0, 60);
						glBegin(GL_QUADS);
						{
							glTexCoord2f(0, 1);

							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -54, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-30, -30, 0);
						}
						glEnd();

					}
					glPopMatrix();

					glPushMatrix();
					{

						glBindTexture(GL_TEXTURE_2D, br);

						glColor3f(1, 1, 1);
						glTranslatef(40, -25, 0);
						glRotated(-20, 0, 0, 1);
						glTranslatef(-30, 0, 0);
						glTranslatef(0, 0, 30);
						glRotated(90, 1, 0, 0);
						glTranslatef(0, 0, 30);
						glBegin(GL_QUADS);   ////fronttttt
						{
							glTexCoord2f(0, 1);

							glVertex3f(-35, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -30, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-35, -30, 0);
						}
						glEnd();

					}
					glPopMatrix();


					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, wall);
						glColor3f(1, 1, 1);

						glTranslatef(0, 0, 30);
						glRotated(90, 1, 0, 0);
						glTranslatef(0, 0, -30);
						glBegin(GL_QUADS); // backkkkkkkkkkkk
						{
							glTexCoord2f(0, 1);

							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);
							glVertex3f(30, -30, 0);
							glTexCoord2f(1, 1);
							glVertex3f(-30, -30, 0);
						}
						glEnd();

					}
					glPopMatrix();


					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, wall); /// right brick hobe
						glColor3f(1, 1, 1);

						glTranslatef(0, 0, 30);
						glRotated(90, 0, 1, 0);
						glTranslatef(0, 0, 30);
						glBegin(GL_QUADS); // rightttttt
						{
							glTexCoord2f(0, 1);

							glVertex3f(-30, 30, 0);
							glTexCoord2f(0, 0);
							glVertex3f(30, 30, 0);
							glTexCoord2f(1, 0);

							glVertex3f(30, -54, 0);
							glTexCoord2f(1, 1);

							glVertex3f(-30, -54, 0);
						}
						glEnd();
					}
					glPopMatrix();


					glPushMatrix();
					{
						glColor3f(1, 1, 1);

						glTranslatef(0, 0, 30);
						glRotated(90, 0, 1, 0);
						glTranslatef(0, 0, -30);
						glBegin(GL_QUADS); // leftttttt
						{

							glVertex3f(-30, 30, 0);
							glVertex3f(30, 30, 0);
							glVertex3f(30, -30, 0);
							glVertex3f(-30, -30, 0);
						}
						glEnd();

					}
					glPopMatrix();



				}
				glPopMatrix();




			}
			glPopMatrix();
		}
		glPopMatrix();

		///tyachra building end



		glPushMatrix();
		{
			glTranslated(-113.7, 10, 0);
			glScaled(.71, 2, 1.3);
			// glRotated(0,0,0,1);


			glPushMatrix();
			{
				glColor3f(1, 1, 1);
				glBegin(GL_QUADS);
				{

					/* glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);*/
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{

				glBindTexture(GL_TEXTURE_2D, ab);/// top grass hobe
				glColor3f(1, 1, 1);
				glTranslatef(0, 0, 60);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);   ////fronttttt
				{

					glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS); // backkkkkkkkkkkk
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall); ///bric hob
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS); // rightttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);

				}
				glEnd();
			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall); /// brick hobe
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS); // leftttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();



		}
		glPopMatrix();

		///2nd  tyachra building with back end

		///middle bump 1

		glPushMatrix();
		{


			glTranslated(-40, 90, 0);
			glScaled(.71, 2, 1.3);


			glPushMatrix();
			{
				glColor3f(1, 1, 1);


			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, ab);/// top grass hobe
				glColor3f(1, 1, 1);
				glTranslatef(0, 0, 60);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, br);/// baranda hobe
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);   ////fronttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS); // backkkkkkkkkkkk
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall); /// brick hobr
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS); // rightttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();
			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS); // leftttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


		}
		glPopMatrix();


		///middle bump 2
		glPushMatrix();
		{
			glTranslated(-50.5, -1, 0);
			glScaled(.37, 1, 1.3);


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, ab);/// top grass ho9be

				glColor3f(1, 1, 1);
				glTranslatef(0, 0, 60);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -54, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, br); /// baranda hobe

				glColor3f(1, 1, 1);
				glTranslatef(40, -25, 0);
				glRotated(-20, 0, 0, 1);
				glTranslatef(-30, 0, 0);
				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);   ////fronttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-35, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-35, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS); // backkkkkkkkkkkk
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall); /// bric hobe
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS); // rightttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -54, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -54, 0);
				}
				glEnd();
			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);/// brick hobe
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS); // leftttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();



		}
		glPopMatrix();




		///left side extend
		glPushMatrix();
		{
			glTranslated(-140, 60, 0);
			glScaled(.71, 2, 1.3);


			glPushMatrix();
			{
				glColor3f(1, 1, 1);


			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, ab); /// top grass

				glColor3f(1, 1, 1);
				glTranslatef(0, 0, 60);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, br); /// baranda hobe
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);   ////fronttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS); // backkkkkkkkkkkk
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);///brick hobe
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS); // rightttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();
			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);/// bric hobe
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS); // leftttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


		}
		glPopMatrix();


		///right side extend

		glPushMatrix();
		{
			glTranslated(49, 60, 0);
			glScaled(.71, 2, 1.3);

			glPushMatrix();
			{
				glColor3f(1, 1, 1);


			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, ab);/// top grass
				glColor3f(1, 1, 1);
				glTranslatef(0, 0, 60);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, br); /// baranda hobe
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);

				glRotated(90, 1, 0, 0);

				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);   ////fronttttt
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0); glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0); glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0); glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS); // backkkkkkkkkkkk
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall); /// brick hiobe
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS); // rightttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0); glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0); glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0); glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();
			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall); /// bri hobr
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS); // leftttttt
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);

					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);

					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);

					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


		}


	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}




void plane()
{

	glEnable(GL_TEXTURE_2D);
	{
		glPushMatrix();
		{

			glTranslated(15, 240, 1);
			glScaled(4, 4, 8);


			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, ab); /// /// top may be
				glColor3f(1, 1, 1);

				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, ab); ///dorkar nai
				glColor3f(1, 1, 1);
				glTranslatef(0, 0, 60);
				glBegin(GL_QUADS);
				{

					glTexCoord2f(0, 1);


					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, br1); /// front ekhane aktaa notun type er baranda lagbe
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall);/// back panel
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{

				glBindTexture(GL_TEXTURE_2D, wall); /// lest brick hobe
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);
				{

					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, wall); /// brick
				glColor3f(1, 1, 1);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);

					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 1);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();



		}
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);

}



void road()
{


	glEnable(GL_TEXTURE_2D);
	{
		//glBindTexture(GL_TEXTURE_2D, ab);
		///road right
		glTranslated(370, -900, 0);
		//glScaled(1.2, 2, 1);
		glPushMatrix(); {
			glBindTexture(GL_TEXTURE_2D, cd);

			glColor3f(1, 1, 1);
			GLUquadricObj *obj = gluNewQuadric();
			gluQuadricTexture(obj, GL_TRUE);

			glTranslated(0, -300, 0);
			//glColor3f(1, .5, 0);
			glScaled(2.3, 70, 10);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex3f(-30, 30, 0);
				glTexCoord2f(0, 0);
				glVertex3f(30, 30, 0);
				glTexCoord2f(1, 0);
				glVertex3f(30, -30, 0);
				glTexCoord2f(1, 1);
				glVertex3f(-30, -30, 0);
			}
			glEnd();


		} glPopMatrix();


		/// road green bump

		glTranslated(90, -900, 0);
		//glScaled(.6, 2, 1);
		glPushMatrix(); {
			glBindTexture(GL_TEXTURE_2D, bc);
			glTranslated(27, 680, 0);
			glColor3f(1, 1, 1);
			glScaled(1.5, 72, 10);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex3f(-30, 30, 0);
				glTexCoord2f(1, 0);
				glVertex3f(30, 30, 0);
				glTexCoord2f(0, 0);
				glVertex3f(30, -30, 0);
				glTexCoord2f(1, 1);
				glVertex3f(-30, -30, 0);
			}
			glEnd();

		} glPopMatrix();

		///main road

		glPushMatrix(); {
			glTranslated(180, -100, 0);
			//glScaled(.6,4,1);
			glPushMatrix(); {
				glBindTexture(GL_TEXTURE_2D, cd);
				glTranslated(15, 850, 0);
				glColor3f(1, 1, 1);
				glScaled(4, 75, 10);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			} glPopMatrix();
		}
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


}


void road1()
{

	///road right
	glTranslated(370, -900, 0);
	//glScaled(1.2, 2, 1);
	glPushMatrix(); {
		glEnable(GL_TEXTURE_2D);
		{

			glBindTexture(GL_TEXTURE_2D, cd);
			glTranslated(0, 184, 0);
			glColor3f(1, 1, 1);
			glScaled(2.3, 55, 10);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex3f(-30, 30, 0);
				glTexCoord2f(0, 0);
				glVertex3f(30, 30, 0);
				glTexCoord2f(1, 0);
				glVertex3f(30, -30, 0);
				glTexCoord2f(1, 1);
				glVertex3f(-30, -30, 0);
			}
			glEnd();

		} glPopMatrix();


		/// road green bump

		glTranslated(90, -900, 0);
		//glScaled(.6, 2, 1);
		glPushMatrix(); {

			glBindTexture(GL_TEXTURE_2D, bc);
			glTranslated(27, 950, 0);
			glColor3f(1, 1, 1);
			glScaled(1.5, 58.9, 10);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex3f(-30, 30, 0);
				glTexCoord2f(1, 0);
				glVertex3f(30, 30, 0);
				glTexCoord2f(0, 0);
				glVertex3f(30, -30, 0);
				glTexCoord2f(1, 1);
				glVertex3f(-30, -30, 0);
			}
			glEnd();

		} glPopMatrix();

		///main road

		glPushMatrix(); {
			glTranslated(180, -100, 0);
			//glScaled(.6,4,1);
			glPushMatrix(); {
				glBindTexture(GL_TEXTURE_2D, cd);
				glTranslated(15, 700, 0);
				glColor3f(1, 1, 1);
				glScaled(4, 70, 10);
				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);
					glVertex3f(-30, 30, 0);
					glTexCoord2f(0, 0);
					glVertex3f(30, 30, 0);
					glTexCoord2f(1, 0);
					glVertex3f(30, -30, 0);
					glTexCoord2f(1, 1);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			} glPopMatrix();
		}
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);

}


void stairs()
{
	int x = 0, i;
	float y = 0, z = 0;


	for (i = 0; i < 10; i++)
	{
		y = y + .1;
		x = x + 30;
		z = z + .05;

		glPushMatrix();
		{
			glTranslated(-30, -1100 - x, .2);
			glScalef(2.5 + y, .6, .05 + z);


			glPushMatrix();
			{
				glColor3f(0, 1, 0);

				glBegin(GL_QUADS);
				{

					glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glColor3f(.95, .93, .8);
				glTranslatef(0, 0, 60);
				glBegin(GL_QUADS);
				{

					glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glColor3f(.95, .93, .8);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);
				{

					glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glColor3f(.55, .53, .4);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS);
				{

					glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{
				glColor3f(.95, .93, .8);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);
				{

					glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{

				glColor3f(.95, .93, .8);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS);
				{

					glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

		}
		glPopMatrix();
	}

}


void front_st()
{
	int x = 0, i;
	float y = 0, z = 0;


	for (i = 0; i < 10; i++)
	{
		x = x + 30;
		z = z + .1;

		glPushMatrix();
		{
			glTranslated(-30, -1100 - x, .2);
			glScalef(2.7, .5, .03 + z);


			glPushMatrix();
			{
				glColor3f(0, 1, 0);

				glBegin(GL_QUADS);
				{

					glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glColor3f(.95, .93, .8);
				glTranslatef(0, 0, 60);
				glBegin(GL_QUADS);
				{

					glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glColor3f(.95, .93, .8);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);
				{

					glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{
				glColor3f(.55, .53, .4);

				glTranslatef(0, 0, 30);
				glRotated(90, 1, 0, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS);
				{

					glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();


			glPushMatrix();
			{
				glColor3f(.95, .93, .8);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, 30);
				glBegin(GL_QUADS);
				{

					glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

			glPushMatrix();
			{

				glColor3f(.95, .93, .8);

				glTranslatef(0, 0, 30);
				glRotated(90, 0, 1, 0);
				glTranslatef(0, 0, -30);
				glBegin(GL_QUADS);
				{

					glVertex3f(-30, 30, 0);
					glVertex3f(30, 30, 0);
					glVertex3f(30, -30, 0);
					glVertex3f(-30, -30, 0);
				}
				glEnd();

			}
			glPopMatrix();

		}
		glPopMatrix();
	}

}
void stair_back()
{
	glTranslated(150, -1550, 0);
	glScalef(5.5, 4.5, 1.5);



	glPushMatrix();
	{
		glColor3f(0, .7, .3);

		glBegin(GL_QUADS);
		{
			glVertex3f(-30, 30, 0);
			glVertex3f(30, 30, 0);
			glVertex3f(30, -30, 0);
			glVertex3f(-30, -30, 0);
		}
		glEnd();

	}
	glPopMatrix();


	glPushMatrix();
	{
		glColor3f(0, .7, .3);
		glTranslatef(0, 0, 60);
		glBegin(GL_QUADS);
		{


			glVertex3f(-30, 30, 0);
			glVertex3f(30, 30, 0);
			glVertex3f(30, -30, 0);
			glVertex3f(-30, -30, 0);
		}
		glEnd();

	}
	glPopMatrix();



	glPushMatrix();
	{
		glColor3f(.95, .93, .8);

		glTranslatef(0, 0, 30);
		glRotated(90, 1, 0, 0);
		glTranslatef(0, 0, 30);
		glBegin(GL_QUADS);
		{

			glVertex3f(-30, 30, 0);
			glVertex3f(30, 30, 0);
			glVertex3f(30, -30, 0);
			glVertex3f(-30, -30, 0);
		}
		glEnd();

	}
	glPopMatrix();


	glPushMatrix();
	{
		glColor3f(.95, .93, .8);

		glTranslatef(0, 0, 30);
		glRotated(90, 1, 0, 0);
		glTranslatef(0, 0, -30);
		glBegin(GL_QUADS);
		{

			glVertex3f(-30, 30, 0);
			glVertex3f(30, 30, 0);
			glVertex3f(30, -30, 0);
			glVertex3f(-30, -30, 0);
		}
		glEnd();

	}
	glPopMatrix();


	glPushMatrix();
	{
		glColor3f(.95, .93, .8);

		glTranslatef(0, 0, 30);
		glRotated(90, 0, 1, 0);
		glTranslatef(0, 0, 30);
		glBegin(GL_QUADS);
		{

			glVertex3f(-30, 30, 0);
			glVertex3f(30, 30, 0);
			glVertex3f(30, -30, 0);
			glVertex3f(-30, -30, 0);
		}
		glEnd();

	}
	glPopMatrix();


	glPushMatrix();
	{
		glColor3f(.95, .93, .8);

		glTranslatef(0, 0, 30);
		glRotated(90, 0, 1, 0);
		glTranslatef(0, 0, -30);
		glBegin(GL_QUADS);
		{

			glVertex3f(-30, 30, 0);
			glVertex3f(30, 30, 0);
			glVertex3f(30, -30, 0);
			glVertex3f(-30, -30, 0);
		}
		glEnd();

	}
	glPopMatrix();

	////////////////////////////////////////////////////// left side done


	glTranslated(-60, 0, 0);
	glScalef(1, 1, .75);
	glPushMatrix();
	{
		glColor3f(.95, .93, .8);

		glBegin(GL_QUADS);
		{
			glVertex3f(-30, 30, 0);
			glVertex3f(30, 30, 0);
			glVertex3f(30, -30, 0);
			glVertex3f(-30, -30, 0);
		}
		glEnd();

	}
	glPopMatrix();


	glPushMatrix();
	{
		glColor3f(0, .6, .3);
		glTranslatef(0, 0, 60);
		glBegin(GL_QUADS);
		{

			glVertex3f(-30, 30, 0);
			glVertex3f(30, 30, 0);
			glVertex3f(30, -30, 0);
			glVertex3f(-30, -30, 0);
		}
		glEnd();

	}
	glPopMatrix();


	glPushMatrix();
	{
		glColor3f(.95, .93, .8);

		glTranslatef(0, 0, 30);
		glRotated(90, 1, 0, 0);
		glTranslatef(0, 0, 30);
		glBegin(GL_QUADS);
		{

			glVertex3f(-30, 30, 0);
			glVertex3f(30, 30, 0);
			glVertex3f(30, -30, 0);
			glVertex3f(-30, -30, 0);
		}
		glEnd();

	}
	glPopMatrix();


	glPushMatrix();
	{
		glColor3f(.95, .93, .8);

		glTranslatef(0, 0, 30);
		glRotated(90, 1, 0, 0);
		glTranslatef(0, 0, -30);
		glBegin(GL_QUADS);
		{

			glVertex3f(-30, 30, 0);
			glVertex3f(30, 30, 0);
			glVertex3f(30, -30, 0);
			glVertex3f(-30, -30, 0);
		}
		glEnd();

	}
	glPopMatrix();


	glPushMatrix();
	{
		glColor3f(.95, .93, .8);

		glTranslatef(0, 0, 30);
		glRotated(90, 0, 1, 0);
		glTranslatef(0, 0, 30);
		glBegin(GL_QUADS);
		{

			glVertex3f(-30, 30, 0);
			glVertex3f(30, 30, 0);
			glVertex3f(30, -30, 0);
			glVertex3f(-30, -30, 0);
		}
		glEnd();

	}
	glPopMatrix();


	glPushMatrix();
	{
		glColor3f(.95, .93, .8);

		glTranslatef(0, 0, 30);
		glRotated(90, 0, 1, 0);
		glTranslatef(0, 0, -30);
		glBegin(GL_QUADS);
		{

			glVertex3f(-30, 30, 0);
			glVertex3f(30, 30, 0);
			glVertex3f(30, -30, 0);
			glVertex3f(-30, -30, 0);
		}
		glEnd();

	}
	glPopMatrix();


	///////////////////////////////swimming pool

	glTranslated(0, 0, 64);
	glScalef(.6, .88, .2);
	glPushMatrix();
	{
		glColor3f(0, .3, 1);
		glEnable(GL_TEXTURE_2D);
		{

			glBindTexture(GL_TEXTURE_2D, water);
			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex3f(-30, 30, 0);
				glTexCoord2f(0, 0);
				glVertex3f(30, 30, 0);
				glTexCoord2f(1, 0);
				glVertex3f(30, -30, 0);
				glTexCoord2f(1, 1);
				glVertex3f(-30, -30, 0);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

	}
	glPopMatrix();

}


void canteen()
{
	glTranslated(250, -1350, 0);
	glScalef(1.6, 3.7, .7);


	glEnable(GL_TEXTURE_2D);
	{


		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, wall);
			glColor3f(0, .7, .3);

			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex3f(-30, 30, 0);
				glTexCoord2f(0, 0);
				glVertex3f(30, 30, 0);
				glTexCoord2f(1, 0);
				glVertex3f(30, -30, 0);
				glTexCoord2f(1, 1);
				glVertex3f(-30, -30, 0);
			}
			glEnd();

		}
		glPopMatrix();


		glPushMatrix();
		{
			// glBindTexture(GL_TEXTURE_2D,wall);
			glColor3f(0, .7, .3);
			glTranslatef(0, 0, 60);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);



				glVertex3f(-30, 30, 0);
				glTexCoord2f(0, 0);
				glVertex3f(30, 30, 0);
				glTexCoord2f(1, 0);
				glVertex3f(30, -30, 0);
				glTexCoord2f(1, 1);
				glVertex3f(-30, -30, 0);
			}
			glEnd();

		}
		glPopMatrix();



		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, wall);
			glColor3f(.95, .93, .8);

			glTranslatef(0, 0, 30);
			glRotated(90, 1, 0, 0);
			glTranslatef(0, 0, 30);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);


				glVertex3f(-30, 30, 0);
				glTexCoord2f(0, 0);

				glVertex3f(30, 30, 0);
				glTexCoord2f(1, 0);

				glVertex3f(30, -30, 0);
				glTexCoord2f(1, 1);

				glVertex3f(-30, -30, 0);
			}
			glEnd();

		}
		glPopMatrix();


		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, wall);
			glColor3f(.95, .93, .8);

			glTranslatef(0, 0, 30);
			glRotated(90, 1, 0, 0);
			glTranslatef(0, 0, -30);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);


				glVertex3f(-30, 30, 0);
				glTexCoord2f(0, 0);

				glVertex3f(30, 30, 0);
				glTexCoord2f(1, 0);

				glVertex3f(30, -30, 0);
				glTexCoord2f(1, 1);

				glVertex3f(-30, -30, 0);
			}
			glEnd();

		}
		glPopMatrix();


		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, wall);
			glColor3f(.95, .93, .8);

			glTranslatef(0, 0, 30);
			glRotated(90, 0, 1, 0);
			glTranslatef(0, 0, 30);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);

				glVertex3f(-30, 30, 0);
				glTexCoord2f(0, 1);
				glVertex3f(30, 30, 0);
				glTexCoord2f(1, 0);
				glVertex3f(30, -30, 0);
				glTexCoord2f(1, 1);
				glVertex3f(-30, -30, 0);
			}
			glEnd();

		}
		glPopMatrix();


		glPushMatrix();
		{
			glColor3f(.95, .93, .8);

			glTranslatef(0, 0, 30);
			glRotated(90, 0, 1, 0);
			glTranslatef(0, 0, -30);
			glBegin(GL_QUADS);
			{

				glVertex3f(-30, 30, 0);
				glVertex3f(30, 30, 0);
				glVertex3f(30, -30, 0);
				glVertex3f(-30, -30, 0);
			}
			glEnd();

		}
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);

}
void lake()
{
	glEnable(GL_TEXTURE_2D);
	{
		glBindTexture(GL_TEXTURE_2D, water);

		glPushMatrix(); {
			glColor3f(1, 1, 1);

			glTranslated(-605, -1200, 0);
			glScaled(4.3, 70, 10);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex3f(-30, 30, 0);
				glTexCoord2f(0, 0);
				glVertex3f(30, 30, 0);
				glTexCoord2f(1, 0);
				glVertex3f(30, 20, 0);
				glTexCoord2f(1, 1);
				glVertex3f(-30, 20, 0);
			}
			glEnd();
		} glPopMatrix();
		glPushMatrix(); {
			glTranslated(-605, -1900, 0);
			glScaled(4.3, 70, 10);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex3f(-30, 30, 0);
				glTexCoord2f(0, 0);
				glVertex3f(30, 30, 0);
				glTexCoord2f(1, 0);
				glVertex3f(30, 20, 0);
				glTexCoord2f(1, 1);
				glVertex3f(-30, 20, 0);
			}
			glEnd();

		} glPopMatrix();

		glPushMatrix(); {
			glTranslated(-605, -2600, 0);
			glScaled(4.3, 70, 10);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex3f(-30, 30, 0);
				glTexCoord2f(0, 0);
				glVertex3f(30, 30, 0);
				glTexCoord2f(1, 0);
				glVertex3f(30, 20, 0);
				glTexCoord2f(1, 1);
				glVertex3f(-30, 20, 0);
			}
			glEnd();

		} glPopMatrix();

		glPushMatrix(); {
			glTranslated(-605, -3300, 0);
			glScaled(4.3, 70, 10);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex3f(-30, 30, 0);
				glTexCoord2f(0, 0);
				glVertex3f(30, 30, 0);
				glTexCoord2f(1, 0);
				glVertex3f(30, 20, 0);
				glTexCoord2f(1, 1);
				glVertex3f(-30, 20, 0);
			}
			glEnd();

		} glPopMatrix();
		}
		glDisable(GL_TEXTURE_2D);

}

void trees()
{
	glPushMatrix();
	{

		glEnable(GL_TEXTURE_2D);
		{
			glBindTexture(GL_TEXTURE_2D, ab);

			glPushMatrix();
			{
				glTranslated(670, -600, 0);
				glColor3f(1, 0, 5);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				glTranslated(0, 0, 35);
				gluCylinder(obj, 5, 5, 100, 100, 100);
				glTranslated(0, 0, 100);
				glColor3f(1, 1, 0);
				gluCylinder(obj, 45, 0, 50, 100, 100);


				glPushMatrix(); {
					glTranslated(0, 0, 40);
					glColor3f(0, 1, 1);
					gluCylinder(obj, 40, 0, 50, 100, 100);
				}
				glPopMatrix();


				glPushMatrix(); {
					glTranslated(0, 0, 80);
					glColor3f(0, 1, 1);
					gluCylinder(obj, 35, 0, 50, 100, 100);
				}
				glPopMatrix();

				glPushMatrix(); {
					glTranslated(0, 0, 80);
					glColor3f(0, .8, .6);
					gluCylinder(obj, 30, 0, 50, 100, 100);
				}
				glPopMatrix();


			}
			glPopMatrix();


		}
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();
}


void umbrella()
{

	// glBindTexture(GL_TEXTURE_2D, sea);

	glPushMatrix();
	{
		glTranslated(900, -500, 0);
		glColor3f(.6, .3, .3);
		GLUquadricObj *obj = gluNewQuadric();
		gluQuadricTexture(obj, GL_TRUE);
		gluCylinder(obj, 4, 4, 90, 100, 100);
		glTranslated(0, 0, 80);
		glColor3f(.5, .5, 1);
		gluCylinder(obj, 35, 0, 30, 100, 100);

	}
	glPopMatrix();

}
void display()
{
	//codes for Models, Camera

	//clear the display
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);    //color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        //clear buffers to preset values

															   /***************************
															   / set-up camera (view) here
															   ****************************/
															   //load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);        //specify which matrix is the current matrix

									   //initialize the matrix
	glLoadIdentity();                //replace the current matrix with the identity matrix [Diagonals have 1, others have 0]

									 //now give three info
									 //1. where is the camera (viewer)?
									 //2. where is the camera looking?
									 //3. Which direction is the camera's UP direction?

	gluLookAt(at * cos(cameraAngle), at * sin(cameraAngle), cameraHeight, 0, 0, 0, 0, 0, 1);
	//gluLookAt(cameraX, cameraY, cameraHeight, cameraLookingX, cameraLookingY, cameraLookingZ, 0, 0, 1);
	//gluLookAt(cameraRadius * sin(cameraAngle), -cameraRadius * cos(cameraAngle), cameraHeight, cameraLookingX, cameraLookingY, cameraLookingZ, 0, 0, 1);


	glMatrixMode(GL_MODELVIEW);


	/**************************************************
	/ Grid and axes Lines(You can remove them if u want)
	***************************************************/



	/****************************
	/ Add your objects from here
	****************************/
	glTranslated(0, 900, 0);

	///////////////canteen


	glPushMatrix();
	{
		glTranslated(-720, 600, 0);
		canteen();
		glScalef(.6, .2, 1);
		glTranslated(-250, 2150, 0);

		canteen();

	}
	glPopMatrix();

	/// tree
	glPushMatrix();
	{
		glTranslated(80, -800, 0);
		trees();
		glTranslated(0, 800, 0);
		trees();
		glTranslated(0, 600, 0);
		trees();
		glTranslated(0, 400, 0);
		trees();
		glTranslated(0, 400, 0);
		trees();

	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(-170, 1750, 0);
		trees();
		glTranslated(-300, 0, 0);
		trees();
		glTranslated(-340, 0, 0);
		trees();

	}
	glPopMatrix();

	////////////////////umbrella

	glPushMatrix();
	{
		glTranslated(-1410, -70, 0);
		umbrella();
		glTranslated(0, 300, 0);
		umbrella();
		glTranslated(60, -200, 0);
		umbrella();
		glTranslated(-30, 130, 0);
		umbrella();
	}
	glPopMatrix();



	///sphere;

	glPushMatrix();
	{

		glEnable(GL_TEXTURE_2D);
		{
			glBindTexture(GL_TEXTURE_2D, sky);

			glPushMatrix();
			{
				glColor3f(1, 1, 1);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				glTranslated(300, 300, 1750);
				glRotated(180, 0, 0, 1);
				gluSphere(obj, 3000, 100, 100);

			}
			glPopMatrix();





		}
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();


	//////back building behind stair
	glPushMatrix();
	{
		stair_back();
	}
	glPopMatrix();



	///plane calling
	//glColor3f(1,1,1);
	// drawSphere(1000);


	glPushMatrix();
	{
		glScalef(1.6, 1.2, 1);
		glTranslated(50, 170, 0);
		glPushMatrix();
		{
			//glRotated(90,1,0,0);

			glTranslated(-58, 0, 0);
			glScaled(2.5, .5, 1);
			plane();

		}
		glPopMatrix();


		glPushMatrix();
		{
			//glRotated(90,1,0,0);

			glTranslated(-58, 220, 0);
			glScaled(2.5, .5, 1);
			plane();

		}
		glPopMatrix();



		glPushMatrix();
		{

			glTranslated(0, -400, 0);
			glScaled(1, 1, 2);
			building();
		}
		glPopMatrix();

		glPushMatrix();
		{

			glTranslated(0, 900, 0);
			glRotated(180, 0, 0, 1);
			glScaled(1.2, 1.1, 2);
			building();
		}
		glPopMatrix();
	}
	glPopMatrix();


	glPushMatrix();
	{

		glScalef(1.3, 1, 2);
		glTranslated(120, 2030, 0);
		glColor3f(1, 1, 0);

		front_st();
	}
	glPopMatrix();

	glPushMatrix();
	{

		glTranslated(0, 300, 0);
		glScaled(1.2, 1.3, 1);
		lake();
	}
	glPopMatrix();


	glPushMatrix();
	{
		stairs();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslated(10, -610, 0);
		glRotated(-18, 0, 0, 1);
		glTranslated(0, 600, 0);
		stairs();

	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(-10, -600, 0);
		glRotated(18, 0, 0, 1);
		glTranslated(0, 600, 0);
		stairs();

	}
	glPopMatrix();


	glPushMatrix();
	{
		glTranslated(290, 0, 0);
		road();
	}



	glPopMatrix();

	glPushMatrix();
	{
		glRotated(90, 0, 0, 1);

		glTranslated(530, 220, 0);
		glScalef(1.2, .4, 1);
		road1();


	}
	glPopMatrix();
	///surface

	glScalef(1.3, 1, 1);
	glTranslated(10, -300, 0);

	glPushMatrix();
	{
		glColor3f(.6, .6, .61);
		glScaled(15, 40, 10);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex3f(30, -45, 0);
			glTexCoord2f(0, 1);
			glVertex3f(-30, -45, 0);
			glTexCoord2f(1, 1);
			glVertex3f(-30, 30, 0);

			glTexCoord2f(1, 0);
			glVertex3f(30, 30, 0);


		}
		glEnd();
	}
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	{
		glBindTexture(GL_TEXTURE_2D, sur);
		glPushMatrix();
		{
			glTranslated(0, -100, 8);
			glScaled(10.7, 15, 9);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 0);
				glVertex3f(30, -40, 0);
				glTexCoord2f(0, 1);
				glVertex3f(-30, -40, 0);
				glTexCoord2f(1, 1);
				glVertex3f(-30, 30, 0);

				glTexCoord2f(1, 0);
				glVertex3f(30, 30, 0);


			}
			glEnd();
		}
		glPopMatrix();

	}

	glDisable(GL_TEXTURE_2D);



	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glFlush();
	glutSwapBuffers();
}

void animate()
{
	glutPostRedisplay();    //this will call the display AGAIN

}

void init()
{
	glClearColor(0, 0, 0, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	/*
	gluPerspective() � set up a perspective projection matrix

	fovy -         Specifies the field of view angle, in degrees, in the y direction.
	aspect ratio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	zNear -        Specifies the distance from the viewer to the near clipping plane (always positive).
	zFar  -        Specifies the distance from the viewer to the far clipping plane (always positive).
	*/

	gluPerspective(90, 1, 0.1, 10000.0);


}

void keyboardListener(unsigned char key, int x, int y)
{
	switch (key)
	{

	case '+':
		at += 50;
		break;

	case '-':
		at -= 50;
		break;

	case 'l':
	case 'L':
		break;

	case 'r':
	case 'R':
		break;

	case 'q':
	case 'Q':
		break;

	case 'e':
	case 'E':
		break;

	case 'x':
		x += 10;
		//glutPostRedisplay();
		break;
	case 'y':
		y += 10;
		//glutPostRedisplay();
		break;
	case 'z':
		z += 10;
		//glutPostRedisplay();
		break;

	default:
		break;
	}
}

void specialKeyListener(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:		//down arrow key
		cameraHeight -= 80.0;
		break;
	case GLUT_KEY_UP:		// up arrow key
		cameraHeight += 90.0;
		break;

	case GLUT_KEY_RIGHT:
		cameraAngle += 0.3;
		break;
	case GLUT_KEY_LEFT:
		cameraAngle -= 0.3;
		break;

	case GLUT_KEY_PAGE_UP:
		break;
	case GLUT_KEY_PAGE_DOWN:
		break;

	case GLUT_KEY_INSERT:
		break;

	case GLUT_KEY_HOME:

		break;
	case GLUT_KEY_END:
		break;

	default:
		break;
	}
}

void mouseListener(int button, int state, int x, int y)
{
	//x, y is the x-y of the screen (2D)
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			// 2 times?? in ONE click? -- solution is checking DOWN or UP
		}
		break;

	case GLUT_RIGHT_BUTTON:
		//........
		break;

	case GLUT_MIDDLE_BUTTON:
		//........
		break;

	default:
		break;
	}
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);                            //initialize the GLUT library

	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(40, 0);

	/*
	glutInitDisplayMode - inits display mode
	GLUT_DOUBLE - allows for display on the double buffer window
	GLUT_RGBA - shows color (Red, green, blue) and an alpha
	GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("UIU Permanent Campus");

	printf("Camera Controls\n\n");
	printf("Roll: UP and DOWN arrow\n");
	printf("Pitch: Q and E\n");
	printf("Yaw: LEFT and RIGHT arrow\n");
	printf("Up-Down: PAGEUP and PAGEDOWN\n");
	printf("Left-Right: L and R\n");
	printf("Zoom in-out: + and -\n");
	printf("Reset Camera: HOME\n");

	init();                        //codes for initialization

	loadAllImages();

	//glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST);    //enable Depth Testing

								//loadAllImages();

	glutDisplayFunc(display);    //display callback function
	glutIdleFunc(animate);        //what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	glutMouseFunc(mouseListener);

	glutMainLoop();        //The main loop of OpenGL

	return 0;
}

