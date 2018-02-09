/*
Name:		MagicConMenus.ino
Created:	06/02/2018 11:31:57
Author:	joel_
*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <gfxfont.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

#define XPOS 0
#define YPOS 1
#define DELTAY 2


byte boton1 = 8;
byte boton2 = 9;
byte boton3 = 10;
byte boton4 = 11;

boolean luz = 1;
byte pagina = 1;
byte menuitem = 1;

int8_t vida1 = 20;
int8_t vida2 = 20;


unsigned long currentMillis = 0;
byte menu = 1;


void setup() {
	pinMode(2, OUTPUT);
	digitalWrite(2, HIGH);
	pinMode(8, INPUT);
	pinMode(9, INPUT);
	pinMode(10, INPUT);
	pinMode(11, INPUT);

	display.begin();
	display.setContrast(50);
	display.clearDisplay();   // clears the screen and buffer
}

void loop() {

	dibujaMenu();

	if (pagina == 1) {
		if (CompruebaBoton(boton1)) {
			menuitem--;
			if (menuitem == 0) menuitem = 3;
		}
		if (CompruebaBoton(boton3)) {
			menuitem++;
			if (menuitem == 4) menuitem = 1;

		}
		if (CompruebaBoton(boton2)) {
			switch (menuitem)
			{
			case 2:
			{
				pagina = 3;
				break;
			}
			case 3: {
				pagina = 4;
				break;
			}
			case 1: {
				pagina = 2;
				break;
			}
			default:
				break;
			}
		}
	}
	if (pagina == 2) {
		MenuVidas();
		if (CompruebaBoton(boton4)) pagina = 1;
	}if (pagina == 3) {
		MenuMana();
		if (CompruebaBoton(boton4)) pagina = 1;
	}if (pagina == 4) {
		MenuOpciones();
		if (CompruebaBoton(boton4)) pagina = 1;
	}
}

void dibujaMenu() {

	display.setRotation(0);
	if (pagina == 1) // Pagina principal
	{
		display.setTextSize(1);
		display.clearDisplay();
		display.setTextColor(BLACK, WHITE);
		display.setCursor(0, 0);
		display.print("MENU PRINCIPAL");
		display.drawFastHLine(0, 10, 83, BLACK);

		display.setCursor(0, 15);
		if (menuitem == 1) display.setTextColor(WHITE, BLACK); else	display.setTextColor(BLACK, WHITE);
		display.print(">Vidas");

		display.setCursor(0, 25);
		if (menuitem == 2) display.setTextColor(WHITE, BLACK); else	display.setTextColor(BLACK, WHITE);
		display.print(">Mana");

		if (menuitem == 3) display.setTextColor(WHITE, BLACK); else	display.setTextColor(BLACK, WHITE);
		display.setCursor(0, 35);
		display.print(">Opciones");
		display.display();
	}
}

boolean CompruebaBoton(byte slbtn) {

	boolean estboton = 0;

	while (digitalRead(slbtn) == HIGH)
	{
		estboton = 1;
		delay(5);
	}

	if (digitalRead(slbtn) == LOW && estboton) {
		estboton = 0;
		return 1;
	}
	else return 0;
}

void MenuVidas() {


	int8_t posMenu = 3;

	display.setRotation(0);
	while (!CompruebaBoton(boton4))
	{
		display.setTextSize(1); //El tamaño del caracter es de 6x8
		display.setTextColor(BLACK);
		display.setCursor(0, 0);
		display.print("Contador vidas");
		display.drawLine(0, 10, 84, 10, BLACK);
		display.setCursor(0, 13);
		display.print(" Jug1    Jug2");
		switch (posMenu)
		{
		case 1: { // Vida1 selec
			if (CompruebaBoton(boton1)) vida1++;
			if (CompruebaBoton(boton3)) vida1--;
			if (CompruebaBoton(boton2)) posMenu = 3;
			break;
		}
		case 2: { // Vida2 selec
			if (CompruebaBoton(boton1)) vida2++;
			if (CompruebaBoton(boton3)) vida2--;
			if (CompruebaBoton(boton2)) posMenu = 4;
			break;
		}
		case 3: { // Sin seleccion
			display.drawRect(4, 22, 28, 20, BLACK);
			if (CompruebaBoton(boton1) || CompruebaBoton(boton3)) posMenu = 4;
			if (CompruebaBoton(boton2)) posMenu = 1;
			break;
		}
		case 4: { // Sin seleccion
			if (CompruebaBoton(boton1) || CompruebaBoton(boton3)) posMenu = 3;
			display.drawRect(52, 22, 28, 20, BLACK);
			if (CompruebaBoton(boton2)) posMenu = 2;
			break;
		}
		default: break;
		}
		display.setTextSize(2);
		display.setCursor(7, 25);
		if (posMenu == 1) display.setTextColor(WHITE, BLACK); else	display.setTextColor(BLACK, WHITE);
		display.print(vida1);
		display.setCursor(55, 25);
		if (posMenu == 2) display.setTextColor(WHITE, BLACK); else	display.setTextColor(BLACK, WHITE);
		display.print(vida2);
		display.display();
		display.clearDisplay();
	}
	pagina = 1;

}

void MenuMana() {

	int8_t white = 0;
	int8_t blue = 0;
	int8_t black = 0;
	int8_t red = 0;
	int8_t green = 0;
	int8_t uncol = 0;

	int8_t posMenu = 1;


	display.setRotation(1); //48x84 Tamaño display rotado

	while (!CompruebaBoton(boton4))
	{
		switch (posMenu)
		{
		case 1: { // Blanco sin seleccionar
			display.drawRect(0, 0, 48, 10, BLACK);
			if (CompruebaBoton(boton1)) posMenu = 11;
			if (CompruebaBoton(boton3)) posMenu = 3;
			if (CompruebaBoton(boton2)) posMenu = 2;
			break;
		}
		case 2: { // Blanco seleccionado
			if (CompruebaBoton(boton1)) white++;
			if (CompruebaBoton(boton3)) white--;
			if (CompruebaBoton(boton2)) posMenu = 1;
			break;
		}
		case 3: { // Azul sin seleccionar
			display.drawRect(0, 15, 48, 10, BLACK);
			if (CompruebaBoton(boton1)) posMenu = 1;
			if (CompruebaBoton(boton3)) posMenu = 5;
			if (CompruebaBoton(boton2)) posMenu = 4;
			break;
		}
		case 4: { // Azul seleccionado
			if (CompruebaBoton(boton1)) blue++;
			if (CompruebaBoton(boton3)) blue--;
			if (CompruebaBoton(boton2)) posMenu = 3;
			break;
		}
		case 5: { // Negro sin seleccionar
			display.drawRect(0, 30, 48, 10, BLACK);
			if (CompruebaBoton(boton1)) posMenu = 3;
			if (CompruebaBoton(boton3)) posMenu = 7;
			if (CompruebaBoton(boton2)) posMenu = 6;
			break;
		}
		case 6: { // Negro seleccionado
			if (CompruebaBoton(boton1)) black++;
			if (CompruebaBoton(boton3)) black--;
			if (CompruebaBoton(boton2)) posMenu = 5;
			break;
		}
		case 7: { // Rojo sin seleccionar
			display.drawRect(0, 44, 48, 10, BLACK);
			if (CompruebaBoton(boton1)) posMenu = 5;
			if (CompruebaBoton(boton3)) posMenu = 9;
			if (CompruebaBoton(boton2)) posMenu = 8;
			break;
		}
		case 8: { // Rojo seleccionado
			if (CompruebaBoton(boton1)) red++;
			if (CompruebaBoton(boton3)) red--;
			if (CompruebaBoton(boton2)) posMenu = 7;
			break;
		}
		case 9: { // Verde sin seleccionar
			display.drawRect(0, 59, 48, 10, BLACK);
			if (CompruebaBoton(boton1)) posMenu = 7;
			if (CompruebaBoton(boton3)) posMenu = 11;
			if (CompruebaBoton(boton2)) posMenu = 10;
			break;
		}
		case 10: { // Verde seleccionado
			if (CompruebaBoton(boton1)) green++;
			if (CompruebaBoton(boton3)) green--;
			if (CompruebaBoton(boton2)) posMenu = 9;
			break;
		}
		case 11: { // Incoloro sin seleccionar
			display.drawRect(0, 74, 48, 10, BLACK);
			if (CompruebaBoton(boton1)) posMenu = 9;
			if (CompruebaBoton(boton3)) posMenu = 1;
			if (CompruebaBoton(boton2)) posMenu = 12;
			break;
		}
		case 12: { // Incoloro seleccionado
			if (CompruebaBoton(boton1)) uncol++;
			if (CompruebaBoton(boton3)) uncol--;
			if (CompruebaBoton(boton2)) posMenu = 11;
			break;
		}
		default: break;
		}

		display.setTextSize(1);
		display.setTextColor(BLACK);
		display.setTextWrap(false);
		display.setCursor(1, 1);
		display.print("Blanc");
		display.setCursor(37, 1);
		if (posMenu == 2) display.setTextColor(WHITE, BLACK);
		display.print(white);
		display.setTextColor(BLACK);
		display.setCursor(1, 16);
		display.print("Azul");
		display.setCursor(37, 16);
		if (posMenu == 4) display.setTextColor(WHITE, BLACK);
		display.print(blue);
		display.setTextColor(BLACK);
		display.setCursor(1, 31);
		display.print("Negro");
		display.setCursor(37, 31);
		if (posMenu == 6) display.setTextColor(WHITE, BLACK);
		display.print(black);
		display.setTextColor(BLACK);
		display.setCursor(1, 45);
		display.print("Rojo");
		display.setCursor(37, 45);
		if (posMenu == 8) display.setTextColor(WHITE, BLACK);
		display.print(red);
		display.setTextColor(BLACK);
		display.setCursor(1, 60);
		display.print("Verde");
		display.setCursor(37, 60);
		if (posMenu == 10) display.setTextColor(WHITE, BLACK);
		display.print(green);
		display.setTextColor(BLACK);
		display.setCursor(1, 75);
		display.print("Inco");
		display.setCursor(37, 75);
		if (posMenu == 12) display.setTextColor(WHITE, BLACK);
		display.print(uncol);
		display.setTextColor(BLACK);
		display.display();
		display.clearDisplay();
	}

	pagina = 1;

}

void MenuOpciones() {

	int8_t posMenu = 1;
	display.setRotation(0);

	while (!CompruebaBoton(boton4))
	{
		display.setTextSize(1);
		display.clearDisplay();
		display.setTextColor(BLACK, WHITE);
		display.setCursor(0, 0);
		display.print("OPCIONES");
		display.drawFastHLine(0, 10, 83, BLACK);

		display.setCursor(0, 15);
		if (posMenu == 1) display.setTextColor(WHITE, BLACK); else	display.setTextColor(BLACK, WHITE);
		display.print(">Luz");

		display.setCursor(0, 25);
		if (posMenu == 2) display.setTextColor(WHITE, BLACK); else	display.setTextColor(BLACK, WHITE);
		display.print(">Reset");

		if (posMenu == 3) display.setTextColor(WHITE, BLACK); else	display.setTextColor(BLACK, WHITE);
		display.setCursor(0, 35);
		display.print(">Reset");
		display.display();


		if (CompruebaBoton(boton1)) {
			posMenu--;
			if (posMenu == 0) posMenu = 3;
		}
		if (CompruebaBoton(boton3)) {
			posMenu++;
			if (posMenu == 4) posMenu = 1;

		}
		if (CompruebaBoton(boton2)) {
			switch (posMenu)
			{
			case 1:
			{
				if (digitalRead(2) == HIGH) {
					luz = 0;
					digitalWrite(2, LOW);
				}
				else {
					luz = 1;
					digitalWrite(2, HIGH);
				}
				break;
			}
			case 2: {
				vida1 = 20;
				vida2 = 20;
				break;
			}
			case 3: {
				vida1 = 20;
				vida2 = 20;
				break;
			}
			default:
				break;
			}

		}
	}
	pagina = 1;
}