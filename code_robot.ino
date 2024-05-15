int IN1 = 12;                        //Pin pour Le Capteur Gauche
int IN4 = 3;                         //Pin pour Le Capteur Droite
int GA = 9, GB = 8, DA = 7, DB = 6;  //Pin pour Deux moteurs (GA et GB pour le moteur Gauche, DA et DB pour le moteur de droite)
int trig = 4;                        // Broche pour le signal de déclenchement du capteur ultrason
int echo = 5;                        // Broche pour la réception du signal du capteur ultrason
int bouton = 2;                      // Broche pour le bouton poussoir
float distance = 0;                  // Distance mesurée par le capteur ultrason

bool boutonActive = false;  // Variable pour indiquer si le bouton a été activé

void setup() {
  Serial.begin(9550);
  pinMode(IN1, INPUT);
  pinMode(IN4, INPUT);
  pinMode(DA, OUTPUT);
  pinMode(DB, OUTPUT);
  pinMode(GA, OUTPUT);
  pinMode(GB, OUTPUT);
}

void loop() {

  // Vérification si le bouton est activé pour la première fois
  if (!boutonActive && digitalRead(bouton)) {
    boutonActive = true;  // Marquer le bouton comme activé
  }

  //Si le bouton n'est pas actif, lance un nouveau cycle
  if (!boutonActive) {
    return;
  }

  // Si le bouton a été activé, exécuter le code suivant

  float distance = mesurerDistance();
  // Si un objet est détecté à moins de 20 cm, les moteurs s'arrêtent
  if (distance < 20) {
    // Faire une fonction pour arreté les moteur

    //Fin d'une loop plus tôt, ne lance jamais la fonction avance() et donc stop le robot à chaque fois que le code passe ici
    return;
  }



  {
    //Si compatible avec le robot, peut être changer avec analogRead() pour avoir des infos + précises que true/false et faire un calcul
    //d'angle afin d'adapté la rotation du robot et avoir un mouvement fluide
    int in1_val = digitalRead(IN1);
    int in4_val = digitalRead(IN4);


    if ((in1_val) && (!in4_val))  //S'il y a du noir à gauche et du blanc à droite, tourner à gauche
    {
      Serial.println("Tourner à gauche");
      tourneGauche();
    } else if ((!in1_val) && (in4_val))  //S'il y a du blanc à gauche et du noir à droite, tourner à droite
    {
      Serial.println("Tourner à droite");
      tourneDroite();
    } else  //Si les conditions plus haut ne s'appliquent pas, continuer tout droit
    {
      Serial.println("Continuer tout droit");
      avance();
    }
  }
}

//on Crée Les Fonctions FAIRE UNE FONCTION


// Fonction pour mesurer la distance avec le capteur ultrason
float mesurerDistance() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  return pulseIn(echo, HIGH) / 58;  // Conversion en centimètres
}

//Fonction qui permet au robot de tourner a droite
void tourneDroite() {
  digitalWrite(DA, LOW);
  analogWrite(DB, 100);
  analogWrite(GA, 100);
  digitalWrite(GB, LOW);
}

//Fonction qui permet au robot de tourner a gauche
void tourneGauche() {
  analogWrite(DA, 100);
  digitalWrite(DB, LOW);
  digitalWrite(GA, LOW);
  analogWrite(GB, 100);
}

//Fonction qui permet au robot de continuer tout droit
void avance() {
  digitalWrite(DA, LOW);
  analogWrite(DB, 100);
  digitalWrite(GA, LOW);
  analogWrite(GB, 100);
}