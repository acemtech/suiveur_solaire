#include <Servo.h> // Pour inclure les servo-moteurs et leurs fonctionnalités prédéfinies dans la bibliothéque “servo.h”
Servo servohori; // Nomination de servomoteur horizontal dans le code
int servoh = 0;
int servohLimitMax = 160;
int servohLimitMin = 20;
Servo servoverti; // Nomination de servomoteur vertical dans le code
int servov = 0;
int servovLimitMax = 160;
int servovLimitMin = 20;
int ldrGaucheB = 0; 
// Ceci correspond aux branchement des capteurs sur la carte électronique. Par exemple, le capteur en bas à gauche est relié au port A0 sur la carte Arduino
int ldrGaucheH = 1;
int ldrDroiteB = 2;
int ldrDroiteH = 3;
// Réglages et liaison Arduino/servomoteurs
void setup () // début de la boucle de réglage
{
servohori.attach(10) ;//le fil de signal de commande pour le servo horizontal sera connecté à la pin 10 de la carte
servohori.write(0);// le fil de signal de commande pour le servo verticalsera connecté à la pin 9 de la carte
servoverti.attach(9);//

servoverti.write(0);
delay(500);
}
// Acquisition de la luminosité
void loop() // début de la boucle principale
{
servoh = servohori.read();
servov = servoverti.read();
int hautG = analogRead(ldrGaucheH); // déclaration des entiers dont on aurons besoin
int hautD = analogRead(ldrDroiteH);
int basG = analogRead(ldrGaucheB);
int basD = analogRead(ldrDroiteB);
//Calcul des moyennes
float moyH = (hautD+hautG) / 2; // calcul des moyennes des 4 directions
float moyB = (basG+basD) / 2;
float moyG = (hautG+basG) / 2;
float moyD = (hautD+basD) / 2;
if (moyH < moyB)
{
servohori.write(servoh +1); // on décrémente la position du servo verticale
if (servoh > servohLimitMax)
{
servoh = servohLimitMax;
}
delay(10);
}
else if (moyB < moyH) // Si le haut reçoit plus de lumière que le bas,
{
servohori.write(servoh -1); // Mouvements en conséquence
if (servoh < servohLimitMin)
{
servoh = servohLimitMin;
}
delay(10);
}
else
{
servohori.write(servoh);
}
if (moyG > moyD)  // Si le gauche reçoit plus de lumière que le droit
{
servoverti.write(servov +1); // Mouvements en conséquence
if (servov > servovLimitMax)
{
  servov = servovLimitMax;
}
delay(10);
}
else if (moyD > moyG) // Si le droit reçoit plus de lumière que le gauche
{
servoverti.write(servov -1); // Mouvements en conséquence
if (servov < servovLimitMin)
{
servov = servovLimitMin;
}
delay(10);
}
else
{
servoverti.write(servov);
}
delay(50);// un délai de 50 milliseconde avant de exécuter une autre fois le programme principal
}
